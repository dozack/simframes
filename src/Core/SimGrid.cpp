#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimGridLayout::SimGridLayout(const lv_coord_t *columns, const lv_coord_t *rows)
        : lvColumnMap(columns)
        , lvRowMap(rows)
    {}

    SimGrid::SimGrid(SimFrames::Core::SimTab &tab, SimFrames::Core::SimGridLayout &layout)
        : Layout(layout)
        , Tab(tab)
        , Lock(tab.Window.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        lvGrid = lv_obj_create(Tab.lvTab);
        lv_obj_align(lvGrid, LV_ALIGN_TOP_MID, 0, 5);
        lv_obj_set_size(lvGrid, LV_PCT(100), LV_PCT(100));
        lv_obj_set_layout(lvGrid, LV_LAYOUT_GRID);
        lv_obj_set_style_grid_column_dsc_array(lvGrid, Layout.lvColumnMap, 0);
        lv_obj_set_style_grid_row_dsc_array(lvGrid, Layout.lvRowMap, 0);
        lv_obj_clear_flag(lvGrid, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(lvGrid, LV_SCROLLBAR_MODE_OFF);
    }

}}