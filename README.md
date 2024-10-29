# trivial-vm

My attempt at replicating the VM design as shown by Dr. Jonas Birch in [his video](https://www.youtube.com/watch?v=vymrj-2YD64)

The VM is capable of executing an esoteric assembly language that currently boasts four 16-bit registers `ax, bx, cx, dx`, in addition to 64KB addressable memory and a whoppingly incredible instruction set of three instructions: `mov`, `nop` and `hlt`.

Conveniently, this VM features variable argument length and a modular, extensible design that supports more instructions and additional error codes.

Codewise, this VM makes use of C structs to model different VM components including CPU, Registers, Instructions, Opcodes, Args and Memory; following the structure initially set by Dr. Birch:
```
/*
 * 16-bit VM
 * AX
 * BX
 * CX
 * DX
 * SP: stack pointer
 * IP: instruction pointer
 * 65KB memory
 *
 * Future work:
 * (Serial COM port)
 * (Floppy drive)
 *
*/
```

## usage

Compiled using the provided `compile.bat`:
```sh
C:\> .\compile.bat
Compiling into 'vm.exe'...
Compiled successfully.
```

Run `vm.exe`:
```sh
C:\> .\vm.exe
vm  = 0000021CD61A1FB0 (sz: 4366)
prog  = 0000021CD61A1FBC
ax = 0000
executing program on vm...
System halted
ax = 0005
01 05 00 02 03 00 00 00 00
```

The above is a test run of the following program:
```
01 05 00 02 03 00 00 00 00
```
which translates to:
```c
// 0x01     opcode: mov arg1 to ax
// 0x05                 arg1
// 0x00                 arg2
// 0x02     opcode: nop
// 0x03     opcode: hlt
```

## future work
- Implement IO/serial communication
- More advanced VM, perhaps *tiny-vm* :)
