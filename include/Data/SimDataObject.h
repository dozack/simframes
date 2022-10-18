#ifndef SIM_DATA_OBJECT_H_
#define SIM_DATA_OBJECT_H_

#include <Core/SimCommon.h>

namespace SimFrames { namespace Data {

    enum SimDataObjectType
    {
        Boolean,
        Signed32,
        Unsigned32,
        String,
    };

    class ISimDataObject
    {
    public:
        ~ISimDataObject()                                                         = default;

        virtual SimDataObjectType GetType()                                       = 0;

        virtual size_t GetSize()                                                  = 0;

        virtual SimFrames::Core::OperationResult ReadRaw(void *dest, size_t size) = 0;

        virtual SimFrames::Core::OperationResult WriteRaw(void *src, size_t size) = 0;
    };

    template <typename T>
    class SimDataObject : public ISimDataObject
    {
    private:
        SimDataObjectType Type;
        T                 Value;

    public:
        SimDataObject(T value);

        SimDataObjectType GetType() override;

        size_t GetSize() override;

        SimFrames::Core::OperationResult ReadRaw(void *dest, size_t size) override;

        SimFrames::Core::OperationResult WriteRaw(void *src, size_t size) override;

        SimFrames::Core::OperationResult Read(T *dest);

        SimFrames::Core::OperationResult Write(T *src);
    };
}}

#endif /* SIM_DATA_OBJECT_H_ */