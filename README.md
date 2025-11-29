# bankers_algorithm

## About this program

This is a program called banker that when compiled and ran will read the allocation, max, available, and request matrices/vectors from a file, which is part of its command line argument
and echo those values out as well as do computations to determine need matrix and available vector after determining safe state and whether a request can be granted

## Compiling this program

You must use a C compiler to compile this program (it doesn't matter which):

```bash
clang -o banker banker.c safebankalgo.c rralgo.c
```

for gcc users:

```bash
gcc -o banker banker.c safebankalgo.c rralgo.c
```

alternatively a makefile has been provided:

```bash
make
```

## Running this program

Using s1.txt or a similar file for running this program normally:

```bash
./banker s1.txt
```

## Removing the program

To remove the program simply run:

```bash
rm banker
```

or if using the makefile:

```bash
make clean
```
