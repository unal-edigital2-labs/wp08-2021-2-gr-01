PACKAGES=libc libcompiler_rt libbase libfatfs liblitespi liblitedram libliteeth liblitesdcard liblitesata bios
PACKAGE_DIRS=/tools/Litex/litex/litex/soc/software/libc /tools/Litex/litex/litex/soc/software/libcompiler_rt /tools/Litex/litex/litex/soc/software/libbase /tools/Litex/litex/litex/soc/software/libfatfs /tools/Litex/litex/litex/soc/software/liblitespi /tools/Litex/litex/litex/soc/software/liblitedram /tools/Litex/litex/litex/soc/software/libliteeth /tools/Litex/litex/litex/soc/software/liblitesdcard /tools/Litex/litex/litex/soc/software/liblitesata /tools/Litex/litex/litex/soc/software/bios
LIBS=libc libcompiler_rt libbase libfatfs liblitespi liblitedram libliteeth liblitesdcard liblitesata
TRIPLE=riscv64-unknown-elf
CPU=picorv32
CPUFAMILY=riscv
CPUFLAGS=-mno-save-restore -march=rv32im     -mabi=ilp32 -D__picorv32__ 
CPUENDIANNESS=little
CLANG=0
CPU_DIRECTORY=/tools/Litex/litex/litex/soc/cores/cpu/picorv32
SOC_DIRECTORY=/tools/Litex/litex/litex/soc
PICOLIBC_DIRECTORY=/tools/Litex/pythondata-software-picolibc/pythondata_software_picolibc/data
COMPILER_RT_DIRECTORY=/tools/Litex/pythondata-software-compiler_rt/pythondata_software_compiler_rt/data
export BUILDINC_DIRECTORY
BUILDINC_DIRECTORY=/home/diego_sanchez/Dokumente/GitHub/wp04-2021-2-gr-01/SoC_project/build/nexys4ddr/software/include
LIBC_DIRECTORY=/tools/Litex/litex/litex/soc/software/libc
LIBCOMPILER_RT_DIRECTORY=/tools/Litex/litex/litex/soc/software/libcompiler_rt
LIBBASE_DIRECTORY=/tools/Litex/litex/litex/soc/software/libbase
LIBFATFS_DIRECTORY=/tools/Litex/litex/litex/soc/software/libfatfs
LIBLITESPI_DIRECTORY=/tools/Litex/litex/litex/soc/software/liblitespi
LIBLITEDRAM_DIRECTORY=/tools/Litex/litex/litex/soc/software/liblitedram
LIBLITEETH_DIRECTORY=/tools/Litex/litex/litex/soc/software/libliteeth
LIBLITESDCARD_DIRECTORY=/tools/Litex/litex/litex/soc/software/liblitesdcard
LIBLITESATA_DIRECTORY=/tools/Litex/litex/litex/soc/software/liblitesata
BIOS_DIRECTORY=/tools/Litex/litex/litex/soc/software/bios