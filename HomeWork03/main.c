#include <stdio.h>
#define EXIT_SUCCESS 0
#define EXIT_ER_NUM 100
#define EXIT_ER_INTERVAL 101
#define EXIT_ER_EVEN 102
#define EXIT_ER_FENCE 103
#define UPPER_LIMIT 69
#define LOWER_LIMIT 3
#define MINIMAL_FENCE 1

void print_walls(int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        if (i == 0 || i == height - 1) // top of house or base of house
        {
            for (int j = 0; j < width; j++)
            {
                printf("X");
            }
            printf("\n");
        }
        else // side walls
        {
            printf("X");
            for (int j = 0; j < width - 2; j++)
            {
                printf(" ");
            }
            printf("X\n");
        }
    }
}

void print_fence_walls(int width, int height, int fence)
{
    for (int i = 0; i < height; i++)
    {
        if (i == 0) // top of house
        {
            for (int j = 0; j < width; j++)
            {
                printf("X");
            }
            printf("\n");
        }

        else if (i == height - 1) // bottom of the house
        {
            for (int j = 0; j < width; j++)
            {
                printf("X");
            }
            if ((fence % 2) == 0) // + fence
            {
                for (int j = 0; j < (fence / 2); j++)
                {
                    printf("-|");
                }
            }
            else
            {
                printf("|");
                for (int j = 0; j < ((fence - 1) / 2); j++)
                {
                    printf("-|");
                }
            }
            printf("\n");
        }

        else // side walls
        {
            printf("X");
            for (int j = 0; j < width - 2; j++) // upgraded wall
            {
                if ((i % 2) == 0)
                {
                    if ((j % 2) == 1)
                    {
                        printf("o");
                    }
                    else
                    {
                        printf("*");
                    }
                }
                else
                {
                    if ((j % 2) == 1)
                    {
                        printf("*");
                    }
                    else
                    {
                        printf("o");
                    }
                }
            }
            printf("X");

            if (i < (height - fence)) // no fence
            {
                printf("\n");
            }

            else if (i == (height - fence)) // highest point of fence
            {
                if ((fence % 2) == 0)
                {
                    for (int j = 0; j < (fence / 2); j++)
                    {
                        printf("-|");
                    }
                }
                else if (fence != 1 && (fence % 2) == 1)
                {
                    printf("|");
                    for (int j = 0; j < ((fence - 1) / 2); j++)
                    {
                        printf("-|");
                    }
                }
                else
                {
                    printf("|");
                }
                printf("\n");
            }
            else if ((i > (height - fence)) && i != height - 1) // most of the fence
            {
                if ((fence % 2) == 0)
                {
                    for (int j = 0; j < (fence / 2); j++)
                    {
                        printf(" |");
                    }
                }
                else
                {
                    printf("|");
                    for (int j = 0; j < ((fence - 1) / 2); j++)
                    {
                        printf(" |");
                    }
                }
                printf("\n");
            }
        }
    }
}

void print_roof(int width, int height)
{
    int roof_size = ((width - 1) / 2);
    for (int i = 0; i < roof_size; i++)
    {
        if (i == 0) // the heighest point
        {
            for (int j = 0; j < roof_size; j++)
            {
                printf(" ");
            }
            printf("X\n");
        }
        else // roof sides
        {
            for (int j = 0; j < (roof_size - i); j++)
            {
                printf(" ");
            }
            printf("X");
            for (int j = 0; j < ((i * 2) - 1); j++)
            {
                printf(" ");
            }
            printf("X\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    int house_width;
    int house_height;
    int fence_size;

    if (scanf("%d", &house_width) == 0) // check if number
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return EXIT_ER_NUM;
    }
    if (scanf(" %d", &house_height) == 0) // check if number
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return EXIT_ER_NUM;
    }

    if (house_width < LOWER_LIMIT || house_width > UPPER_LIMIT || house_height < LOWER_LIMIT || house_height > UPPER_LIMIT) // check if in range
    {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        return EXIT_ER_INTERVAL;
    }

    if ((house_width % 2) == 0) // check if width is odd
    {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        return EXIT_ER_EVEN;
    }

    if (house_height == house_width) // fence bonus
    {

        if ((scanf(" %d", &fence_size)) == 0) // check if number
        {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return EXIT_ER_NUM;
        }
        if ((fence_size >= house_height) || (fence_size < MINIMAL_FENCE)) // check if smaller then house
        {
            fprintf(stderr, "Error: Neplatna velikost plotu!\n");
            return EXIT_ER_FENCE;
        }
        print_roof(house_width, house_height);
        print_fence_walls(house_width, house_height, fence_size);
    }
    else // basic house
    {
        print_roof(house_width, house_height);
        print_walls(house_width, house_height);
    }
    return EXIT_SUCCESS;
}
