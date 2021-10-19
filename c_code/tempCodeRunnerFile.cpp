#include <stdio.h>
int main()
{
    int x[] = {74, 71, 72, 68, 76, 73, 67, 70, 65, 74};
    int y[] = {76, 75, 71, 70, 76, 79, 65, 77, 65, 72};

    int sum = 0;
    int sum2 = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += x[i];
        sum2 += y[i];
    }
    printf("sum: %d\n", sum);

    int average1 = sum / 10;

    int average2 = sum2 / 10;

    printf("average1 : %d\n", average1);

    for (int i = 0; i < 10; i++)
    {
        sum += x[i] * y[i] - average1 * average2;
        printf("sum : %d\t", sum);
        printf("\n");

        sum2 += x[i] * x[i] - average1 * average1;
    }

    printf("线性回归方程为： %d-%d", average1, average1 * sum / sum2);
}