#include <stdio.h>

int main(void)
{
    int money_spent = 0;
    scanf("%d", &money_spent);
    
    int fifty = (money_spent - money_spent % 50) / 50;
    int fiftyz = money_spent % 50;

    int twenty = (fiftyz - fiftyz % 20) / 20;
    int twentyz = fiftyz % 20;
    
    int ten = (twentyz - twentyz % 10) / 10;
    int tenz = twentyz % 10;
    
    int five = (tenz - tenz % 5) / 5;
    int fivez = tenz % 5;
    
    int two = (fivez - fivez % 2) / 2;
    int twoz = fivez % 2;
    
    int one = twoz / 1;

    printf("50 * %d\n20 * %d\n10 * %d\n5 * %d\n2 * %d\n1 * %d\n",fifty,twenty,ten,five,two,one);


    return 0;
}
