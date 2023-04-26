#include "syscall.h"

#define IN_CONS 0
#define OUT_CONS 1

int main() {
    char *console;
    int charCount;

    // testing read and write file on console
    PrintString("\n----Read from console: ");
    charCount = ReadFile(console, 20, IN_CONS);
    
    PrintString("\n----Write to console: ");
    charCount = WriteFile(console, 20, OUT_CONS);

    PrintString("\n----Number of character: ");
    PrintInt(charCount);

    Halt();
}