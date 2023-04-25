// create, read and write file test file

#include "syscall.h"

#define IN_CONS 0
#define OUT_CONS 1

#define READ_ONLY 0
#define READ_WRITE 1

#define CONTENT_LEN 50

int main() {
    char *console;
    char *fileName;
    char *inputContent;
    char *outputContent;
    int fileID;
    int charCount;

    // testing read and write file on console
    PrintString("\n----Read from console: ");
    charCount = ReadFile(console, 20, IN_CONS);
    
    PrintString("\n----Write to console: ");
    charCount = WriteFile(console, 20, OUT_CONS);

    PrintString("\n----Number of character: ");
    PrintInt(charCount);

    // create file
    PrintString("\n----Enter creating filename: ");
    ReadString(fileName, FILE_NAME_LEN);
    CreateFile(fileName);

    // open created file
    fileID = OpenFile(fileName, READ_WRITE);
    if (fileID == -1) {
        return 0;
    }

    // input file content
    PrintString("\n----Enter content: ");
    ReadString(inputContent, CONTENT_LEN);

    // reading and writing with created file
    charCount = WriteFile(inputContent, CONTENT_LEN, fileID);

    PrintString("\n----Number of character: ");
    PrintInt(charCount);


    PrintString("\n----Read from file: ");
    charCount = ReadFile(outputContent, CONTENT_LEN, fileID);
    PrintString(outputContent);

    PrintString("\n----Number of character: ");
    PrintInt(charCount);

    // close file
    charCount = CloseFile(fileID);

    return 0;
    // Halt();
}