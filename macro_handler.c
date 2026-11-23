#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "preprocessor.h"

// Array to store macro definitions
static struct Macro macros[MAX_MACROS];

// Number of macros stored
static int macro_count = 0;

// Function to store a macro

void store_macro(const char *name, const char *parameter,
                 const char *value, int is_function)
{
    // Check whether macro storage has available space
    if (macro_count < MAX_MACROS)
    {
        // Store macro name
        snprintf(macros[macro_count].name, MAX_NAME, "%s", name);

        // Store parameter name
        snprintf(macros[macro_count].parameter, MAX_NAME, "%s", parameter);

        // Store replacement value
        snprintf(macros[macro_count].value, MAX_VALUE, "%s", value);

        // Store macro type
        macros[macro_count].is_function = is_function;

        // Increase macro count
        macro_count++;
    }
}
int process_macros(FILE *fp_in, FILE *fp_out)
{
    char line[1024];
    char name[MAX_NAME];
    char parameter[MAX_NAME];
    char value[MAX_VALUE];

    char *p;
    int i;

    while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        p = line;

        // Skip leading spaces
        while (isspace((unsigned char)*p))
            p++;

        // Check for #define
        if (strncmp(p, "#define", 7) == 0)
        {
            p += 7;

            // Skip spaces after #define
            while (isspace((unsigned char)*p))
                p++;

            // Extract macro name
            i = 0;

            while (isalnum((unsigned char)*p) || *p == '_')
            {
                if (i < MAX_NAME - 1)
                    name[i++] = *p;

                p++;
            }

            name[i] = '\0';

            // Check for function-like macro
            if (*p == '(')
            {
                p++;

                i = 0;

                // Extract parameter
                while (*p != ')' && *p != '\0')
                {
                    if (!isspace((unsigned char)*p) && i < MAX_NAME - 1)
                        parameter[i++] = *p;

                    p++;
                }

                parameter[i] = '\0';

                if (*p == ')')
                    p++;

                // Skip spaces before replacement value
                while (isspace((unsigned char)*p))
                    p++;

                snprintf(value, MAX_VALUE, "%s", p);

                value[strcspn(value, "\n")] = '\0';
                // Store function-like macro
                store_macro(name, parameter, value, 1);
            }
            else
            {
                parameter[0] = '\0';

                // Skip spaces before replacement value
                while (isspace((unsigned char)*p))
                    p++;

                snprintf(value, MAX_VALUE, "%s", p);
                value[strcspn(value, "\n")] = '\0';

                // Store object-like macro
                store_macro(name, parameter, value, 0);
            }
        }
        else
        {
            // Replace macro names in normal code
            replace_macros(line, fp_out);
        }
    }

    return 0;
}

const char *find_macro(const char *name)
{
    int i;

    // Search through stored macros
    for (i = 0; i < macro_count; i++)
    {
        // Compare the macro name
        if (strcmp(macros[i].name, name) == 0)
        {
            return macros[i].value;
        }
    }

    // Macro not found
    return NULL;
}
// Replace the macro parameter with the actual argument
void expand_function_macro(const struct Macro *macro,
                           const char *argument, FILE *fp_out)
{
    int i = 0;
    char word[MAX_NAME];
    int j;

    // Read the replacement value
    while (macro->value[i] != '\0')
    {
        // Check for an identifier
        if (isalpha((unsigned char)macro->value[i]) ||
            macro->value[i] == '_')
        {
            j = 0;

            // Extract the complete identifier
            while (isalnum((unsigned char)macro->value[i]) ||
                   macro->value[i] == '_')
            {
                if (j < MAX_NAME - 1)
                    word[j++] = macro->value[i];

                i++;
            }

            word[j] = '\0';

            // Replace parameter with actual argument
            if (strcmp(word, macro->parameter) == 0)
            {
                fputs(argument, fp_out);
            }
            else
            {
                fputs(word, fp_out);
            }
        }
        else
        {
            fputc(macro->value[i], fp_out);
            i++;
        }
    }
}

void replace_macros(const char *line, FILE *fp_out)
{
    int i = 0;
    int j;
    int k;
    int pos;
    int depth;
    int arg_len;
    int found;

    char word[MAX_NAME];
    char argument[MAX_VALUE];

    int state = 0;
    int escaped = 0;

    while (line[i] != '\0')
    {
        // Inside a string literal
        if (state == 1)
        {
            fputc(line[i], fp_out);

            if (escaped)
                escaped = 0;
            else if (line[i] == '\\')
                escaped = 1;
            else if (line[i] == '"')
                state = 0;

            i++;
        }

        // Inside a character literal
        else if (state == 2)
        {
            fputc(line[i], fp_out);

            if (escaped)
                escaped = 0;
            else if (line[i] == '\\')
                escaped = 1;
            else if (line[i] == '\'')
                state = 0;

            i++;
        }

        // Detect string literal
        else if (line[i] == '"')
        {
            state = 1;
            fputc(line[i], fp_out);
            i++;
        }

        // Detect character literal
        else if (line[i] == '\'')
        {
            state = 2;
            fputc(line[i], fp_out);
            i++;
        }

        // Identify macro name
        else if (isalpha((unsigned char)line[i]) || line[i] == '_')
        {
            j = 0;

            while (isalnum((unsigned char)line[i]) || line[i] == '_')
            {
                if (j < MAX_NAME - 1)
                    word[j++] = line[i];

                i++;
            }

            word[j] = '\0';

            found = -1;

            // Search for the macro
            for (k = 0; k < macro_count; k++)
            {
                if (strcmp(macros[k].name, word) == 0)
                {
                    found = k;
                    break;
                }
            }

            if (found == -1)
            {
                fputs(word, fp_out);
            }

            // Object-like macro
            else if (macros[found].is_function == 0)
            {
                fputs(macros[found].value, fp_out);
            }

            // Function-like macro
            else
            {
                pos = i;

                // Skip spaces before opening parenthesis
                while (isspace((unsigned char)line[pos]))
                    pos++;

                if (line[pos] == '(')
                {
                    pos++;
                    depth = 0;
                    arg_len = 0;

                    // Extract macro argument
                    while (line[pos] != '\0')
                    {
                        if (line[pos] == '(')
                            depth++;

                        else if (line[pos] == ')')
                        {
                            if (depth == 0)
                                break;

                            depth--;
                        }

                        if (arg_len < MAX_VALUE - 1)
                            argument[arg_len++] = line[pos];

                        pos++;
                    }

                    argument[arg_len] = '\0';

                    if (line[pos] == ')')
                    {
                        // Expand function-like macro
                        expand_function_macro(&macros[found],
                                              argument, fp_out);

                        i = pos + 1;
                    }
                    else
                    {
                        fputs(word, fp_out);
                    }
                }
                else
                {
                    fputs(word, fp_out);
                }
            }
        }

        else
        {
            fputc(line[i], fp_out);
            i++;
        }
    }
}




