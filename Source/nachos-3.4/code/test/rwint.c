// Read and write int test file

#include "syscall.h"
#include "copyright.h"


int main() {
    int a, b;
    a = ReadInt();
    PrintInt(a);
    Halt();
}