#!/bin/bash

python3 load.py
echo 'Load done'
echo '================================'
cd firmware
make clean
make all
echo 'make done'
echo '================================'
cd .. 
litex_term /dev/ttyUSB1 --kernel firmware/firmware.bin
echo '================================'
echo 'Press RESET button'
