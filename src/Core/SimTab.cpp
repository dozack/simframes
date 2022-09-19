#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimTab::SimTab(SimFrames::Core::SimWindow &window, std::string description)
        : Description(description)
        , Window(window)
        , Lock(window.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        Obj = lv_tabview_add_tab(window.TabView, Description.c_str());
        lv_obj_clear_flag(Obj, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Obj, LV_SCROLLBAR_MODE_OFF);
    }

}}