#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimWidget::SimWidget(SimContainer &container, uint8_t descriptionWidth, std::string description)
        : Container(container)
        , Lock(container.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        lvWidgetFrame = lv_obj_create(Container.lvContainer);
        lv_obj_set_size(lvWidgetFrame, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lvWidgetFrame, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(lvWidgetFrame, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER);
        lv_obj_center(lvWidgetFrame);
        lv_obj_clear_flag(lvWidgetFrame, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(lvWidgetFrame, LV_SCROLLBAR_MODE_OFF);

        if (descriptionWidth > 0)
        {
            if (descriptionWidth > 100)
            {
                descriptionWidth = 100;
            }

            lvDescriptionFrame = lv_obj_create(lvWidgetFrame);
            lv_obj_set_size(lvDescriptionFrame, LV_PCT(descriptionWidth), LV_SIZE_CONTENT);
            lv_obj_center(lvDescriptionFrame);
            lv_obj_clear_flag(lvDescriptionFrame, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(lvDescriptionFrame, LV_SCROLLBAR_MODE_OFF);

            lvDescriptionLabel = lv_label_create(lvDescriptionFrame);
            lv_label_set_text(lvDescriptionLabel, description.c_str());
            lv_obj_center(lvDescriptionLabel);
            lv_obj_clear_flag(lvDescriptionLabel, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(lvDescriptionLabel, LV_SCROLLBAR_MODE_OFF);
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