#ifndef SIM_WINDOW_H_
#define SIM_WINDOW_H_

#include <lvgl/lvgl.h>

#include <mutex>

namespace SimFrames { namespace Core {

    typedef void (*SimDriverInitFunc_t)(void);

    class SimWindow
    {
    public:
        std::mutex Lock;
        lv_obj_t*  TabView;

        SimWindow(SimDriverInitFunc_t initFunc);

        ~SimWindow();
    };

}}

#endif