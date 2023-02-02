#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STARTING_SIZE 20
#define SUCCESS 0
#define ERR_INP 100
#define ERR_SIZE 101
#define CAPITAL_CONST 65
#define LOWER_CONST 71
#define ALL_ALPHA 52
#define NORMALIZE '-'
#define DENORMALIZE '+'


void err_msg(int err_code);

void *CheckedMalloc(size_t size);

void *CheckedRealloc(void *ptr, size_t size);

char *read_line();

int not_letters(char *line);

char *change_char_val(char *ptr, char operand, int s_len);

void find_similarities(char *shifting, char *unchanged, int similarities[ALL_ALPHA],int s_len);

int best_shift(int similarities[ALL_ALPHA]);

void ces_decipher(char *to_decipher, int shift, int s_len);



int main(int argc, char const *argv[])
{
    // read lines
    char *cipher_line = read_line();
    char *heard_line = read_line();

    // if not letters raise err
    if (not_letters(cipher_line) || not_letters(heard_line) ||
        cipher_line == NULL || heard_line == NULL)
    {
        err_msg(ERR_INP);
    }

    int str_len = strlen(cipher_line);

    // if lines are of dif size, raise err
    if (str_len != strlen(heard_line))
    {
        err_msg(ERR_SIZE);
    }

    

    // find similarities in dif shifts
    int similarities[ALL_ALPHA];
    find_similarities(cipher_line, heard_line, similarities, str_len);

    // find best shift
    int most_similarities = best_shift(similarities);

    // decipher line by best shift & print
    ces_decipher(cipher_line, most_similarities, str_len);

    free(cipher_line);
    free(heard_line);
    return(SUCCESS);
}



void err_msg(int err_code)
{
    // prints err msg & exits with err_code
    switch (err_code)
    {
    case ERR_INP:
        fprintf(stderr,"Error: Chybny vstup!\n");
        break;
    case ERR_SIZE:
        fprintf(stderr,"Error: Chybna delka vstupu!\n");
        break;
    }

    exit(err_code);
}

void *CheckedMalloc(size_t size)
{
    // malloc that exits if fails
    void *al_mem = malloc(size);
    if (!al_mem)
    {
        err_msg(ERR_INP);
    }
    return al_mem;
}

void *CheckedRealloc(void *ptr, size_t size)
{
    // realloc that exits if fails
    void *al_mem = realloc(ptr, size);
    if (!al_mem)
    {
        err_msg(ERR_INP);
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
            return true;
        }
        i++;
    }
    return false;
}

char cicular_alphabet(char ch, int shift)
{
    // fce makes it so chars stay in alphabet
    return ((ch + shift) % ALL_ALPHA);
}

char *change_char_val(char *ptr, char operand, int s_len)
{
    // removes need to deal with symbols between 'Z' and 'a'
    int A_val, z_val, Z_val, a_val, sign;

    // choose way of change
    switch (operand)
    {
    case DENORMALIZE:
        A_val = 0;
        Z_val = 25;
        a_val = 26;
        z_val = 51;
        sign = 1;
        break;

    case NORMALIZE:
        A_val = 'A';
        Z_val = 'Z';
        a_val = 'a';
        z_val = 'z';
        sign = -1;
        break;
    }

    // change value of char, whilst deleting the ascii gap
    for (int i = 0; i < s_len; i++)
    {
        if (ptr[i] >= A_val && ptr[i] <= Z_val)
        {
            ptr[i] += (CAPITAL_CONST * sign);
        }
        else if (ptr[i] >= a_val && ptr[i] <= z_val)
        {
            ptr[i] += (LOWER_CONST * sign);
        }
    }
    

    return ptr;
}

void find_similarities(char *shifting, char *heard, int similarities[ALL_ALPHA], int s_len)
{
    /* shift letters by n amount
     * ret arr with amount of same letters in all shifts
     * position symbolises shift by,
     * int at position symbolises number of same letters.
     * (similarities is the array)
     */
    heard = change_char_val(heard, NORMALIZE, s_len);
    shifting = change_char_val(shifting, NORMALIZE, s_len);

    for (int i = 0; i <= ALL_ALPHA; i++)
    {
        similarities[i] = 0;
        for (int j = 0; j < s_len; j++)
        {
            shifting[j] = cicular_alphabet(shifting[j], 1);
            if (shifting[j] == heard[j])
            {
                similarities[i]++;
            }
        }
    }
}

int best_shift(int similarities[ALL_ALPHA])
{
    // finds best shift for letters by comparing to 2nd line
    int most_similarities = 0;
    for (int i = 0; i < ALL_ALPHA; i++)
    {
        if (similarities[most_similarities] < similarities[i])
        {
            most_similarities = i;
        }
    }

    return most_similarities;
}

void ces_decipher(char *to_decipher, int shift, int s_len)
{
    // deciphers by ceasar ciphre
    for (int i = 0; i < s_len; i++)
    {
        to_decipher[i] = cicular_alphabet(to_decipher[i], shift);
    }

    to_decipher = change_char_val(to_decipher, DENORMALIZE, s_len);

    for (int i = 0; i < s_len; i++)
    {
        printf("%c", to_decipher[i]);
    }
    printf("\n");
}
