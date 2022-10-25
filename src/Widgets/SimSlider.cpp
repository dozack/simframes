#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimSlider::SimSlider(SimFrames::Core::SimContainer &container, uint8_t descriptionWidth,
                         std::string description)
        : SimFrames::Core::SimWidget(container, (100 - descriptionWidth), description)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        SliderContainer = lv_obj_create(lvWidgetFrame);
        lv_obj_set_size(SliderContainer, LV_PCT(descriptionWidth), LV_SIZE_CONTENT);
        lv_obj_center(SliderContainer);
        lv_obj_clear_flag(SliderContainer, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(SliderContainer, LV_SCROLLBAR_MODE_OFF);

        Slider = lv_slider_create(SliderContainer);
        lv_obj_set_size(Slider, LV_PCT(100), LV_SIZE_CONTENT);
        lv_slider_set_range(Slider, 0, 100);
        lv_slider_set_value(Slider, 0, LV_ANIM_OFF);
        lv_obj_center(Slider);
        lv_obj_add_event_cb(Slider, &_event_callback, LV_EVENT_VALUE_CHANGED, this);

        SliderValue = lv_label_create(Slider);
        lv_obj_set_style_text_color(SliderValue, LV_COLOR_MAKE(0x26, 0x32, 0x38), 0);
        lv_label_set_text_fmt(SliderValue, "%i", lv_slider_get_value(Slider));
        lv_obj_center(SliderValue);
    }

    SimFrames::Core::SimWidgetType SimSlider::GetType()
    {
        return SimFrames::Core::SimWidgetType::Slider;
    }

    SimFrames::Core::OperationResult SimSlider::SetRange(int32_t minValue, int32_t maxValue)
    {
        lv_slider_mode_t mode;

        if (minValue > maxValue)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        mode = (minValue < 0) ? (LV_SLIDER_MODE_SYMMETRICAL) : (LV_SLIDER_MODE_NORMAL);

        lv_slider_set_range(Slider, minValue, maxValue);
        lv_slider_set_mode(Slider, mode);

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimSlider::WriteValue(int32_t value)
    {
        lv_slider_set_value(Slider, value, LV_ANIM_ON);
        lv_event_send(Slider, LV_EVENT_VALUE_CHANGED, this);
        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimSlider::ReadValue(int32_t *value)
    {
        *value = lv_slider_get_value(Slider);
        return SimFrames::Core::OperationResult::Success;
    }

    void SimSlider::_event_callback(lv_event_t *event)
    {
        SimSlider *slider;

        if (event == nullptr)
        {
            return;
        }

        slider = static_cast<SimSlider *>(lv_event_get_user_data(event));

        if (slider != nullptr)
        {
            lv_label_set_text_fmt(slider->SliderValue, "%d", lv_slider_get_value(slider->Slider));
            lv_obj_center(slider->SliderValue);
            slider->OnValueChanged();
        }
    }
}}