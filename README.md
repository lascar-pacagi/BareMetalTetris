# Bare metal tetris: Tetris without OS

To compile and run:
```bash
make
make run
```
![tetris qemu](tetris_qemu.png)

To compile and debug:

```bash
make
make debug
```

and 

```bash
gdb
(gdb) file bin/kernel.sym
(gdb) target remote localhost:1234
(gdb) c
```
