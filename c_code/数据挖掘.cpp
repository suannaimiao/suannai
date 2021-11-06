#include <stdio.h>
#include <iostream>
#include <math.h>
#define m 7 //7行
#define n 4 //4列
int max(float a[][n], float b[], float c[])
{ //求最大及最小值
    for (int i = 0; i < n; i++)
        b[i] = c[i] = a[0][i];
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
        {
            if (a[i][j] > b[j])
                b[j] = a[i][j];
            if (a[i][j] < c[j])
                c[j] = a[i][j];
        }
    return 0;
}

int aver_std(float a[][n], float b[], float c[])
{ //求每列的均值和标准差
    float sum = 0.00;
    float std = 0.00;
    int num = 0;

    for (int i = 0; i < n; i++)
    {
        b[i] = c[i] = 0;
    }

    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
        {
            sum += a[i][j];
            num++;
            b[j] = sum / m;

            std += (a[i][j] - b[j]) * (a[i][j] - b[j]) / m;
            c[j] = sqrt(std);
            if (num % 7 == 0)
            {
                sum = 0;
                std = 0;
            }
        }
    return 0;
}

int abs_num(float a[][n], float b[])
{
    //求每列最大绝对值的位数

    for (int i = 0; i < n; i++)
    {
        b[i] = 0;
    }
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
        {
            if (abs(a[i][j]) > b[j])
            {
                b[j] = abs(a[i][j]);
            }
        }
    return 0;
}

int abs_size(float b[], float c[])
{
    //求每列最大绝对值的位数
    int num_size = 0;
    int num_data = 100;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        num_data = b[i];
        do
        {
            j++;
            num_data /= 10;
            num_size = j;
        } while (num_data > 0);
        c[i] = num_size;
        j = 0;
    }

    return 0;
}
void printff(float a[][n]) //自定义函数用来输出矩阵
{
    int count = 0;
    for (int i = 0; i < m; i++) //输出原来矩阵
        for (int j = 0; j < n; j++)
        {
            printf("%f\t\t", a[i][j]);
            count++;
            if (count % 4 == 0)
            {
                printf("\n");
            }
        }

    printf("\n\n");
}
int main()
{
    float data[m][n] = {{78, 521, 602, 2863}, {144, -600, -521, 2245}, {95, -457, 468, -1283}, {69, 596, 695, 1054}, {190, 527, 691, 2051}, {101, 403, 470, 2487}, {146, 413, 435, 2571}}; //定义数组
    float data_new[m][n];                                                                                                                                                                  //定义三个矩阵，用来存放结果
    float data_two[m][n];
    float data_three[m][n];
    int count = 0;
    //最小—最大规范化
    float data_max[n]; //定义数组用来存放数据
    float data_min[n];
    float data_aver[n];
    float data_std[n];
    float data_abs[n];
    float data_size[n];

    printf("\n");
    printf("计算机1901 朱万里 参上！");
    printf("\n");
    printf("原来数据矩阵：\n");
    printff(data);
    /*for (int i = 0; i < m; i++) //输出原来矩阵
        for (int j = 0; j < n; j++)
        {
            printf("%f\t\t", data[i][j]);
            count++;
            if (count % 4 == 0)
            {
                printf("\n");
            }
        }
    */
    printf("\n\n");
    printf("最小—最大规范化：\n");

    max(data, data_max, data_min);
    //开始处理数据
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            data_new[i][j] = (data[i][j] - data_min[j]) / (data_max[j] - data_min[j]);
        }
    } //极差标准化处理

    printff(data_new);
    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f\t\t", data_new[i][j]);
            count++;
            if (count % 4 == 0 && count != 0)
            {
                printf("\n");
            }
        }
    } //输出
    printf("\n\n");
    */
    //零-均值规范化
    printf("零-均值规范化：\n");
    aver_std(data, data_aver, data_std); //调用函数求出每列均值和方差
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            data_two[i][j] = (data[i][j] - data_aver[j]) / data_std[j];
        }
    }
    printff(data_two); //输出结果
    printf("\n");

    printf("\n\n");
    printf("小数定标规范化：\n");

    abs_num(data, data_abs); //调用函数求出每列绝对值最大的数值位数
    abs_size(data_abs, data_size);

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            data_three[i][j] = data[i][j] / pow(10, data_size[j]);
        }
    }
    printff(data_three);

    for (int i = 0; i < n; i++)
    {
        printf("%f\t", pow(10, data_size[i]));
    }
    printf("\n");

    return 0;
}
