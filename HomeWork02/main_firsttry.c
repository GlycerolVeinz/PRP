#include <stdio.h>
#include <stdlib.h>
#define UPPER_RANGE_LIMIT 10001
#define LOWER_RANGE_LIMIT -10001

int main(void)
{
    int scanned_number;
    int count_of_nums = 0;
    int even_nums = 0;
    int odd_nums = 0;
    int positive_nums = 0;
    int negative_nums = 0;
    int highest_num = LOWER_RANGE_LIMIT;
    int lowest_num = UPPER_RANGE_LIMIT;
    int summ_of_nums = 0;

    // scanf uknown amount of numbers in range <-10000; 10000>
    do
    {

        if (scanf("%d", &scanned_number)) // if they really are numbers
        {
            if (scanned_number == 0x0a || scanned_number == 0x20) // the last character is enter, and I dont want it with other numbers
            {
                continue;
            }

            if ((scanned_number <= LOWER_RANGE_LIMIT) || (scanned_number >= UPPER_RANGE_LIMIT)) // check if in range
            {
                fprintf(stdout, "\nError: Vstup je mimo interval!\n");
                return 100;
            }

            // printf those numbers separated by ", " last one withou ", "
            if (count_of_nums == 0) // so first goes alone
            {
                printf("%d", scanned_number);
            }
            else // everyone else gets ", " before them
            {
                printf(", %d", scanned_number);
            }

            count_of_nums += 1; // for statistics, how many numbers

            summ_of_nums += scanned_number; // for statistics, summ of all numbers

            if ((scanned_number % 2) == 0) // for statistics, checks if even or odd
            {
                even_nums += 1;
            }
            else
            {
                odd_nums += 1;
            }

            if (scanned_number < lowest_num) // for statistics, checks extremes
            {
                lowest_num = scanned_number;
            }
            if (scanned_number > highest_num)
            {
                highest_num = scanned_number;
            }

            if (scanned_number > 0) // for statistics, check if positive or negative
            {
                positive_nums += 1;
            }
            else if (scanned_number == 0) // ignore zero
            {
                continue;
            }
            else
            {
                negative_nums += 1;
            }
        }

        else // if not a number print error
        {
            fprintf(stderr, "Error: Neni cislo!\n");
            return 1;
        }

    } while ((scanned_number = getchar()) != EOF); // stop scanning at end of file

    // printf "number statistics"
    printf("\nPocet cisel: %d", count_of_nums);
    printf("\nPocet kladnych: %d", positive_nums);
    printf("\nPocet zapornych: %d", negative_nums);
    printf("\nProcento kladnych: %.2f", (((float)positive_nums * 100) / (float)count_of_nums));
    printf("\nProcento zapornych: %.2f", (((float)negative_nums * 100) / (float)count_of_nums));
    printf("\nPocet sudych: %d", even_nums);
    printf("\nPocet lichych: %d", odd_nums);
    printf("\nProcento sudych: %.2f", (100 - (((float)odd_nums * 100) / (float)count_of_nums)));
    printf("\nProcento lichych: %.2f", (((float)odd_nums * 100) / (float)count_of_nums));
    printf("\nPrumer: %.2f", ((float)summ_of_nums / (float)count_of_nums));
    printf("\nMaximum: %d", highest_num);
    printf("\nMinimum: %d", lowest_num);
    printf("\n");

    return 0;
}

// format like a pro pls))
