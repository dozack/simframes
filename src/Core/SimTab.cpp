#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimTab::SimTab(SimFrames::Core::SimWindow &window, std::string description)
        : Window(window)
        , Lock(window.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        lvTab = lv_tabview_add_tab(window.lvTabView, description.c_str());
        lv_obj_clear_flag(lvTab, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(lvTab, LV_SCROLLBAR_MODE_OFF);
    }

}}