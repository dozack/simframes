#include <SimFrames.h>

#include <typeinfo>

namespace SimFrames { namespace Data {

    SimDataObject::SimDataObject(int32_t defaultValue)
        : Value(defaultValue)
    {}

    void SimDataObject::OnWrite()
    {
        for (auto it : Listeners)
        {
            if (it != nullptr)
            {
                it->OnWrite(*this);
            }
        }
    }

    void SimDataObject::OnRead()
    {
        for (auto it : Listeners)
        {
            if (it != nullptr)
            {
                it->OnRead(*this);
            }
        }
    }

    SimFrames::Core::OperationResult SimDataObject::AddListener(
        SimDataObjectEventListener *listener)
    {
        auto it = std::find(Listeners.begin(), Listeners.end(), listener);

        if (it != Listeners.end())
        {
            return SimFrames::Core::OperationResult::Error;
        }

        Listeners.push_back(listener);
        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataObject::RemoveListener(
        SimDataObjectEventListener *listener)
    {
        Listeners.erase(std::find(Listeners.begin(), Listeners.end(), listener));
        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataObject::Read(int32_t *dest)
    {
        if (dest == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            memcpy(dest, &Value, sizeof(Value));
        }

        OnRead();

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataObject::Write(int32_t *src)
    {
        if (src == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            memcpy(&Value, src, sizeof(Value));
        }

        OnWrite();

        return SimFrames::Core::OperationResult::Success;
    }

}}