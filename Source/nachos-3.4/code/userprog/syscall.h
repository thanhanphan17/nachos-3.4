/* syscalls.h
 * 	Nachos system call interface.  These are Nachos kernel operations
 * 	that can be invoked from user programs, by trapping to the kernel
 *	via the "syscall" instruction.
 *
 *	This file is included by user programs and by the Nachos kernel.
 *
 * Copyright (c) 1992-1993 The Regents of the University of California.
 * All rights reserved.  See copyright.h for copyright notice and limitation
 * of liability and disclaimer of warranty provisions.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "copyright.h"

/* system call codes -- used by the stubs to tell the kernel which system call
 * is being asked for
 */
#define SC_Halt 0

#define SC_Exit 1
#define SC_Exec 2
#define SC_Join 3
#define SC_Create 4

#define SC_Open 5
#define SC_Read 6
#define SC_Write 7
#define SC_Close 8
#define SC_Fork 9
#define SC_Yield 10

// Self-defined system call
#define SC_ReadInt 11
#define SC_PrintInt 12
#define SC_ReadChar 13
#define SC_PrintChar 14
#define SC_ReadString 15
#define SC_PrintString 16
#define SC_CreateFile 17
#define SC_OpenFile 18
#define SC_CloseFile 19
#define SC_ReadFile 20
#define SC_WriteFile 21

#define SC_CreateSemaphore 22
#define SC_Wait 23
#define SC_Singal 24

#define INT_LEN 11
#define FILE_NAME_LEN 255

#ifndef IN_ASM

/* The system call interface.  These are the operations the Nachos
 * kernel needs to support, to be able to run user programs.
 *
 * Each of these is invoked by a user program by simply calling the
 * procedure; an assembly language stub stuffs the system call code
 * into a register, and traps to the kernel.  The kernel procedures
 * are then invoked in the Nachos kernel, after appropriate error checking,
 * from the system call entry point in exception.cc.
 */

typedef int OpenFileId;

/* Stop Nachos, and print out performance stats */
void Halt();

/* Self-defined functions */
int ReadInt(); // Read integer from console

void PrintInt(int num); // Print integer number to console

char ReadChar(); // Read character from console

void PrintChar(char ch); // Print character number to console

void ReadString(char buffer[], int length); // Read string from console

void PrintString(char buffer[]); // Print string to console

int CreateFile(char *name); // Create new file

OpenFileId OpenFile(char* name, int type); // Open an existing file and return file's id

int CloseFile(OpenFileId id); // Close file with given id

int ReadFile(char *buffer, int charcount, OpenFileId id); // Read file

int WriteFile(char *buffer, int charcount, OpenFileId id); // Write file

/* Address space control operations: Exit, Exec, and Join */

/* This user program is done (status = 0 means exited normally). */
void Exit(int exitCode);

/* A unique identifier for an executing user program (address space) */
typedef int SpaceId;

/* Run the executable, stored in the Nachos file "name", and return the
 * address space identifier
 */
SpaceId Exec(char *name);

/* Only return once the the user program "id" has finished.
 * Return the exit status.
 */
int Join(SpaceId id);

int CreateSemaphore(char* name, int semval);

int Wait(char* name);

int Signal(char* name);

/* File system operations: Create, Open, Read, Write, Close
 * These functions are patterned after UNIX -- files represent
 * both files *and* hardware I/O devices.
 *
 * If this assignment is done before doing the file system assignment,
 * note that the Nachos file system has a stub implementation, which
 * will work for the purposes of testing out these routines.
 */

/* A unique identifier for an open Nachos file. */
// typedef int OpenFileId;

/* when an address space starts up, it has two open files, representing
 * keyboard input and display output (in UNIX terms, stdin and stdout).
 * Read and Write can be used directly on these, without first opening
 * the console device.
 */

#define ConsoleInput 0
#define ConsoleOutput 1

/* Create a Nachos file, with "name" */
// void Create(char *name);

/* Open the Nachos file "name", and return an "OpenFileId" that can
 * be used to read and write to the file.
 */
// OpenFileId Open(char* name, int type); // Open an existing file and return file's id
// OpenFileId Open(char *name);

/* Write "size" bytes from "buffer" to the open file. */
// void Write(char *buffer, int size, OpenFileId id);

/* Read "size" bytes from the open file into "buffer".
 * Return the number of bytes actually read -- if the open file isn't
 * long enough, or if it is an I/O device, and there aren't enough
 * characters to read, return whatever is available (for I/O devices,
 * you should always wait until you can return at least one character).
 */
// int Read(char *buffer, int size, OpenFileId id);

/* Close the file, we're done reading and writing to it. */
// int Close(OpenFileId id); // Close file with given id
// void Close(OpenFileId id);

// int Read(char *buffer, int charcount, OpenFileID id); // Read file

// int Write(char *buffer, int charcount, OpenFileID id); // Write file


/* User-level thread operations: Fork and Yield.  To allow multiple
 * threads to run within a user program.
 */

/* Fork a thread to run a procedure ("func") in the *same* address space
 * as the current thread.
 */
void Fork(void (*func)());

/* Yield the CPU to another runnable thread, whether in this address space
 * or not.
 */
void Yield();

#endif /* IN_ASM */

#endif /* SYSCALL_H */
