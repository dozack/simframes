#ifndef SIM_CONTAINER_H_
#define SIM_CONTAINER_H_

#include <Core/SimGrid.h>
#include <Core/SimLock.h>

namespace SimFrames { namespace Core {

    class SimContainerMap
    {
    public:
        uint32_t ColumnIndex;
        uint32_t ColumnSpan;
        uint32_t RowIndex;
        uint32_t RowSpan;

        SimContainerMap(uint32_t column, uint32_t colSpan, uint32_t row, uint32_t rowSpan);
    };

    class SimContainer
    {
    public:
        SimFrames::Core::SimGrid&         Grid;
        SimFrames::Core::SimContainerMap& Map;
        SimFrames::Core::SimLock&         Lock;
        lv_obj_t*                         lvContainer;

        SimContainer(SimFrames::Core::SimGrid& grid, SimFrames::Core::SimContainerMap& map);

        ~SimContainer(){};
    };

}}

#endif