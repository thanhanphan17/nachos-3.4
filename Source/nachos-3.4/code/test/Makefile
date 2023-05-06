# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort rwint rwchar rwstring help ascii bbsort rwfile createfile\
	 rwconsole process_a process_b test_exec_join main sinhvien voinuoc

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

# Add rwint to compile 
rwint.o: rwint.c
	$(CC) $(CFLAGS) -c rwint.c
rwint: rwint.o start.o
	$(LD) $(LDFLAGS) start.o rwint.o -o rwint.coff
	../bin/coff2noff rwint.coff rwint

# Add rwchar to compile 
rwchar.o: rwchar.c
	$(CC) $(CFLAGS) -c rwchar.c
rwchar: rwchar.o start.o
	$(LD) $(LDFLAGS) start.o rwchar.o -o rwchar.coff
	../bin/coff2noff rwchar.coff rwchar

# Add rwstring to compile 
rwstring.o: rwstring.c
	$(CC) $(CFLAGS) -c rwstring.c
rwstring: rwstring.o start.o
	$(LD) $(LDFLAGS) start.o rwstring.o -o rwstring.coff
	../bin/coff2noff rwstring.coff rwstring

# Add help to compile 
help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

# Add ascii to compile 
ascii.o: ascii.c
	$(CC) $(CFLAGS) -c ascii.c
ascii: ascii.o start.o
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff
	../bin/coff2noff ascii.coff ascii

# Add bbsort to compile 
bbsort.o: bbsort.c
	$(CC) $(CFLAGS) -c bbsort.c
bbsort: bbsort.o start.o
	$(LD) $(LDFLAGS) start.o bbsort.o -o bbsort.coff
	../bin/coff2noff bbsort.coff bbsort

# Add rwfile to compile 
rwfile.o: rwfile.c
	$(CC) $(CFLAGS) -c rwfile.c
rwfile: rwfile.o start.o
	$(LD) $(LDFLAGS) start.o rwfile.o -o rwfile.coff
	../bin/coff2noff rwfile.coff rwfile

# Add createfile to compile 
createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

# Add rwconsole to compile 
rwconsole.o: rwconsole.c
	$(CC) $(CFLAGS) -c rwconsole.c
rwconsole: rwconsole.o start.o
	$(LD) $(LDFLAGS) start.o rwconsole.o -o rwconsole.coff
	../bin/coff2noff rwconsole.coff rwconsole

# Add process_a to compile 
process_a.o: process_a.c
	$(CC) $(CFLAGS) -c process_a.c
process_a: process_a.o start.o
	$(LD) $(LDFLAGS) start.o process_a.o -o process_a.coff
	../bin/coff2noff process_a.coff process_a

# Add process_b to compile 
process_b.o: process_b.c
	$(CC) $(CFLAGS) -c process_b.c
process_b: process_b.o start.o
	$(LD) $(LDFLAGS) start.o process_b.o -o process_b.coff
	../bin/coff2noff process_b.coff process_b

# Add test_exec_join to compile 
test_exec_join.o: test_exec_join.c
	$(CC) $(CFLAGS) -c test_exec_join.c
test_exec_join: test_exec_join.o start.o
	$(LD) $(LDFLAGS) start.o test_exec_join.o -o test_exec_join.coff
	../bin/coff2noff test_exec_join.coff test_exec_join

# Add main to compile 
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
main: main.o start.o
	$(LD) $(LDFLAGS) start.o main.o -o main.coff
	../bin/coff2noff main.coff main

# Add sinhvien to compile 
sinhvien.o: sinhvien.c
	$(CC) $(CFLAGS) -c sinhvien.c
sinhvien: sinhvien.o start.o
	$(LD) $(LDFLAGS) start.o sinhvien.o -o sinhvien.coff
	../bin/coff2noff sinhvien.coff sinhvien

# Add voinuoc to compile 
voinuoc.o: voinuoc.c
	$(CC) $(CFLAGS) -c voinuoc.c
voinuoc: voinuoc.o start.o
	$(LD) $(LDFLAGS) start.o voinuoc.o -o voinuoc.coff
	../bin/coff2noff voinuoc.coff voinuoc