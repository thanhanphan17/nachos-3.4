// create, read and write file test file

#include "syscall.h"

#define READ_ONLY 1
#define READ_WRITE 0

#define CONTENT_LEN 20

int main() {
    char *fileName;
    char *inputContent;
    char *outputContent;
    int fileID;
    int charCount;

    // create file
    PrintString("\n----Enter filename to read: ");
    ReadString(fileName, 20);

    // open created file
    fileID = Open_File(fileName, READ_WRITE);
    if (fileID == -1) {
        Halt();
    }

    // input file content
    PrintString("\n----Enter content to write: ");
    ReadString(inputContent, CONTENT_LEN);

    while (inputContent[charCount] != '\0') {
        charCount++;
    }

    // reading and writing with created file
    Write_File(inputContent, charCount, fileID);

    if (charCount == -1) {
        Halt();
    }

    PrintString("\n----Content in file: ");
    Read_File(outputContent, charCount, fileID);
    PrintString(outputContent);
    PrintString("\n");

    PrintString("\n----Number of character: ");
    PrintInt(charCount);
    PrintString("\n");

    // close file
    Close_File(fileID);

    Halt();
}