#include "utils.h"
#include <iostream>

char *ReadFile(char *filename) {

    FILE *filePtr;
    char *buffer;
    long fileSize, count;
    int error;

    // Open the shader file for reading in text modee.
    filePtr = fopen(filename, "r");
    if (filePtr == NULL) {
        return 0;
    }

    // Go to the end of the file and get the size of the file.
    fseek(filePtr, 0, SEEK_END);
    fileSize = ftell(filePtr);

    // Initialize the buffer to read the shader source file into, adding 1 for an
    // extra null terminator.
    buffer = new char[fileSize + 1];

    // Return the file pointer back to the beginning of the file.
    fseek(filePtr, 0, SEEK_SET);

    // Read the shader text file into the buffer.
    count = fread(buffer, 1, fileSize, filePtr);
    if (count != fileSize) {
        return 0;
    }

    // Close the file.
    error = fclose(filePtr);
    if (error != 0) {
        return 0;
    }

    // Null terminate the buffer.
    buffer[fileSize] = '\0';

    return buffer;
}
