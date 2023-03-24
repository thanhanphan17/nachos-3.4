// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

void IncreaseProgramCounter()
{
   	machine->WriteRegister(PrevPCReg, 
                            machine->ReadRegister(PCReg));

    machine->WriteRegister(PCReg, 
                            machine->ReadRegister(NextPCReg));

   	machine->WriteRegister(NextPCReg, 
                            machine->ReadRegister(NextPCReg) + 4);
}

void ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch (which)
    {
        // Handle exceptions in machine.h
        case NoException:
            return;

        case PageFaultException:
            DEBUG('a', "\nPageFaultException: No valid translation found!");
            printf("\n\nPageFaultException: No valid translation found!");
            interrupt->Halt();
            break;

        case ReadOnlyException:
            DEBUG('a', "\nReadOnlyException: Write attempted to page marked read-only!");
            printf("\n\nReadOnlyException: Write attempted to page marked read-only!");
            interrupt->Halt();
            break;

        case BusErrorException:
            DEBUG('a', "\nBusErrorException: Translation resulted in an invalid physical address!");
            printf("\n\nBusErrorException: Translation resulted in an invalid physical address!");
            interrupt->Halt();
            break;

        case AddressErrorException:            
            DEBUG('a', "\nAddressErrorException: Unaligned reference or one that was beyond the end of the address space!");
            printf("\n\nAddressErrorException: Unaligned reference or one that was beyond the end of the address space!");
            interrupt->Halt();
            break;

        case OverflowException:
            DEBUG('a', "\nOverflowException: Integer overflow in add or sub!");
            printf("\n\nOverflowException: Integer overflow in add or sub!");
            interrupt->Halt();
            break;

        case IllegalInstrException:
            DEBUG('a', "\nIllegalInstrException: Unimplemented or reserved instr!");
            printf("\n\nIllegalInstrException: Unimplemented or reserved instr!");
            interrupt->Halt();
            break;
        
        case NumExceptionTypes:
            DEBUG('a', "\nNumExceptionTypes: Num exeption types occurred!");
            printf("\n\nNum exeption types occurred!");
            interrupt->Halt();
            break;

        // Handle system call exceptions
        case SyscallException:
            switch (type)
            {
                case SC_Halt:
                    DEBUG('a', "Shutdown, initiated by user program\n");
                    interrupt->Halt();
                    break;
            }
            break;
    }
}
