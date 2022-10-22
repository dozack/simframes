#include <SimFrames.h>

#include <typeinfo>

namespace SimFrames { namespace Data {

    SimDataObject::SimDataObject(bool defaultValue)
        : ValueType(SimDataObjectType::Boolean)
        , ValueSize(sizeof(defaultValue))
    {
        Value = new bool(defaultValue);
    }

    SimDataObject::SimDataObject(int64_t defaultValue)
        : ValueType(SimDataObjectType::Integer)
        , ValueSize(sizeof(defaultValue))
    {
        Value = new int64_t(defaultValue);
    }

    SimDataObject::SimDataObject(double defaultValue)
        : ValueType(SimDataObjectType::Decimal)
        , ValueSize(sizeof(defaultValue))
    {
        Value = new double(defaultValue);
    }

    SimDataObject::~SimDataObject()
    {
        switch (ValueType)
        {
        case SimDataObjectType::Boolean:
            delete ((bool *)Value);
            break;
        case SimDataObjectType::Integer:
            delete ((int64_t *)Value);
            break;
        case SimDataObjectType::Decimal:
            delete ((double *)Value);
            break;
        default:
            break;
        }
    }

    SimDataObjectType SimDataObject::GetType()
    {
        return (ValueType);
    }

    size_t SimDataObject::GetSize()
    {
        return (ValueSize);
    }

    SimFrames::Core::OperationResult SimDataObject::Read(void *dest, size_t maxSize)
    {
        if (maxSize < ValueSize)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        memcpy(dest, Value, ValueSize);

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataObject::Write(void *src, size_t maxSize)
    {
        if (maxSize > ValueSize)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        memcpy(Value, src, ValueSize);

        return SimFrames::Core::OperationResult::Success;
    }

}}