#include "syscall.h"

#define IN_CONS 0
#define OUT_CONS 1
#define MAX_LEN 20

int main() {
    char *fileName;

    // create file
    PrintString("\n----Enter filename to create: ");
    ReadString(fileName, MAX_LEN);
    Create_File(fileName);

    Halt();
}