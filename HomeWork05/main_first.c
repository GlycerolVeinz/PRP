#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define STARTING_SIZE 20
#define SUCCESS 0
#define ERR_INP 100
#define ERR_SIZE 101
#define ALL_CHARS 58
#define NON_LETTER_CHARS 6
#define ALL_ALPHA 52

void *CheckedMalloc(size_t size)
{
    void *al_mem = malloc(size);
    if (!al_mem)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
    return al_mem;
}

void *CheckedRealloc(void *ptr, size_t size)
{
    void *al_mem = realloc(ptr, size);
    if (!al_mem)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
    return al_mem;
}

char *read_line()
{
    // fce reads line from stdin
    // ret adress in mem to string
    int current_size = STARTING_SIZE * sizeof(char);
    char *saving_to = CheckedMalloc(current_size);
    int i = 0;
    do
    {
        if (i >= current_size - 1)
        {
            current_size *= 2;
            saving_to = CheckedRealloc(saving_to, current_size);
        }
        saving_to[i++] = getchar();
    } while (saving_to[i - 1] != '\n');

    saving_to[i - 1] = '\0';
    return saving_to;
}

int not_letters(char *line)
{
    // fce checks if chars are not letters
    // ret true if so
    int i = 0;
    while (line[i] != '\0')
    {
        if (((line[i] < 'a') || (line[i] > 'z')) &&
            ((line[i] < 'A') || (line[i] > 'Z')))
        {
            return TRUE;
        }
        i++;
    }
    return FALSE;
}

int ascii_cycle(char original, int shift)
{
    int res = original + shift;

    // go back to start of alphabet
    if (res > 'z' && shift <= 42)
    {
        res -= ALL_CHARS;
    }

    if (res > 'z' && shift > 42)
    {
        res -= ALL_CHARS;
        res += NON_LETTER_CHARS;
    }

    // skip non letters
    if (res > 'Z' && res < 'a')
    {
        res += NON_LETTER_CHARS;
    }

    return res;
}

void find_similarities(char *to_shift, char *unchanged, int save_to[ALL_ALPHA])
{
    /* shift letters by n amount
     * ret arr with amount of same letters in all shifts
     * position symbolises shift by,
     * int at position symbolises number of same letters.
     * (save_to is the array)
     */

    int line_size = strlen(to_shift);
    int cycled_letter = 0;
    // for each letter in alphabet
    for (int i = 0; i < ALL_ALPHA; i++)
    {
        // printf("\ni = %d\n", i);
        save_to[i] = 0;
        // for each letter in line
        for (int j = 0; j < line_size; j++)
        {
            // printf("\nj = %d\n", j);
            cycled_letter = ascii_cycle(to_shift[j], i);

            // // go back to start of alphabet
            // if (cycled_letter > 'z' && i <= 42)
            // {
            //     cycled_letter -= ALL_CHARS;
            // }

            // if (cycled_letter > 'z' && i > 42)
            // {
            //     cycled_letter -= ALL_CHARS;
            //     cycled_letter += NON_LETTER_CHARS;
            // }

            // // skip non letters
            // if (cycled_letter > 'Z' && cycled_letter < 'a')
            // {
            //     cycled_letter += NON_LETTER_CHARS;
            // }

            // if letters are same,
            // remember it then safe to array
            if (cycled_letter == unchanged[j])
            {
                save_to[i]++;
            }

            printf("%c", cycled_letter);
        }
        printf("\n\n");
    }
}

int main(int argc, char const *argv[])
{
    // read cipher and heard lines
    char *cipher_line_p = read_line();
    char *heard_line_p = read_line();

    // check if letters
    if (not_letters(cipher_line_p) || not_letters(heard_line_p) ||
        cipher_line_p == NULL || heard_line_p == NULL)
    {
        free(cipher_line_p);
        free(heard_line_p);
        fprintf(stderr, "Error: Chybny vstup!\n");
        return ERR_INP;
    }

    // check size of lines
    if (strlen(cipher_line_p) != strlen(heard_line_p))
    {
        free(cipher_line_p);
        free(heard_line_p);
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        return ERR_SIZE;
    }

    // shift letters in cipher,
    int equal_letters[ALL_ALPHA];
    find_similarities(cipher_line_p, heard_line_p, equal_letters);

    // find the best shift
    int most_similarities = 0;
    for (int i = 0; i < ALL_ALPHA; i++)
    {
        printf("sim = %d  eq = %d  i = %d\n", most_similarities, equal_letters[i], i);
        if (equal_letters[most_similarities] < equal_letters[i])
        {
            most_similarities = i;
        }
    }

    // shift by that amount
    int cipher_transform = 0;
    printf("\n%d\n", most_similarities);
    for (int i = 0; i < strlen(cipher_line_p); i++)
    {
        printf("%c", cipher_line_p[i]);
        cipher_transform = ascii_cycle(cipher_line_p[i], most_similarities);

        // if (cipher_transform > 'z' && most_similarities <= 42)
        // {
        //     cipher_transform -= ALL_CHARS;
        // }

        // if (cipher_transform > 'z' && most_similarities > 42)
        // {
        //     cipher_transform -= ALL_CHARS;
        //     cipher_transform += NON_LETTER_CHARS;
        // }

        // if (cipher_transform > 'Z' && cipher_transform < 'a')
        // {
        //     cipher_transform += NON_LETTER_CHARS;
        // }

        cipher_line_p[i] = cipher_transform;
    }

    // print result
    printf("\n%s\n", cipher_line_p);

    // clean mess and end
    free(cipher_line_p);
    free(heard_line_p);
    return SUCCESS;
}
