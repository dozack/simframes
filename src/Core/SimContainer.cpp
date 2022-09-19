#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimContainerMap::SimContainerMap(uint32_t column, uint32_t colSpan, uint32_t row,
                                     uint32_t rowSpan)
        : ColumnIndex(column)
        , ColumnSpan(colSpan)
        , RowIndex(row)
        , RowSpan(rowSpan)
    {}

    SimContainer::SimContainer(SimFrames::Core::SimGrid&         grid,
                               SimFrames::Core::SimContainerMap& map)
        : Grid(grid)
        , Map(map)
        , Lock(grid.Tab.Window.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        Obj = lv_obj_create(Grid.Obj);
        lv_obj_set_grid_cell(Obj, LV_GRID_ALIGN_STRETCH, Map.ColumnIndex, Map.ColumnSpan,
                             LV_GRID_ALIGN_STRETCH, Map.RowIndex, Map.RowSpan);
        lv_obj_set_flex_flow(Obj, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scroll_snap_y(Obj, LV_SCROLL_SNAP_START);
        lv_obj_set_scrollbar_mode(Obj, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_flag(Obj, LV_OBJ_FLAG_SCROLL_ONE);
    }

}}