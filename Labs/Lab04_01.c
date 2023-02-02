#include <stdio.h>

#define ERROR_INPUT 100
#define EXIT_SUCCESS 0

int fill_array(int *arr, int n) {
    int ret = EXIT_SUCCESS;
    int num;
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return ret;
}

void print_array(int *arr, int n) {
    printf("Entered array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



int main(int argc, char const *argv[])
{
    int ret = EXIT_SUCCESS;
    int n;
    printf("Enter length of the array: ");
    if (scanf("%d", &n) != 1) {
        ret = ERROR_INPUT;
        fprintf(stderr, "ERROR: Wrong input.\n");
        return ret;
    } 
    int vl_arr[n];
    ret = fill_array(vl_arr, n);
    print_array(vl_arr, n);

    return ret;
}
