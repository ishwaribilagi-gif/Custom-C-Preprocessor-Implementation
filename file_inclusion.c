#include <stdio.h>
#include "preprocessor.h"

int include_file(const char *filename, FILE *fp_out)
{
    FILE *fp_header;
    int result;

    // Open the header file
    fp_header = fopen(filename, "r");

    if (fp_header == NULL)
    {
        printf("Error: Unable to open header file %s\n", filename);
        return -1;
    }

    // Process the header file contents
    // This also checks for nested #include directives
    result = process_file_includes(fp_header, fp_out);

    // Close the header file
    fclose(fp_header);

    return result;
}

int process_file_includes(FILE *fp_in, FILE *fp_out)
{
    char line[1024];
    char filename[256];

    // Read input file line by line
    while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        // Check for a quoted include directive
        if (sscanf(line, " #include \"%255[^\"]\"", filename) == 1)
        {
            // Copy the included file contents
            if (include_file(filename, fp_out) != 0)
            {
                return -1;
            }
        }
        else
        {
            // Copy the original line to output
            fputs(line, fp_out);
        }
    }


    return 0;
}
