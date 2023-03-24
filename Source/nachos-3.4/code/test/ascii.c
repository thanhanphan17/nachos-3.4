// This function is used for printing ascii table

#include "syscall.h"

int main() {
    char ch;
    int i = 0;

    for(i = 0; i <= 255; ++i) {
        PrintString("Code ");
        PrintInt(i);
        PrintString(": ");
        PrintChar(ch);
        PrintString("\n");
        ch++;
    }

    Halt();
}