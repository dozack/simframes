#ifndef SIM_TAB_H_
#define SIM_TAB_H_

#include <Core/SimCommon.h>

namespace SimFrames { namespace Core {

    class SimWindow;

    class SimTab
    {
    public:
        SimFrames::Core::SimWindow &Window;
        SimFrames::Core::SimLock   &Lock;
        lv_obj_t                   *lvTab;

        SimTab(SimWindow &window, std::string description = "Tab");

        ~SimTab(){};
    };

}}

#endif