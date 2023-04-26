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
    fileID = OpenFile(fileName, READ_WRITE);
    if (fileID == -1) {
        Halt();
    }

    // input file content
    PrintString("\n----Enter content to write into file: ");
    ReadString(inputContent, CONTENT_LEN);

    // reading and writing with created file
    charCount = WriteFile(inputContent, CONTENT_LEN, fileID);

    if (charCount == -1) {
        Halt();
    }

    PrintString("\n----Content in file: ");
    ReadFile(outputContent, CONTENT_LEN, fileID);
    PrintString(outputContent);
    PrintString("\n");

    PrintString("\n----Number of character: ");
    PrintInt(charCount);
    PrintString("\n");

    // close file
    charCount = CloseFile(fileID);

    Halt();
}