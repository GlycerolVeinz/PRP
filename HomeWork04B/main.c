#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// - CONSTANTS -----------------------------------------------------------------

// constants for calculations
#define MAX_INP_LEN 101 // max lenght of number on input + 1 (place for marker) 
#define PRIME_MAX 1000000 // max size of a prime number

// constants for exit values
#define EXIT_SUCCESS 0 // exiting program without error
#define ERR_INP 100 // wrong input error
#define SUCCESS 1 // succesfully executing a function

// other constants
#define NO_PRIMES -1 // if there is 1 on input
#define EO_INPUT 0 // if there is 0 on input
#define EO_NUM '\n' // end of number marker
#define IS_PRIME 1
#define NOT_PRIME 0
#define IS_DIVISIBLE 1
#define NOT_DIVISIBLE 0
#define YES 1
#define NO 0

/*local type for really long number
 using '\n' as a marker, to symbolise EO_number*/
typedef int big_num[MAX_INP_LEN];

// - LOCAL DECLARATIONS -----------------------------------------------------------------

int ascii_trans(int inp);
void err_msg(int err_code);
int read_num(big_num big_int);
void sieve(int sieved_nums[]);
void print_big_num(big_num big_int);
int pretty_print(big_num big_int);
int long_division(big_num divided, long divisor);
void rewrite_big_num(big_num from, big_num to);



// - MAIN -----------------------------------------------------------------
int main(void)
{
	// prepare all prime numbers
	int prime_nums[PRIME_MAX];
	sieve(prime_nums);

	big_num big_int;
	while (read_num(big_int)) //while there are numbers in stdin
	{
		int printing_method = 0;

		if ((printing_method = pretty_print(big_int)) == EO_INPUT)
		{
			break;
		}
		else if (printing_method == NO_PRIMES)
			;
		else
		{
			int factor = 0; // purely for "x" symbol
			int power;

			// factorise
			for (long prime_i = 0; prime_i < PRIME_MAX; ++prime_i)
			{
				// if number is prime start dividing
				if ((prime_nums[prime_i] == IS_PRIME) &&
					(long_division(big_int, prime_i) == IS_DIVISIBLE))
				{
					power = 1;
					(++factor) > 1 ? printf(" x ") : 0; // prints "x" between numbers
					printf("%ld",prime_i);

					
					while (long_division(big_int, prime_i) == IS_DIVISIBLE) // divide until you can
					{
						power += 1;
					}
					power > 1 ? printf("^%d", power) : 0; // prints power of a number
				}
			}
			printf("\n");
		}
	}

	exit(EXIT_SUCCESS);
}
// - EO_MAIN-----------------------------------------------------------------



// - LOCAL FUNCTIONS -----------------------------------------------------------------

// - #function -----------------------------------------------------------------
/*exits program (thus freeing everything alloced) with exit code, and error message

err_code = exit code*/
void err_msg(int err_code)
{
	fprintf(stderr, "Error:");
	switch (err_code)
	{
	case ERR_INP:
		fprintf(stderr, " Chybny vstup!");
		break;
	}
	fprintf(stderr, "\n");
	exit(err_code);
}

// - #function -----------------------------------------------------------------
/*Changes ascii code to int numbers

ascii = input ascii code

return transformed int*/

int ascii_trans(int ascii)
{
	int ret = -1;
	if (ascii == '\n')
	{
		ret = 10;
	}
	else if ((ascii < '0') || (ascii > '9'))
	{
		err_msg(ERR_INP);
	}
	else
	{
		ret = (ascii - 48);
	}
	return ret;
}

// - #function -----------------------------------------------------------------
/*Reads a really long number, up to MAX_INP_LEN,
and stores it in a special big_num type,
!does not alloc it in any way!

big_int = special long num type

return SUCCESS when done*/
int read_num(big_num big_int)
{
	int inp = -1;
	int cursor = 0;
	do
	{
		inp = getchar();
		// printf("got = %d\n", inp);

		inp = ascii_trans(inp);
		// printf("changed to = %d\n", inp);

		big_int[cursor++] = inp;
	} while (inp != EO_NUM);

	return SUCCESS;
}

// - #function -----------------------------------------------------------------
/*Sieves all IDs in an array of size bigger then 2,
if the ID is a prime number, there will be 1 saved on it's position

sieved_nums[] = empty array of size at least 2*/
void sieve(int sieved_nums[]) // Sieve of Eratosthenes
{
	long size = PRIME_MAX;

	for (long i = 0; i < size; i++) // create all nums from 2 to 10^6...
	{
		sieved_nums[i] = IS_PRIME; // ...expect them to be prime
	}

	// eleminate weird ones by hand
	sieved_nums[0] = NOT_PRIME;
	sieved_nums[1] = NOT_PRIME;

	for (long i = 2; i < sqrt(size); i++)
	{
		if (sieved_nums[i]) // if i is prime...
		{
			for (long j = pow(i, 2); j < size; j += i) // ...set every i^n as not prime
			{
				sieved_nums[j] = NOT_PRIME;
			}
		}
	}
}

// - #function -----------------------------------------------------------------
/*Prints any big_num type*/
void print_big_num(big_num big_int)
{
	int cursor = 0;
	while (big_int[cursor] != EO_NUM)
	{
		printf("%d", big_int[cursor++]);
	}
}

// - #function -----------------------------------------------------------------
/*Prints "Prvociselny rozklad cisla [big_num] je:"

big_int = really long number type

returns EO_INPUT if input is 0,
returns NO_PRIMES if there are no primes,
else return SUCCESS*/
int pretty_print(big_num big_int)
{
	int ret;
	if (big_int[0] == EO_INPUT)
	{
		ret = EO_INPUT;
	}
	else if ((big_int[0] == 1) && (big_int[1] == EO_NUM))
	{
		printf("Prvociselny rozklad cisla 1 je:\n1\n");
		ret = NO_PRIMES;
	}
	else
	{
		printf("Prvociselny rozklad cisla ");
		print_big_num(big_int);
		printf(" je:\n");

		ret = SUCCESS;
	}

	return ret;
}

// - #function -----------------------------------------------------------------
/*Rewrites from big_num to big_num,
"to" will be rewriten so that it starts with non-zero integer

from = copy where from
to = where to copy*/
void rewrite_big_num(big_num from, big_num to)
{
	int start_num = NO; // marker for when the results starts (so that there arent execes 0)
	int cur_I = 0;
	int cur_II = 0;
	while (from[cur_I] != EO_NUM)
	{
		switch (start_num)
		{
		case NO:
			start_num = (from[cur_I] != 0) ? YES : NO;
			if (start_num == YES)
			{
				to[cur_II++] = from[cur_I];
			}
			break;

		case YES:
			to[cur_II++] = from[cur_I];
			break;
		}
		cur_I += 1;
	}
	to[cur_II] = EO_NUM;
}

// - #function -----------------------------------------------------------------
/*Long division that is learned in elementary school aplied to big_num type,
also rewrites divided if it is fully divisible by divisor (without a remainder)

divided = what to divide
divisor = divide by what number

return IS_DIVISIBLE if rewrite is succesfull, NOT_DIVISIBLE otherwise*/
int long_division(big_num divided, long divisor)
{
	// divide by divisor
	big_num result;
	long remainder = 0;
	int i = 0;
	while (divided[i] != EO_NUM)
	{
		int num = (divided[i] + remainder * 10);
		result[i++] = num / divisor;
		remainder = num % divisor;
	}
	result[i] = EO_NUM; // remember to mark where the number ends

	int ret = (remainder == 0) ? IS_DIVISIBLE : NOT_DIVISIBLE;

	// if is divisible, rewrite resulut to divided
	if (ret)
	{
		// printf("result = ");
		// print_big_num(result);

		rewrite_big_num(result, divided);

		// printf("\nrewrite = ");
		// print_big_num(divided);
	}

	return ret;
}

/*End of implimentation*/
