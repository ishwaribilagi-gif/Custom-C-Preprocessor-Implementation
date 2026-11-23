#include <stdio.h>
#include "preprocessor.h"

int create_output_file(const char *input, const char *output)
{
    FILE *fp_in;
    FILE *fp_out;
    FILE *fp_temp;
    FILE *fp_included;

    // Open input file
    fp_in = fopen(input, "r");

    if (fp_in == NULL)
    {
        printf("Error: Unable to open input file\n");
        return -1;
    }

    // Create output file
    fp_out = fopen(output, "w");

    if (fp_out == NULL)
    {
        printf("Error: Unable to create output file\n");
        fclose(fp_in);
        return -1;
    }

    // Create temporary file for comment removal
    fp_temp = tmpfile();

    if (fp_temp == NULL)
    {
        printf("Error creating temporary file\n");
        fclose(fp_in);
        fclose(fp_out);
        return -1;
    }

    // Create temporary file for header expansion
    fp_included = tmpfile();

    if (fp_included == NULL)
    {
        printf("Error creating temporary file\n");
        fclose(fp_in);
        fclose(fp_out);
        fclose(fp_temp);
        return -1;
    }

    // Step 1: Remove comments
    remove_single_line_comments(fp_in, fp_temp);

    // Step 2: Process header inclusion
    rewind(fp_temp);

    if (process_file_includes(fp_temp, fp_included) != 0)
    {
        printf("Error: File inclusion failed\n");

        fclose(fp_in);
        fclose(fp_out);
        fclose(fp_temp);
        fclose(fp_included);

        remove(output);
        return -1;
    }

    // Step 3: Process macro substitution
    rewind(fp_included);

    if (process_macros(fp_included, fp_out) != 0)
    {
        printf("Error: Macro processing failed\n");

        fclose(fp_in);
        fclose(fp_out);
        fclose(fp_temp);
        fclose(fp_included);

        remove(output);
        return -1;
    }

    // Close all files
    fclose(fp_in);
    fclose(fp_out);
    fclose(fp_temp);
    fclose(fp_included);

    return 0;
}
