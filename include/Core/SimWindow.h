#ifndef SIM_WINDOW_H_
#define SIM_WINDOW_H_

#include <Core/SimCommon.h>
#include <Core/SimLock.h>

namespace SimFrames { namespace Core {

    typedef void (*SimDriverInitFunc_t)(void);

    class SimWindow
    {
    public:
        SimFrames::Core::SimLock Lock;
        bool                     IsActive;
        lv_obj_t                *lvTabView;

        SimWindow(SimDriverInitFunc_t initFunc = nullptr);

        ~SimWindow();

        void Deploy(uint32_t cycleTime = 10);

        void Terminate();

        void WaitForTermination();

    private:
        std::thread TickThread;
        std::thread MainThread;

        static void TickThreadFunc(void *context, uint32_t cycleTime);

        static void MainThreadFunc(void *context, uint32_t cycleTime);
    };

}}

#endif