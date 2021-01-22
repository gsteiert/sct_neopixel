.\blhost.exe -p COM3 -- fill-memory 0x1c000 4 0xc1503051 
.\blhost.exe -p COM3 -- fill-memory 0x1c004 4 0x20000014
.\blhost.exe -p COM3 -- configure-memory 0x9 0x1c000
.\blhost.exe -p COM3 -- flash-image neo_demo.hex erase
