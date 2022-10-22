#ifndef SIM_DATA_OBJECT_H_
#define SIM_DATA_OBJECT_H_

#include <Core/SimCommon.h>

namespace SimFrames { namespace Data {

    enum SimDataObjectType
    {
        Boolean,
        Integer,
        Decimal,
    };

    class SimDataObject
    {
    private:
        SimDataObjectType ValueType;
        size_t            ValueSize;
        void             *Value;

#if 0
        
        bool              BooleanValue;
        int64_t           IntegerValue;
        double            DecimalValue;
#endif

    public:
        SimDataObject(bool defaultValue);
        SimDataObject(int64_t defaultValue);
        SimDataObject(double defaultValue);
        ~SimDataObject();

        SimDataObjectType                GetType();
        size_t                           GetSize();
        SimFrames::Core::OperationResult Read(void *dest, size_t maxSize);
        SimFrames::Core::OperationResult Write(void *src, size_t maxSize);
    };

}}

#endif /* SIM_DATA_OBJECT_H_ */