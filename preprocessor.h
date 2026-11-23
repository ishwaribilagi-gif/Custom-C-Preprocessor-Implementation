#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <stdio.h>

#define MAX_MACROS 100
#define MAX_NAME 100
#define MAX_VALUE 256

// Structure to store macro information
struct Macro
{
    char name[MAX_NAME];
    char parameter[MAX_NAME];
    char value[MAX_VALUE];
    int is_function;
};



int create_output_file(const char *input, const char *output);
int remove_single_line_comments(FILE *fp_in, FILE *fp_out);
int include_file(const char *filename, FILE *fp_out);
int process_file_includes(FILE *fp_in, FILE *fp_out);
int process_macros(FILE *fp_in, FILE *fp_out);
const char *find_macro(const char *name);
void store_macro(const char *name, const char *parameter,const char *value, int is_function);
void replace_macros(const char *line, FILE *fp_out);

#endif
