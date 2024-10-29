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

Looking forward to *tiny-vm*!
