#include <stdio.h>
#include <math.h>

#define NUM_ERROR 100
#define PRIME_MAX 1000000
#define IS_PRIME 1
#define NOT_PRIME 0
#define EXIT_SUCCESS 0

void sieve(int sieved_nums[]) // Sieve of Eratosthenes
{
    unsigned long size = PRIME_MAX;

    for (unsigned long i = 0; i < size; i++) // create all nums from 2 to 10^6...
    {
        sieved_nums[i] = IS_PRIME; // ...expect them to be prime
    }

    // eleminate weird ones by hand
    sieved_nums[0] = NOT_PRIME;
    sieved_nums[1] = NOT_PRIME;

    for (unsigned long i = 2; i < sqrt(size); i++)
    {
        if (sieved_nums[i]) // if i is prime...
        {
            for (unsigned long j = pow(i, 2); j < size; j += i) // ...set every i^n as not prime
            {
                sieved_nums[j] = NOT_PRIME;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    long long factorize_num = 2;
    int prime_nums[PRIME_MAX];
    sieve(prime_nums);
    int factor = 0;
    int power = 0;

start_scan:
    if (((scanf("%lld", &factorize_num)) == 0) || (factorize_num < 0)) // check if number, and larger then 0
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return NUM_ERROR;
    }

    else if (factorize_num == 0) // if zero -> end
    {
        return EXIT_SUCCESS;
    }

    else if (factorize_num == 1) // eleminate weird case by hand
    {
        printf("Prvociselny rozklad cisla %lli je:\n1\n", factorize_num);
        goto start_scan;
    }

    else
    {
        printf("Prvociselny rozklad cisla %lli je:\n", factorize_num);

        for (long long i = 0; i <= PRIME_MAX; i++)
        {
            if ((prime_nums[i] == IS_PRIME) && ((factorize_num % i) == 0)) // if number is prime and can divide input
            {
                factor += 1; // this is purely for " x " symbol
                factor > 1 ? printf(" x ") : 0;
                printf("%lli", i);

                while ((factorize_num % i) == 0) // while input is divisble by number...
                {
                    factorize_num /= i; //...divide
                    power += 1;         // if made more times, increase power
                }
                power > 1 ? printf("^%d", power) : 0;
            }
            power = 0; // reset power

            if (factorize_num == 1) // if there is nothing else to do
            {
                printf("\n");
                factor = 0; // reset factor
                goto start_scan;
            }
        }
    }
    return EXIT_SUCCESS;
}
