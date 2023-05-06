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
#include "directory.h"

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

void IncreaseProgramCounter() {
    machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));

    machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));

    machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg) + 4);
}

char *User2System(int virtAddr, int limit) {
    int i;  // index
    int oneChar;
    char *kernelBuf = NULL;

    kernelBuf = new char[limit + 1];  // need for terminal string

    if (kernelBuf == NULL) return kernelBuf;

    memset(kernelBuf, 0, limit + 1);

    // printf("\n Filename u2s:");
    for (i = 0; i < limit; i++) {
        machine->ReadMem(virtAddr + i, 1, &oneChar);
        kernelBuf[i] = (char)oneChar;
        // printf("%c",kernelBuf[i]);
        if (oneChar == 0) break;
    }

    return kernelBuf;
}

int System2User(int virtAddr, int len, char *buffer) {
    if (len < 0) return -1;

    if (len == 0) return len;

    int i = 0;
    int oneChar = 0;
    do {
        oneChar = (int)buffer[i];
        machine->WriteMem(virtAddr + i, 1, oneChar);
        i++;
    } while (i < len && oneChar != 0);

    return i;
}

void HaltHandler() {
    DEBUG('a', "Shutdown, initiated by user program!");
    printf("\n\nShutdown, initiated by user program!");
    interrupt->Halt();
}

void ReadIntHandler() {
    DEBUG('a', "Read integer number from console.\n");

    // Use a fixed-size buffer on the stack
    char buffer[INT_LEN];

    int length = gSynchConsole->Read(buffer, INT_LEN);
    int result = 0, index = 0;

    bool valid = true;  // check if input is a valid number

    if (buffer[index] == '-') {
        // If the first character is '-', increment the index and set the sign
        index++;

        // input only contains '-'
        if (length == 1) {
            machine->WriteRegister(2, 0);
            printf("\nYour input is not an integer number!\n");
            valid = false;
        }
    }

    while (index < length) {
        if (buffer[index] >= '0' && buffer[index] <= '9') {
            // If the character is a digit, add it to the result
            result = result * 10 + (buffer[index] - '0');
        } else {
            machine->WriteRegister(2, 0);
            printf("\nYour input is not an integer number!\n");
            valid = false;

            break;
        }

        index++;
    }

    // Multiply the result by -1 if the sign is negative
    if (buffer[0] == '-') {
        result *= -1;
    }

    if (valid) {
        machine->WriteRegister(2, result);
    }
}

void PrintIntHandler() {
    int n = machine->ReadRegister(4);
    bool negative = false;

    if (n < 0) {
        negative = true;
        n = -n;
    }

    char s[INT_LEN];
    int i = 0;

    do {
        s[i++] = n % 10 + '0';
    } while (n /= 10);

    if (negative) {
        s[i++] = '-';
    }

    for (int j = i - 1; j >= 0; j--) {
        gSynchConsole->Write(&s[j], 1);
    }
}

void ReadCharHandler() {
    char buffer[1];
    int length = gSynchConsole->Read(buffer, 1);

    if (length != 1) {
        printf("\nError occurred!\n");
        return;
    }

    machine->WriteRegister(2, buffer[0]);
}

void PrintCharHandler() {
    char c = (char)machine->ReadRegister(4);
    gSynchConsole->Write(&c, 1);
}

void ReadStringHandler() {
    int virtualAddress = machine->ReadRegister(4);
    int length = machine->ReadRegister(5);
    char *buffer = new char[length + 1];

    gSynchConsole->Read(buffer, length);
    System2User(virtualAddress, length, buffer);

    delete[] buffer;
}

void PrintStringHandler() {
    int virtualAddress = machine->ReadRegister(4);
    char *buffer = User2System(virtualAddress, MAX_SIZE);
    int length = 0;
    while (buffer[length] != '\0') {
        ++length;
    }

    gSynchConsole->Write(buffer, length + 1);
}

void CreateFileHandler() {
    /*load file name from user to kernel*/
    int name = machine->ReadRegister(4);
    char s[FileNameMaxLen+1] = {0};
    for (int i = 0; i < FileNameMaxLen; ++i) {
        int oneChar = 0;
        machine->ReadMem(name+i, 1, &oneChar);
        if (oneChar == 0) break;
        s[i] = (char)oneChar;
    }
    /*create new file*/
    bool chk = fileSystem->Create(s, 0);
    if (chk) machine->WriteRegister(2, 0);
    else machine->WriteRegister(2, -1);
}

void OpenFileHandler() {
    /*load file name from user to kernel*/
    int name = machine->ReadRegister(4);
    char s[FileNameMaxLen+1] = {0};
    for (int j = 0; j < FileNameMaxLen; ++j) {
        int oneChar = 0;
        machine->ReadMem(name+j, 1, &oneChar);
        if (oneChar == 0) break;
        s[j] = (char)oneChar;
    }
    /*open file*/
    OpenFile* pFile = fileSystem->Open(s);
    if (pFile == NULL) {
        machine->WriteRegister(2, -1);
        return;
    }
    /*load file type from user to kernel*/
    int type = machine->ReadRegister(5);
    /*add open file to file table*/
    int ret = gFTable->Open(pFile, type);
    if (ret == -1) {
        delete pFile;
        machine->WriteRegister(2, -1);
        return;
    }
    else {
        machine->WriteRegister(2, ret+2);
        return;
    }
}

void CloseFileHandler() {
    /*load fid from user to kernel*/
    int fid = machine->ReadRegister(4);
    /*fid: console input & output*/
    if (fid == ConsoleInput || fid == ConsoleOutput) {
        machine->WriteRegister(2, -1);
        return;
    }
    /*fid: not console input & output*/
    fid -= 2;
    int ret = gFTable->Close(fid);
    machine->WriteRegister(2, ret);
}

void ReadFileHandler() {
      int buffer = machine->ReadRegister(4);
    int charcount = machine->ReadRegister(5);
    int fid = machine->ReadRegister(6);
    if (charcount < 0) {
        machine->WriteRegister(2, -1);
        return;
    }
    int i = 0;
    if (fid == ConsoleInput) {
        /*read from console input*/            
        while (i < charcount) {
            char oneChar = 0;
            int ret = gSynchConsole->Read(&oneChar,1);
            if (ret == -1) {
                machine->WriteRegister(2, -2);
                return;
            } else if (ret == 0) break; 
            machine->WriteMem(buffer + i, 1, (int)oneChar);
            ++i;
        }
        machine->WriteRegister(2, i);
        return;      
    }
    /*read from file*/
    fid -= 2;
    if (gFTable->getType(fid) == -1) {
        machine->WriteRegister(2, -1);
        return;
    }
    while (i < charcount) {
        char oneChar = 0;
        if (gFTable->ReadChar(oneChar, fid) == 0) break;
        machine->WriteMem(buffer + i, 1, (int)oneChar);
        ++i;
    }
    machine->WriteRegister(2, i);
}


void WriteFileHandler() {
    int buffer = machine->ReadRegister(4);
    int charcount = machine->ReadRegister(5);
    int fid = machine->ReadRegister(6);

    if (charcount < 0) {
        machine->WriteRegister(2, -1);
        return;
    }
    
    int i = 0;
    if (fid == ConsoleOutput) {            
        /*write to console output*/
        while (i < charcount) {
            int oneChar = 0;
            bool ret = machine->ReadMem(buffer + i, 1, &oneChar); 
            if (!ret) {
                machine->WriteRegister(2, -1);
                return;
            }
            char c = (char)oneChar;
            gSynchConsole->Write(&c,1);
            ++i;
        }
        machine->WriteRegister(2, i);
        return;      
    }

    /*write to file*/
    fid -= 2;
    if (gFTable->getType(fid) != 0) {
        machine->WriteRegister(2, -1);
        return;
    }
    while (i < charcount) {
        int oneChar = 0;
        bool ret = machine->ReadMem(buffer + i, 1, &oneChar); 
        if (!ret) {
            machine->WriteRegister(2, -1);
            return;
        }
        char c = (char)oneChar;
        gFTable->WriteChar(c, fid);
        ++i;
    }
    machine->WriteRegister(2, i);
}

void ExecHandler() {
    int name = machine->ReadRegister(4);
    if (name == 0) {
        machine->WriteRegister(2, -1);
        return;
    }
    /*load file name from user to kernel*/
    char s[FileNameMaxLen+1] = {0};
    for (int j = 0; j < FileNameMaxLen; ++j) {
        int oneChar = 0;
        if (machine->ReadMem(name+j, 1, &oneChar) == FALSE) {
            machine->WriteRegister(2, -1);
            return;
        }
        if (oneChar == 0) break;
        s[j] = (char)oneChar;
    }
    /*execute process*/
    int ret = pTab->ExecUpdate(s);
    machine->WriteRegister(2, ret);
}

void JoinHandler() {
    int id = machine->ReadRegister(4);  
    int res = pTab->JoinUpdate(id);

    machine->WriteRegister(2, res);
    return;
}

void ExitHandler() {
    int exitStatus = machine->ReadRegister(4);

    if (exitStatus != 0) {
        return;
    }

    int result = pTab->ExitUpdate(exitStatus);

    currentThread->FreeSpace();
    currentThread->Finish();

    machine->WriteRegister(2, result);
    return;
}

void CreateSemaphoreHandler() {
    int virtAddr = machine->ReadRegister(4); //Đọc địa chỉ “name” từ thanh ghi r4.
    int semval = machine->ReadRegister(5); //Đọc giá trị “semval” từ thanh ghi r5.

    char *name = User2System(virtAddr, MAX_SIZE);

    if (name == NULL) {
        DEBUG('a', "\nCan not create semaphore with null name");
        printf("\nCan not create semaphore with null name");
        machine->WriteRegister(2, -1);
        return;
    }

    int res = semTab->Create(name, semval);

    if (res == -1) {
        DEBUG('a', "\nCan not create semaphore (%s, %d)", name, &semval);
        printf("\nCan not create semaphore (%s, %d)", name, &semval);
        machine->WriteRegister(2, -1);
        delete[] name;
        return;
    }

    machine->WriteRegister(2, res);
    delete[] name;
    return;
}

void WaitHandler() {
    int virtAddr = machine->ReadRegister(4);

    char *name = User2System(virtAddr, MAX_SIZE);

    if (name == NULL) {
        DEBUG('a', "\n Not enough memory in System");
        printf("\n Not enough memory in System");
        machine->WriteRegister(2, -1);

        delete[] name;
        return;
    }

    int res = semTab->Wait(name);

    if (res == -1) {
        DEBUG('a', "\n This semaphore name not exits");
        printf("\n This semaphore name not exits!");
        machine->WriteRegister(2, -1);

        delete[] name;
        return;
    }

    delete[] name;
    machine->WriteRegister(2, res);
    return;
}

void SignalHandler() {
    int virtAddr = machine->ReadRegister(4);

    char *name = User2System(virtAddr, MAX_SIZE);

    if (name == NULL) {
        DEBUG('a', "\n Not enough memory in System");
        printf("\n Not enough memory in System");
        machine->WriteRegister(2, -1);

        delete[] name;
        return;
    }

    int res = semTab->Signal(name);

    if (res == -1) {
        DEBUG('a', "\n This semaphore name not exits!");
        printf("\n This semaphore name not exits!");
        machine->WriteRegister(2, -1);

        delete[] name;
        return;
    }

    delete[] name;
    machine->WriteRegister(2, res);
    return;
}

void GetPIDHandler() { machine->WriteRegister(2, currentThread->processID); }


void SeekHandler() {
    int pos = machine->ReadRegister(4);
    int id = machine->ReadRegister(5);

    if (id < 0 || id > 9) {
        printf("\nCan not seek.");
        machine->WriteRegister(2, -1);
        return;
    }

    if (fileSystem->openFile[id] == NULL) {
        printf("\nCan not seek because this file does not exits.");
        machine->WriteRegister(2, -1);
        return;
    }

    if (id == 0 || id == 1) {
        printf("\nCan not seek in console.");
        machine->WriteRegister(2, -1);
        return;
    }
    pos = (pos == -1) ? fileSystem->openFile[id]->Length() : pos;
    if (pos > fileSystem->openFile[id]->Length() || pos < 0) {
        printf("\nCan not seek to this position.");
        machine->WriteRegister(2, -1);
    } else {
        fileSystem->openFile[id]->Seek(pos);
        machine->WriteRegister(2, pos);
    }
    return;
}

// Exception handler
void ExceptionHandler(ExceptionType which) {
    int type = machine->ReadRegister(2);

    switch (which) {

        // Handle system call exceptions
        case SyscallException: {
            switch (type) {
                case SC_Halt:
                    HaltHandler();
                    break;

                case SC_ReadInt:
                    ReadIntHandler();
                    break;

                case SC_PrintInt:
                    PrintIntHandler();
                    break;

                case SC_ReadChar:
                    ReadCharHandler();
                    break;

                case SC_PrintChar:
                    PrintCharHandler();
                    break;

                case SC_ReadString:
                    ReadStringHandler();
                    break;

                case SC_PrintString:
                    PrintStringHandler();
                    break;

                case SC_CreateFile:
                    CreateFileHandler();
                    break;

                case SC_OpenFile:
                    OpenFileHandler();
                    break;

                case SC_CloseFile:
                    CloseFileHandler();
                    break;

                case SC_ReadFile:
                    ReadFileHandler();
                    break;

                case SC_WriteFile:
                    WriteFileHandler();
                    break;
                
                case SC_Exec:
                    ExecHandler();
                    break;
            
                case SC_Join:
                    JoinHandler();
                    break;
                
                case SC_Exit:
                    ExitHandler();
                    break;

                case SC_CreateSemaphore:
                    CreateSemaphoreHandler();
                    break;

                case SC_Wait:
                    WaitHandler();
                    break;
                
                case SC_Signal:
                    SignalHandler();
                    break;

                case SC_Seek:
                    SeekHandler();
                    break;

                case SC_GetPid:
                    GetPIDHandler();
                    break;
            }

            IncreaseProgramCounter();
            break;
        }

        // Handle exceptions in machine.h
        case NoException:
            return;

        case PageFaultException:
            DEBUG('a', "\nPageFaultException: No valid translation found!");
            printf("\n\nPageFaultException: No valid translation found!");
            interrupt->Halt();
            break;

        case ReadOnlyException:
            DEBUG('a',
                  "\nReadOnlyException: Write attempted to page marked "
                  "read-only!");
            printf(
                "\n\nReadOnlyException: Write attempted to page marked "
                "read-only!");
            interrupt->Halt();
            break;

        case BusErrorException:
            DEBUG('a',
                  "\nBusErrorException: Translation resulted in an invalid "
                  "physical address!");
            printf(
                "\n\nBusErrorException: Translation resulted in an invalid "
                "physical address!");
            interrupt->Halt();
            break;

        case AddressErrorException:
            DEBUG('a',
                  "\nAddressErrorException: Unaligned reference or one that "
                  "was beyond the end of the address space!");
            printf(
                "\n\nAddressErrorException: Unaligned reference or one that "
                "was beyond the end of the address space!");
            interrupt->Halt();
            break;

        case OverflowException:
            DEBUG('a', "\nOverflowException: Integer overflow in add or sub!");
            printf("\n\nOverflowException: Integer overflow in add or sub!");
            interrupt->Halt();
            break;

        case IllegalInstrException:
            DEBUG('a',
                  "\nIllegalInstrException: Unimplemented or reserved instr!");
            printf(
                "\n\nIllegalInstrException: Unimplemented or reserved instr!");
            interrupt->Halt();
            break;

        case NumExceptionTypes:
            DEBUG('a', "\nNumExceptionTypes: Num exeption types occurred!");
            printf("\n\nNum exeption types occurred!");
            interrupt->Halt();
            break;
    }
}
