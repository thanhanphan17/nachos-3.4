// Read and write string test file

#include "syscall.h"

int main() {
    char* buffer;
    
    PrintString("Enter a string maximum 10 characters: ");
    ReadString(buffer, 10);

    PrintString("Your string is: ");
    PrintString(buffer);
    
    Halt();
}