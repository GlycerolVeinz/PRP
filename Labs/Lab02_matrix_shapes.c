#include <stdio.h>

int main(void)
{
    int size_of_matrix = 5;
    scanf("%d", &size_of_matrix);
    int d = 0;
    scanf("%d", &d);
    // for (int i = 0; i < size_of_matrix; ++i)
    //     {
    //         for (int j = 0; j < size_of_matrix; ++j)
    //             {
    //              printf("[%3d;%3d] ",i,j);

    //             }

    //         printf("\n");
    //     }
    // printf("\n");

    for (int i = 0; i < size_of_matrix; ++i)
    {
        for (int j = 0; j < size_of_matrix; ++j)
        {
            if (i == j && (d == 0 || d == 2))
            {
                printf("[%2d;%2d]", i, j);
            }
            else if ((i + j == size_of_matrix - 1) && (d == 1 || d == 2))
            {
                printf("[%2d;%2d]", i, j);
            }
            else
            {
                printf("[  ;  ]");
            }
        }

        printf("\n");
    }
    printf("\n");

    return 0;
}
