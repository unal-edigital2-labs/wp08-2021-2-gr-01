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
echo '================================'
echo 'Press RESET Button'
litex_term /dev/ttyUSB1 --kernel firmware/firmware.bin
