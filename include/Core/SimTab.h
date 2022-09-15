#ifndef SIM_TAB_H_
#define SIM_TAB_H_

#include <lvgl/lvgl.h>
#include <stdbool.h>

#include <string>

namespace SimFrames { namespace Core {

    class SimWindow;

    class SimTab
    {
    public:
        std::string Description;
        SimWindow  &Window;
        lv_obj_t   *Obj;

        SimTab(SimWindow &window, std::string description = "Tab");

        ~SimTab();
    };

}}

#endif