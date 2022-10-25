#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimLabel::SimLabel(SimFrames::Core::SimContainer &container, uint8_t descriptionWidth,
                       std::string description)
        : SimFrames::Core::SimWidget(container, (100 - descriptionWidth), description)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        LabelContainer = lv_obj_create(Frame);
        lv_obj_set_size(LabelContainer, LV_PCT(descriptionWidth), LV_SIZE_CONTENT);
        lv_obj_center(LabelContainer);
        lv_obj_clear_flag(LabelContainer, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(LabelContainer, LV_SCROLLBAR_MODE_OFF);

        Label = lv_label_create(LabelContainer);
        lv_label_set_text(Label, "");
        lv_obj_center(Label);
        lv_obj_clear_flag(Label, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Label, LV_SCROLLBAR_MODE_OFF);
    }

    SimFrames::Core::SimWidgetType SimLabel::GetType()
    {
        return SimFrames::Core::SimWidgetType::Label;
    }

    SimFrames::Core::OperationResult SimLabel::WriteValue(std::string value)
    {
        if (value != Value)
        {
            lv_label_set_text(Label, Value.c_str());
            Value = value;

            OnValueChanged();
        }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimLabel::ReadValue(std::string *value)
    {
        if (value == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        *value = Value;
        return SimFrames::Core::OperationResult::Success;
    }

}}