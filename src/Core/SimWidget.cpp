#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimWidget::SimWidget(SimContainer &container, uint8_t descriptionWidth, std::string description)
        : Container(container)
        , Lock(container.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        Frame = lv_obj_create(Container.Obj);
        lv_obj_set_size(Frame, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(Frame, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(Frame, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER);
        lv_obj_center(Frame);
        lv_obj_clear_flag(Frame, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Frame, LV_SCROLLBAR_MODE_OFF);

        if (descriptionWidth > 0)
        {
            if (descriptionWidth > 100)
            {
                descriptionWidth = 100;
            }

            DescriptionContainer = lv_obj_create(Frame);
            lv_obj_set_size(DescriptionContainer, LV_PCT(descriptionWidth), LV_SIZE_CONTENT);
            lv_obj_center(DescriptionContainer);
            lv_obj_clear_flag(DescriptionContainer, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(DescriptionContainer, LV_SCROLLBAR_MODE_OFF);

            DescriptionLabel = lv_label_create(DescriptionContainer);
            lv_label_set_text(DescriptionLabel, description.c_str());
            lv_obj_center(DescriptionLabel);
            lv_obj_clear_flag(DescriptionLabel, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(DescriptionLabel, LV_SCROLLBAR_MODE_OFF);
        }
    }

    void SimWidget::OnValueChanged()
    {
        for (auto it : Listeners)
        {
            if (it != nullptr)
            {
                it->OnValueChanged(*this);
            }
        }
    }

    OperationResult SimWidget::AddListener(SimWidgetEventListener *listener)
    {
        auto it = std::find(Listeners.begin(), Listeners.end(), listener);

        if (it != Listeners.end())
        {
            return SimFrames::Core::OperationResult::Error;
        }

        Listeners.push_back(listener);
        return SimFrames::Core::OperationResult::Success;
    }

    OperationResult SimWidget::RemoveListener(SimWidgetEventListener *listener)
    {
        Listeners.erase(std::find(Listeners.begin(), Listeners.end(), listener));
        return SimFrames::Core::OperationResult::Success;
    }

    SimWidgetType SimWidget::GetType()
    {
        return SimWidgetType::Unknown;
    }

}}