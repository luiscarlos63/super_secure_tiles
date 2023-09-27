create_pblock pblock_RP_1
add_cells_to_pblock [get_pblocks pblock_RP_1] [get_cells -quiet [list design_1_i/RP_1]]
resize_pblock [get_pblocks pblock_RP_1] -add {SLICE_X29Y120:SLICE_X43Y149}
resize_pblock [get_pblocks pblock_RP_1] -add {CFGIO_SITE_X0Y0:CFGIO_SITE_X0Y0}
resize_pblock [get_pblocks pblock_RP_1] -add {DSP48E2_X3Y48:DSP48E2_X4Y59}
resize_pblock [get_pblocks pblock_RP_1] -add {RAMB18_X3Y48:RAMB18_X4Y59}
resize_pblock [get_pblocks pblock_RP_1] -add {RAMB36_X3Y24:RAMB36_X4Y29}
set_property SNAPPING_MODE ON [get_pblocks pblock_RP_1]
create_pblock pblock_RP_2
add_cells_to_pblock [get_pblocks pblock_RP_2] [get_cells -quiet [list design_1_i/RP_2]]
resize_pblock [get_pblocks pblock_RP_2] -add {SLICE_X15Y120:SLICE_X28Y149}
resize_pblock [get_pblocks pblock_RP_2] -add {DSP48E2_X1Y48:DSP48E2_X2Y59}
resize_pblock [get_pblocks pblock_RP_2] -add {RAMB18_X2Y48:RAMB18_X2Y59}
resize_pblock [get_pblocks pblock_RP_2] -add {RAMB36_X2Y24:RAMB36_X2Y29}
set_property SNAPPING_MODE ON [get_pblocks pblock_RP_2]
create_pblock pblock_RP_3
add_cells_to_pblock [get_pblocks pblock_RP_3] [get_cells -quiet [list design_1_i/RP_3]]
resize_pblock [get_pblocks pblock_RP_3] -add {SLICE_X29Y30:SLICE_X45Y59}
resize_pblock [get_pblocks pblock_RP_3] -add {DSP48E2_X3Y12:DSP48E2_X4Y23}
resize_pblock [get_pblocks pblock_RP_3] -add {RAMB18_X3Y12:RAMB18_X4Y23}
resize_pblock [get_pblocks pblock_RP_3] -add {RAMB36_X3Y6:RAMB36_X4Y11}
set_property SNAPPING_MODE ON [get_pblocks pblock_RP_3]

