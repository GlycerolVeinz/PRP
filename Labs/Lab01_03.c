#include <stdio.h>

int main(int argc, char const *argv[])
{
    int repetitions = 0;
    scanf("%d", &repetitions);
    printf ("%d\n",repetitions);


    if ((repetitions < 10) && (repetitions > 0))
    {
        for (int c = 0; c < repetitions; ++c)
            return 0;
    }

    if ((repetitions > 10) || (repetitions < 0))
    {
        printf("ERROR: not a valid number\n");
        return 1;
    }

}
