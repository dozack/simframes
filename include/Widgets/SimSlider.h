#ifndef SIM_SLIDER_H_
#define SIM_SLIDER_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    class SimSlider;

    class SimSliderEvents
    {
    public:
        virtual void OnValueChanged(SimSlider *sender) = 0;
    };

    class SimSliderObject : public SimFrames::Core::SimWidgetObject
    {
    public:
        SimSlider       &Parent;
        lv_obj_t        *SliderContainer;
        lv_obj_t        *Slider;
        lv_obj_t        *SliderValue;
        SimSliderEvents *Events;

        SimSliderObject(SimSlider &parent, uint8_t width, std::string description = "");

        ~SimSliderObject(){};

    private:
        static void OnEvent(lv_event_t *event);
    };

    class SimSlider : public SimFrames::Core::SimWidget
    {
    public:
        SimSliderObject Obj;

        SimSlider(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                  std::string description = "Slider");

        ~SimSlider(){};

        int SetRange(int minValue, int maxValue);

        int WriteValue(int32_t value);

        int ReadValue(int32_t *value);

        void SetEvents(SimFrames::Widgets::SimSliderEvents *events);
    };

}}

#endif