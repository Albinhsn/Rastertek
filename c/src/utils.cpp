#include "utils.h"
#include <iostream>
#include <string.h>

char *ReadFile(const char *filename) {

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
void OutputShaderErrorMessage(unsigned int shaderId, const char *shaderFilename) {

    long count;
    int error;
    FILE *filePtr;

    // Now retrieve the info log.
    char *infoLog = GetShaderInfoLog(shaderId);

    // Open a text file to write the error message to.
    filePtr = fopen("shader-error.txt", "w");
    if (filePtr == NULL) {
        std::cout << "Error opening shader error message output file." << std::endl;
        return;
    }

    // Write out the error message.
    count = fwrite(infoLog, sizeof(char), strlen(infoLog), filePtr);
    if (count != strlen(infoLog)) {
        std::cout << "Error writing shader error message output file." << std::endl;
        return;
    }

    // Close the file.
    error = fclose(filePtr);
    if (error != 0) {
        std::cout << "Error closing shader error message output file." << std::endl;
        return;
    }

    // Notify the user to check the text file for compile errors.
    std::cout << "Error compiling shader.  Check shader-error.txt for error message.  "
                 "Shader filename: "
              << shaderFilename << std::endl;

    return;
}

void OutputLinkerErrorMessage(unsigned int programId) {
    long count;
    FILE *filePtr;
    int error;

    char *infoLog = GetProgramInfoLog(programId);
    int logSize = strlen(infoLog);

    // Open a file to write the error message to.
    filePtr = fopen("linker-error.txt", "w");
    if (filePtr == NULL) {
        std::cout << "Error opening linker error message output file." << std::endl;
        return;
    }

    // Write out the error message.
    count = fwrite(infoLog, sizeof(char), logSize, filePtr);
    if (count != logSize) {
        std::cout << "Error writing linker error message output file." << std::endl;
        return;
    }

    // Close the file.
    error = fclose(filePtr);
    if (error != 0) {
        std::cout << "Error closing linker error message output file." << std::endl;
        return;
    }

    // Pop a message up on the screen to notify the user to check the text file
    // for linker errors.
    std::cout << "Error linking shader program.  Check linker-error.txt for message." << std::endl;

    return;
}
