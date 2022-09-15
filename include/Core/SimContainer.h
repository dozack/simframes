#ifndef SIM_CONTAINER_H_
#define SIM_CONTAINER_H_

#include <Core/SimGrid.h>

namespace SimFrames { namespace Core {

    class SimContainerMapping
    {
    public:
        uint32_t ColumnIndex;
        uint32_t ColumnSpan;
        uint32_t RowIndex;
        uint32_t RowSpan;

        SimContainerMapping(uint32_t column, uint32_t colSpan, uint32_t row, uint32_t rowSpan);
    };

    class SimContainer
    {
    public:
        SimFrames::Core::SimGrid& Grid;
        lv_obj_t*                 Obj;

        SimContainer(SimFrames::Core::SimGrid& grid, SimFrames::Core::SimContainerMapping& mapping);
    };

}}

#endif