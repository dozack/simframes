#ifndef SIM_SLIDER_H_
#define SIM_SLIDER_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    class SimSlider : public SimFrames::Core::SimWidget
    {
    private:
        lv_obj_t *SliderContainer;
        lv_obj_t *Slider;
        lv_obj_t *SliderValue;

        static void _event_callback(lv_event_t *event);

    public:
        SimSlider(SimFrames::Core::SimContainer &container, uint8_t descriptionWidth = 50,
                  std::string description = "Slider");

        ~SimSlider(){};

        SimFrames::Core::SimWidgetType GetType() override;

        SimFrames::Core::OperationResult SetRange(int32_t minValue, int32_t maxValue);

        SimFrames::Core::OperationResult WriteValue(int32_t value);

        SimFrames::Core::OperationResult ReadValue(int32_t *value);
    };

}}

#endif