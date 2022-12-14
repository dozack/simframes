#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimWindow::SimWindow(SimDriverInitFunc_t initFunc)
        : IsActive(false)
    {
        lv_coord_t tabSize = 50;

        /*
         * No need for mutex lock here as window is meant
         * to be constructed only once during application
         * runtime. At this time, there are no lvgl threads
         * running, thus mutex is not required anyway.
         */

        if (!lv_is_initialized())
        {
            lv_init();
        }

        if (initFunc != nullptr)
        {
            initFunc();
        }

        lvTabView = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, tabSize);
    }

    SimWindow::~SimWindow()
    {
        Terminate();
        WaitForTermination();
    }

    void SimWindow::Deploy(uint32_t cycleTime)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        if (IsActive)
        {
            return;
        }

        IsActive   = true;

        TickThread = std::thread(&SimWindow::TickThreadFunc, this, cycleTime);
        MainThread = std::thread(&SimWindow::MainThreadFunc, this, cycleTime);
    }

    void SimWindow::Terminate()
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        if (IsActive)
        {
            IsActive = false;
        }
    }

    void SimWindow::WaitForTermination()
    {
        if (TickThread.joinable())
        {
            TickThread.join();
        }
        if (MainThread.joinable())
        {
            MainThread.join();
        }
    }

    void SimWindow::TickThreadFunc(void *context, uint32_t cycleTime)
    {
        SimFrames::Core::SimWindow *window = static_cast<SimFrames::Core::SimWindow *>(context);

        while (window->IsActive)
        {
            {
                std::lock_guard<std::mutex> lk(window->Lock.Lock);
                lv_tick_inc(cycleTime);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
        }
    }

    void SimWindow::MainThreadFunc(void *context, uint32_t cycleTime)
    {
        SimFrames::Core::SimWindow *window = static_cast<SimFrames::Core::SimWindow *>(context);

        while (window->IsActive)
        {
            {
                std::lock_guard<std::mutex> lk(window->Lock.Lock);
                lv_task_handler();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
        }
    }

}}