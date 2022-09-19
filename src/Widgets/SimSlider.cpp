#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimSliderObject::SimSliderObject(SimSlider &parent, uint8_t width, std::string description)
        : SimFrames::Core::SimWidgetObject(parent, (100 - width), description)
        , Parent(parent)
        , Events(nullptr)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        SliderContainer = lv_obj_create(Frame);
        lv_obj_set_size(SliderContainer, LV_PCT(width), LV_SIZE_CONTENT);
        lv_obj_center(SliderContainer);
        lv_obj_clear_flag(SliderContainer, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(SliderContainer, LV_SCROLLBAR_MODE_OFF);

        Slider = lv_slider_create(SliderContainer);
        lv_obj_set_size(Slider, LV_PCT(100), LV_SIZE_CONTENT);
        lv_slider_set_range(Slider, 0, 100);
        lv_slider_set_value(Slider, 0, LV_ANIM_OFF);
        lv_obj_center(Slider);
        lv_obj_add_event_cb(Slider, &SimSliderObject::OnEvent, LV_EVENT_VALUE_CHANGED, this);

        SliderValue = lv_label_create(Slider);
        lv_obj_set_style_text_color(SliderValue, LV_COLOR_MAKE(0x26, 0x32, 0x38), 0);
        lv_label_set_text_fmt(SliderValue, "%i", lv_slider_get_value(Slider));
        lv_obj_center(SliderValue);
    }

    void SimSliderObject::OnEvent(lv_event_t *event)
    {
        SimSliderObject *obj;

        if (event == nullptr)
        {
            return;
        }

        obj = static_cast<SimSliderObject *>(lv_event_get_user_data(event));

        if (obj)
        {
            lv_label_set_text_fmt(obj->SliderValue, "%d", lv_slider_get_value(obj->Slider));
            lv_obj_center(obj->SliderValue);

            if (obj->Events)
            {
                obj->Events->OnValueChanged(&obj->Parent);
            }
        }
    }

    SimSlider::SimSlider(SimFrames::Core::SimContainer &container, uint8_t width,
                         std::string description)
        : SimFrames::Core::SimWidget(container)
        , Obj(*this, width, description)
    {}

    void SimSlider::SetRange(int minValue, int maxValue)
    {
        lv_slider_mode_t mode;

        mode = (minValue < 0) ? (LV_SLIDER_MODE_SYMMETRICAL) : (LV_SLIDER_MODE_NORMAL);

        lv_slider_set_mode(Obj.Slider, mode);
        lv_slider_set_range(Obj.Slider, minValue, maxValue);
    }

    int SimSlider::ReadValue()
    {
        return ((int)lv_slider_get_value(Obj.Slider));
    }

    void SimSlider::SetEvents(SimFrames::Widgets::SimSliderEvents *events)
    {
        Obj.Events = events;
    }
}}