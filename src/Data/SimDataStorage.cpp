#include <SimFrames.h>

namespace SimFrames { namespace Data {

    SimDataStorageEntry::SimDataStorageEntry(bool defaultValue)
        : Object(defaultValue)
    {}

    SimDataStorageEntry::SimDataStorageEntry(int64_t defaultValue)
        : Object(defaultValue)
    {}

    SimDataStorageEntry::SimDataStorageEntry(double defaultValue)
        : Object(defaultValue)
    {}

    SimDataStorageEntry::~SimDataStorageEntry() {}

    void SimDataStorageEntry::AddListener(SimDataStorageEventListener *listener)
    {
        auto lstnr = std::find(Listeners.begin(), Listeners.end(), listener);

        if (lstnr != Listeners.end())
        {
            return;
        }

        Listeners.push_back(listener);
    }

    void SimDataStorageEntry::RemoveListener(SimDataStorageEventListener *listener)
    {
        Listeners.erase(std::find(Listeners.begin(), Listeners.end(), listener));
    }

    SimFrames::Core::OperationResult SimDataStorageEntry::Read(bool *dest)
    {
        if (Object.GetType() != SimDataObjectType::Boolean)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            Object.Read(dest, sizeof(*dest));
        }

        for (auto it : Listeners) { it->OnObjectRead(*this); }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorageEntry::Read(int64_t *dest)
    {
        if (Object.GetType() != SimDataObjectType::Integer)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            Object.Read(dest, sizeof(*dest));
        }

        for (auto it : Listeners) { it->OnObjectRead(*this); }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorageEntry::Read(double *dest)
    {
        if (Object.GetType() != SimDataObjectType::Decimal)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            Object.Read(dest, sizeof(*dest));
        }

        for (auto it : Listeners) { it->OnObjectRead(*this); }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorageEntry::Write(bool src)
    {
        if (Object.GetType() != SimDataObjectType::Boolean)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            Object.Write(&src, sizeof(src));
        }

        for (auto it : Listeners) { it->OnObjectWrite(*this); }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorageEntry::Write(int64_t src)
    {
        if (Object.GetType() != SimDataObjectType::Integer)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            Object.Write(&src, sizeof(src));
        }

        for (auto it : Listeners) { it->OnObjectWrite(*this); }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorageEntry::Write(double src)
    {
        if (Object.GetType() != SimDataObjectType::Decimal)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        {
            std::lock_guard<std::mutex> lk(Lock);
            Object.Write(&src, sizeof(src));
        }

        for (auto it : Listeners) { it->OnObjectWrite(*this); }

        return SimFrames::Core::OperationResult::Success;
    }

    SimDataStorage::SimDataStorage(){};

    SimDataStorage::~SimDataStorage(){};

    SimFrames::Core::OperationResult SimDataStorage::Add(std::string key, bool defaultValue)
    {
        std::lock_guard<std::mutex> lk(Lock);
        auto                        it = Entries.find(key);

        if (it != Entries.end())
        {
            return SimFrames::Core::OperationResult::Error;
        }

        Entries[key] = std::make_shared<SimDataStorageEntry>(defaultValue);

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorage::Add(std::string key, int64_t defaultValue)
    {
        std::lock_guard<std::mutex> lk(Lock);
        auto                        it = Entries.find(key);

        if (it != Entries.end())
        {
            return SimFrames::Core::OperationResult::Error;
        }

        Entries[key] = std::make_shared<SimDataStorageEntry>(defaultValue);

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimDataStorage::Add(std::string key, double defaultValue)
    {
        std::lock_guard<std::mutex> lk(Lock);
        auto                        it = Entries.find(key);

        if (it != Entries.end())
        {
            return SimFrames::Core::OperationResult::Error;
        }

        Entries[key] = std::make_shared<SimDataStorageEntry>(defaultValue);

        return SimFrames::Core::OperationResult::Success;
    }

    RSimDataStorageEntry SimDataStorage::Find(std::string key)
    {
        auto it = Entries.find(key);

        if (it != Entries.end())
        {
            return it->second;
        }

        return nullptr;
    }

}}