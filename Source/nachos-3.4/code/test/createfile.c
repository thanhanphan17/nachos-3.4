#include "syscall.h"

#define IN_CONS 0
#define OUT_CONS 1

int main() {
    char *fileName;

    // create file
    PrintString("\n----Enter filename to create: ");
    ReadString(fileName, 20);
    CreateFile(fileName);

    Halt();
}