// Read and write char test file

#include "syscall.h"

int main() {
    char c;
    
    PrintString("Enter a character: ");
    c = ReadChar();

    PrintString("Your character is: ");
    PrintChar(c);
    
    Halt();
}