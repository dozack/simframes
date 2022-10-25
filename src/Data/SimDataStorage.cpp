#include <SimFrames.h>

namespace SimFrames { namespace Data {

    SimDataStorage::SimDataStorage(){};

    SimDataStorage::~SimDataStorage(){};

    SimFrames::Core::OperationResult SimDataStorage::Add(std::string key, int32_t defaultValue)
    {
        std::lock_guard<std::mutex> lk(Lock);

        auto it = Entries.find(key);

        if (it != Entries.end())
        {
            return SimFrames::Core::OperationResult::Error;
        }

        auto entry = Entries.emplace(key, std::make_shared<SimDataObject>(defaultValue));

        if (entry.second)
        {
            return SimFrames::Core::OperationResult::Success;
        }

        return SimFrames::Core::OperationResult::Error;
    }

    SimFrames::Core::OperationResult SimDataStorage::Remove(std::string key)
    {
        std::lock_guard<std::mutex> lk(Lock);

        auto it = Entries.find(key);

        if (it != Entries.end())
        {
            Entries.erase(it);
            return SimFrames::Core::OperationResult::Success;
        }

        return SimFrames::Core::OperationResult::Error;
    }

    SimFrames::Core::OperationResult SimDataStorage::Remove(RSimDataObject object)
    {
        std::lock_guard<std::mutex> lk(Lock);

        for (auto it : Entries)
        {
            if (it.second == object)
            {
                Entries.erase(it.first);
                return SimFrames::Core::OperationResult::Success;
            }
        }

        return SimFrames::Core::OperationResult::Error;
    }

    RSimDataObject SimDataStorage::Find(std::string key)
    {
        std::lock_guard<std::mutex> lk(Lock);

        auto it = Entries.find(key);

        if (it != Entries.end())
        {
            return it->second;
        }

        return nullptr;
    }

}}