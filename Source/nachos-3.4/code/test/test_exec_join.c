#include "syscall.h"

void main() {
    int process1ID, process2ID;
    PrintString("Test process execute and join...\n\n");
    process1ID = Exec("./test/process_a");
    process2ID = Exec("./test/process_b");

    Join(process1ID);
    Join(process2ID);
    
    PrintString("\n\n");
}
