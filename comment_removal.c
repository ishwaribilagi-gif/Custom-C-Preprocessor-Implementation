#include <stdio.h>
#include "preprocessor.h"

#define NORMAL 0
#define STRING 1
#define CHARACTER 2
#define SINGLE_COMMENT 3
#define MULTI_COMMENT 4

int remove_single_line_comments(FILE *fp_in, FILE *fp_out)
{
    int ch;
    int next;
    int state = NORMAL;
    int escaped = 0;
    int prev = 0;

    while ((ch = fgetc(fp_in)) != EOF)
    {
        switch (state)
        {
            case NORMAL:

                if (ch == '"')
                {
                    state = STRING;
                    fputc(ch, fp_out);
                }

                else if (ch == '\'')
                {
                    state = CHARACTER;
                    fputc(ch, fp_out);
                }

                else if (ch == '/')
                {
                    next = fgetc(fp_in);

                    if (next == '/')
                    {
                        state = SINGLE_COMMENT;
                        fputc(' ', fp_out);
                    }

                    else if (next == '*')
                    {
                        state = MULTI_COMMENT;
                        fputc(' ', fp_out);
                        prev = 0;
                    }

                    else
                    {
                        fputc(ch, fp_out);

                        if (next != EOF)
                        {
                            ungetc(next, fp_in);
                        }
                    }
                }

                else
                {
                    fputc(ch, fp_out);
                }

                break;

            case STRING:

                fputc(ch, fp_out);

                if (escaped)
                {
                    escaped = 0;
                }
                else if (ch == '\\')
                {
                    escaped = 1;
                }
                else if (ch == '"')
                {
                    state = NORMAL;
                }

                break;

            case CHARACTER:

                fputc(ch, fp_out);

                if (escaped)
                {
                    escaped = 0;
                }
                else if (ch == '\\')
                {
                    escaped = 1;
                }
                else if (ch == '\'')
                {
                    state = NORMAL;
                }

                break;

            case SINGLE_COMMENT:

                if (ch == '\n')
                {
                    fputc('\n', fp_out);
                    state = NORMAL;
                }

                break;

            case MULTI_COMMENT:

                if (ch == '\n')
                {
                    fputc('\n', fp_out);
                }

                if (prev == '*' && ch == '/')
                {
                    state = NORMAL;
                }

                prev = ch;

                break;
        }
    }

    return 0;
}
