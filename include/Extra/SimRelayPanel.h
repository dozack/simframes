#ifndef SIM_RELAY_PANEL_H_
#define SIM_RELAY_PANEL_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Extra {

    static constexpr lv_color_t RelayColorOn  = LV_COLOR_MAKE(119, 221, 119);
    static constexpr lv_color_t SimRelayColorOff = LV_COLOR_MAKE(220, 220, 220);

    class SimRelayPanel;

    class SimRelayPanelObject : public SimFrames::Core::SimWidgetObject
    {
    public:
    };

    class SimRelayPanel : public SimFrames::Core::SimWidget
    {
    public:
    };

}}

#endif