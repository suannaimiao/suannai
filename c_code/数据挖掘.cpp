#include <stdio.h>
#include <iostream>
#include <math.h>
#define m 7 //7��
#define n 4 //4��
int max(float a[][n], float b[], float c[])
{ //�������Сֵ
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
{ //��ÿ�еľ�ֵ�ͱ�׼��
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
    //��ÿ��������ֵ��λ��

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
    //��ÿ��������ֵ��λ��
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
void printff(float a[][n]) //�Զ��庯�������������
{
    int count = 0;
    for (int i = 0; i < m; i++) //���ԭ������
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
    float data[m][n] = {{78, 521, 602, 2863}, {144, -600, -521, 2245}, {95, -457, 468, -1283}, {69, 596, 695, 1054}, {190, 527, 691, 2051}, {101, 403, 470, 2487}, {146, 413, 435, 2571}}; //��������
    float data_new[m][n];                                                                                                                                                                  //������������������Ž��
    float data_two[m][n];
    float data_three[m][n];
    int count = 0;
    //��С�����淶��
    float data_max[n]; //�������������������
    float data_min[n];
    float data_aver[n];
    float data_std[n];
    float data_abs[n];
    float data_size[n];

    printf("\n");
    printf("�����1901 ������ ���ϣ�");
    printf("\n");
    printf("ԭ�����ݾ���\n");
    printff(data);
    /*for (int i = 0; i < m; i++) //���ԭ������
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
    printf("��С�����淶����\n");

    max(data, data_max, data_min);
    //��ʼ��������
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            data_new[i][j] = (data[i][j] - data_min[j]) / (data_max[j] - data_min[j]);
        }
    } //�����׼������

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
    } //���
    printf("\n\n");
    */
    //��-��ֵ�淶��
    printf("��-��ֵ�淶����\n");
    aver_std(data, data_aver, data_std); //���ú������ÿ�о�ֵ�ͷ���
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            data_two[i][j] = (data[i][j] - data_aver[j]) / data_std[j];
        }
    }
    printff(data_two); //������
    printf("\n");

    printf("\n\n");
    printf("С������淶����\n");

    abs_num(data, data_abs); //���ú������ÿ�о���ֵ������ֵλ��
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
