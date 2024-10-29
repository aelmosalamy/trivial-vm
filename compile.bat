@echo off
echo Compiling into 'vm.exe'...

gcc -std=c2x -O3 -o vm.exe vm.c utils.c

echo Compiled successfully.
