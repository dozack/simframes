#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimNumericInput::SimNumericInput(SimFrames::Core::SimContainer &container,
                                     uint8_t descriptionWidth, std::string description)
        : SimFrames::Core::SimWidget(container, (100 - descriptionWidth), description)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        TextArea = lv_textarea_create(Frame);
        lv_obj_set_size(TextArea, LV_PCT(descriptionWidth), LV_SIZE_CONTENT);
        lv_obj_clear_flag(TextArea, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        lv_textarea_set_one_line(TextArea, true);
        lv_textarea_set_accepted_chars(TextArea, "1234567890-");
        lv_obj_add_event_cb(TextArea, &_event_callback, LV_EVENT_READY, this);
        lv_obj_add_event_cb(TextArea, &_event_callback, LV_EVENT_VALUE_CHANGED, this);
        lv_obj_center(TextArea);
    }

    SimFrames::Core::SimWidgetType SimNumericInput::GetType()
    {
        return SimFrames::Core::SimWidgetType::NumericInput;
    }

    SimFrames::Core::OperationResult SimNumericInput::ReadValue(int32_t *value)
    {
        if (value == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        *value = (int32_t)atoi(lv_textarea_get_text(TextArea));
        return SimFrames::Core::OperationResult::Success;
    }

    void SimNumericInput::_event_callback(lv_event_t *event)
    {
        SimNumericInput *input;

        if (event == nullptr)
        {
            return;
        }

        input = static_cast<SimNumericInput *>(lv_event_get_user_data(event));

        if (input != nullptr)
        {
            lv_event_code_t eventCode  = lv_event_get_code(event);
            const char     *objectText = lv_textarea_get_text(input->TextArea);

            if (strlen(objectText) <= 0)
            {
                lv_textarea_set_accepted_chars(input->TextArea, "1234567890-");
            }
            else
            {
                lv_textarea_set_accepted_chars(input->TextArea, "1234567890");
            }

            if (eventCode == LV_EVENT_READY)
            {
                input->OnValueChanged();
            }
        }
    }

}}