#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"

int main(int argc, char *argv[])
{
    char *output;

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./mypreprocessor <inputfile.c>\n");
        return 1;
    }

    // Find input filename length
    output = malloc(strlen(argv[1]) + 3);

    if (output == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Copy input filename
    strcpy(output, argv[1]);

    // Replace .c extension with .i
    char *extension = strrchr(output, '.');

    if (extension == NULL || strchr(extension, '/') != NULL)
    {
        printf("Error: Invalid input filename\n");
        free(output);
        return 1;
    }

    strcpy(extension, ".i");

    // Create output file
    if (create_output_file(argv[1], output) != 0)
    {
        free(output);
        return 1;
    }

    printf("Preprocessing setup completed!\n");
    printf("Output file: %s\n", output);

    free(output);

    return 0;
}
