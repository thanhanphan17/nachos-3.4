#include "syscall.h"

#define IN_CONS 0
#define OUT_CONS 1
#define MAX_LEN 20

int main() {
    char *console;
    int charCount;
    int i = 0;

    // testing read and write file on console
    PrintString("\n----Read from console: ");
    charCount = Read_File(console, MAX_LEN, IN_CONS);

    PrintString("\n----Write to console: ");
    Write_File(console, charCount, OUT_CONS);

    PrintString("\n----Number of character: ");
    PrintInt(charCount);

    Halt();
}