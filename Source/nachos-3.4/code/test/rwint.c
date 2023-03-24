// Read and write int test file

#include "syscall.h"
#include "copyright.h"


int main() {
    int a;
    
    PrintString("Enter an interger number: ");
    a = ReadInt();

    PrintString("Your number is: ");
    PrintInt(a);
}