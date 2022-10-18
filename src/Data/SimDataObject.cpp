#include <SimFrames.h>

#include <typeinfo>

namespace SimFrames { namespace Data {

    template <typename T>
    SimDataObject<T>::SimDataObject(T value)
        : Value(value)
    {
        const std::type_info &tin = typeid(T);

        if (tin == typeid(bool))
        {
            Type = SimDataObjectType::Boolean;
        }
        else if (tin == typeid(int32_t))
        {
            Type = SimDataObjectType::Signed32;
        }
        else if (tin == typeid(uint32_t))
        {
            Type = SimDataObjectType::Unsigned32;
        }
        else if (tin == typeid(std::string))
        {
            Type = SimDataObjectType::String;
        }
    }

    template <typename T>
    SimDataObjectType SimDataObject<T>::GetType()
    {
        return Type;
    }

    template <typename T>
    size_t SimDataObject<T>::GetSize()
    {
        if (Type == SimDataObjectType::String)
        {
            {
                void *sval = &Value;
                return (static_cast<std::string *>(sval)->length());
            }
        }
        else
        {
            return sizeof(T);
        }
    }

    template <typename T>
    SimFrames::Core::OperationResult SimDataObject<T>::ReadRaw(void *dest, size_t size)
    {
        if ((dest == nullptr) || (size < sizeof(T)))
        {
            return SimFrames::Core::OperationResult::Error;
        }
        memcpy(dest, &Value, size);
        return SimFrames::Core::OperationResult::Success;
    }

    template <typename T>
    SimFrames::Core::OperationResult SimDataObject<T>::WriteRaw(void *src, size_t size)
    {
        if ((src == nullptr) || (size > sizeof(T)))
        {
            return SimFrames::Core::OperationResult::Error;
        }
        memcpy(&Value, src, size);
        return SimFrames::Core::OperationResult::Success;
    }

    template <typename T>
    SimFrames::Core::OperationResult SimDataObject<T>::Read(T *dest)
    {
        if (dest == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }
        *dest = Value;
        return SimFrames::Core::OperationResult::Success;
    }

    template <typename T>
    SimFrames::Core::OperationResult SimDataObject<T>::Write(T *src)
    {
        if (src == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }
        Value = *src;
        return SimFrames::Core::OperationResult::Success;
    }

    template class SimDataObject<bool>;
    template class SimDataObject<int32_t>;
    template class SimDataObject<uint32_t>;
    template class SimDataObject<std::string>;
}}