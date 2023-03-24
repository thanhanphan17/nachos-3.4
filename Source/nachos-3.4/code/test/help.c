/*
    This program is used for showing team's information and
    instruction to run sort and ascii functions
*/

#include "syscall.h"

int main() {
    
    PrintString("\n\n");
    PrintString("\t+---------------------------------------------------------------+\n");
    PrintString("\t|                      OUT TEAM - EARLY BIRD                    |\n");
    PrintString("\t|                                                               |\n");
    PrintString("\t|--------------------+------------+-----------------------------|\n");
    PrintString("\t|      Name          |    ID      |           Email             |\n");
    PrintString("\t|--------------------|------------|-----------------------------|\n");
    PrintString("\t| Phan Thanh An      | 21127003   | ptan21@clc.fitus.edu.vn     |\n");
    PrintString("\t|--------------------|------------|-----------------------------|\n");
    PrintString("\t| Le Anh Thu         | 21127175   | lathu21@clc.fitus.edu.vn    |\n");
    PrintString("\t|--------------------|------------|-----------------------------|\n");
    PrintString("\t| Nguyen Hi Huu      | 21127294   | nhhuu21@clc.fitus.edu.vn    |\n");
    PrintString("\t|--------------------|------------|-----------------------------|\n");
    PrintString("\t| Nguyen Minh Dat    | 21127592   | nmdat21@clc.fitus.edu.vn    |\n");
    PrintString("\t|--------------------|------------|-----------------------------|\n");
    PrintString("\t| Huynh Duc Thien    | 21127693   | hdthien21@clc.fitus.edu.vn  |\n");
    PrintString("\t+--------------------+------------+-----------------------------+\n"); 

    PrintString("\n\n");

    PrintString("\t\t\t+---------------------------------+\n");
    PrintString("\t\t\t|           INSTRUCTION           +\n");
    PrintString("\t\t\t+---------------------------------+\n\n");
    
    PrintString("\t+-------------+-------------------------------------------------+\n");
    PrintString("\t| Program:    | ASCII                                           |\n");
    PrintString("\t|-------------|-------------------------------------------------|\n");
    PrintString("\t| Function:   | Print all characters in ASCII table             |\n");
    PrintString("\t|-------------|-------------------------------------------------|\n");
    PrintString("\t| How to use: | run ./userprog/nachos -rs 1023 -x ./test/ascii  |\n");
    PrintString("\t+-------------+-------------------------------------------------+\n");

    PrintString("\n\n");
    PrintString("\t+-------------+-------------------------------------------------+\n");
    PrintString("\t| Program:    | BUBBLE SORT                                     |\n");
    PrintString("\t|-------------|-------------------------------------------------|\n");
    PrintString("\t| Function:   | Sort a list of number type of intrger           |\n");
    PrintString("\t|-------------|-------------------------------------------------|\n");
    PrintString("\t| How to use: | run ./userprog/nachos -rs 1023 -x ./test/bbsort |\n");
    PrintString("\t+-------------+-------------------------------------------------+\n");

    Halt();
}