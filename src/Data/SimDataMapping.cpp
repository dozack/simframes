#include <SimFrames.h>

namespace SimFrames { namespace Data {

    SimDataMapping::SimDataMapping(SimDataStorage &storage, std::string key)
        : Valid(false)
    {
        Object = storage.Find(key);

        if (Object != nullptr)
        {
            Valid = true;
        }
    }

    SimWidgetToDataMapping::SimWidgetToDataMapping(SimDataStorage             &storage,
                                                   SimFrames::Core::SimWidget &widget,
                                                   std::string                 key)
        : SimDataMapping(storage, key)
    {
        if (!Valid)
        {
            return;
        }

        widget.AddListener(this);
    }

    void SimWidgetToDataMapping::OnValueChanged(SimFrames::Core::SimWidget &widget)
    {
        SimFrames::Core::OperationResult result;
        int32_t                          value;

        if (!Valid)
        {
            return;
        }

        switch (widget.GetType())
        {
        case SimFrames::Core::SimWidgetType::NumericInput:

            result = ((SimFrames::Widgets::SimNumericInput &)widget).ReadValue(&value);
            if (result == SimFrames::Core::OperationResult::Success)
            {
                Object->Write(&value);
            }

            break;
        case SimFrames::Core::SimWidgetType::Slider:

            result = ((SimFrames::Widgets::SimSlider &)widget).ReadValue(&value);
            if (result == SimFrames::Core::OperationResult::Success)
            {
                Object->Write(&value);
            }

            break;
        default:
            return;
        }
    }

    SimDataToWidgetMapping::SimDataToWidgetMapping(SimDataStorage             &storage,
                                                   SimFrames::Core::SimWidget &widget,
                                                   std::string                 key)
        : SimDataMapping(storage, key)
        , Widget(widget)
    {
        if (!Valid)
        {
            return;
        }

        Object->AddListener(this);
    }

    void SimDataToWidgetMapping::OnWrite(SimDataObject &object)
    {
        SimFrames::Core::OperationResult result;
        int32_t                          value;

        if (!Valid)
        {
            return;
        }

        result = object.Read(&value);

        if (result != SimFrames::Core::OperationResult::Success)
        {
            return;
        }

        switch (Widget.GetType())
        {
        case SimFrames::Core::SimWidgetType::Label:

            ((SimFrames::Widgets::SimLabel &)Widget).WriteValue(std::to_string(value));

            break;
        case SimFrames::Core::SimWidgetType::Relay:

            ((SimFrames::Widgets::SimRelay &)Widget).SetState((bool)value);

            break;
        default:
            return;
        }
    }

    void SimDataToWidgetMapping::OnRead(SimDataObject &object) {}

}}