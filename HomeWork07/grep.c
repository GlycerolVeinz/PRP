#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SearchedExpression argv[1]
#define FileName argv[2]

#define ERR_TEXT 1
#define ERR_U 100
#define ERR_START 101
#define ERR_FILE 102
#define ERR_MALOC 103
#define ERR_REALOC 104
#define SUCCESS 0

#define MAX_SIZE 255

void errmsg(int err_type)
{
    switch (err_type)
    {
    case ERR_START:
        perror("Error: No searched expression or file detected.\n");
        exit(ERR_START);

    case ERR_FILE:
        perror("Error: Couldn't load a file.\n");
        exit(ERR_FILE);

    case ERR_MALOC:
        perror("Error: Malloc failed.\n");
        exit(ERR_MALOC);

    case ERR_REALOC:
        perror("Error: Realloc has failed.\n");
        exit(ERR_REALOC);

    default:
        perror("Error: Unexpected problem has occured\n");
        exit(ERR_U);
    }
}

void *CheckedMalloc(size_t size)
{
    // malloc that raises err instead of ret null
    void *al_mem = malloc(size);
    if (!al_mem)
    {
        errmsg(ERR_MALOC);
    }
    return al_mem;
}

void *CheckedRealloc(void *ptr, size_t size)
{
    // realloc that raises err instead of ret null
    void *al_mem = realloc(ptr, size);
    if (!al_mem)
    {
        errmsg(ERR_MALOC);
    }
    return al_mem;
}

void *CheckedFopen(const char *fname, const char *mode)
{
    // fopen that raises err instead of ret null
    FILE *a_file = fopen(fname, mode);

    if (!a_file)
    {
        errmsg(ERR_FILE);
    }

    return a_file;
}

int find_in_file(const char *fname, const char *expr)
{
    // assume that text isnt in file
    int ret = ERR_TEXT;

    // open working file and initialize needed things
    FILE *o_file = CheckedFopen(fname, "r");
    int curr_size = MAX_SIZE;
    char *curr_line = CheckedMalloc(curr_size);
    char cursor = ' ';
    int line_pos = 0;
    int exp_pos = 0;
    int safe_pos = 0;

    // while there are lines to read
    while (fgets(curr_line, curr_size, o_file))
    {
        // printf("line: %s", curr_line);
        // take curr_line, and read char by char
        while (cursor != '\n')
        {
            cursor = curr_line[line_pos++];
            // printf("cur: %c\n", cursor);
            // if cursor finds first letter of searched expression
            if (cursor == expr[exp_pos])
            {
                safe_pos = line_pos;

                // check if next chars are same
                while (1)
                {
                    // print line if yes, return val of prog = 0 and break
                    if (!expr[++exp_pos])
                    {
                        printf("%s", curr_line);
                        // say that line was found
                        ret = SUCCESS;
                        // reset for the next expression
                        exp_pos = 0;
                        // reset so that line isn't printed 2 times
                        cursor = '\n';
                        break;
                    }

                    // break if not
                    if (curr_line[line_pos++] != expr[exp_pos])
                    {
                        // reset counters
                        exp_pos = 0;
                        line_pos = safe_pos;
                        break;
                    }
                }
            }
        }

        // reset cursor, counter
        cursor = ' ';
        line_pos = 0;
    }


    fclose(o_file);
    free(curr_line);
    return ret;
}

int main(int argc, char const *argv[])
{
    // check if arguments are present
    if (argc != 3)
    {
        errmsg(ERR_START);
    }

    int ret = find_in_file(FileName, SearchedExpression);

    exit(ret);
}
