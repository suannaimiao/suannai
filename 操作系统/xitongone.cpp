#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<ctime>
#include<map>
#include<string.h>
using namespace std;
const int N = 1000;

struct Task{
    char name[10];
    int come_time;
    int turn_time;
    int start_time;
    int end_time;
    int wait_time;
    /*data*/
}task[N],tp_task[N];

int num;
void sleep(int n){
    int st= clock();
    while((clock()-st)<=n);
}
void GetData(){
    printf("请输入每个进程的名称，到达时间，服务时间\n");
    for(int i = 0;i<num;i++){
    scanf("%s%d%d",task[i].name,&task[i].come_time,&task[i].turn_time);
    strcpy(tp_task[i].name,task[i].name);
    tp_task[i].come_time = task[i].turn_time;
    tp_task[i].turn_time = task[i].turn_time;
    }
    printf("进程信息输入完毕！！！\n");
}
void BackData(){
    for(int i = 0 ;i<num;i++){
        strcpy(task[i].name,tp_task[i].name);
        task[i].come_time=tp_task[i].come_time;
        task[i].turn_time=tp_task[i].turn_time;
    }
    printf("准备就绪\n");
}

void Printf(){
    printf("进程运行信息：\n");
    printf("进程名字    到达时间    开始时间    周转时间    结束时间\n");
    for(int i = 0;i<num;i++){
        printf("%s\t\t%d\t\t",task[i].name,task[i].come_time);
        printf("%d\t\t%d\t\t",task[i].start_time,task[i].turn_time);
        printf("%d\n",task[i].end_time);
        }
}

bool cmp_1(struct  Task a ,struct Task b)
{
    return a.turn_time < b.turn_time;
}

bool cmp_2(struct Task &a,struct Task b)
{
    return a.come_time < b.come_time;
}
bool cmp_3(struct Task a ,struct Task b)
{
    if(a.end_time < b.turn_time){
    double ra =(a.wait_time+a.turn_time)*1.0/a.turn_time;
    double rb= (b.wait_time+b.turn_time)*1.0/b.turn_time;
    return ra>rb;
    }else
    {
        return a.end_time <b.end_time;
    }
    

}

bool cmp_4(struct Task a,struct Task b){
    return a.come_time < b.come_time;    
}
bool cmp_5(struct Task a, struct Task b){
    return a.end_time < b.end_time;
}
void FCFS(){
    int count_time= 0;
    sort(tp_task,tp_task+num,cmp_2);
    for(int i= 0;i<num;i++){
        printf("%s进程正在运行\n",task[i].name);
        for(int j=0;j<10;j++){
            sleep(100*task[i].turn_time);
        }
        putchar('\n');//程序暂停时间
        task[i].start_time=count_time= 0;
        count_time+=task[i].turn_time;
        task[i].end_time = count_time;

    }
    printf("\n所有程序都执行完了");
    Printf();
}
void SJF(){
    sort(task,task+num,cmp_1);
    int count_time=0;
    for(int i=0; i<num;i++){
        printf("%s进程执行",task[i].name);
        for(int j = 0;j<num;j++){
            sleep(100*task[i].turn_time);
            printf(".");

        }
        putchar('\n');
        task[i].end_time=count_time;
    }
    printf("\n所有进程全部执行完了");

    Printf();

}

void HRRN()
{
    /**
    功能；运行非抢占式 高响应比 优先调度算法执行进程，将进程的运行结束信息
          输出显示。
    */
    //初始化进程的结束时间 -1
    for (int i = 0; i < num; i++)
        task[i].end_time = -1;

    int countt = 0;  //计时器
    while (true)
    {
        for (int i = 0; i < num; i++)
            task[i].wait_time = countt - task[i].come_time;
        sort(task, task + num, cmp_4);

        if (task[0].end_time >= 0) break;

        printf("%s进程正在执行", task[0].name);
        for (int j = 0; j < 10; j++)
        {
            sleep(100 * task[0].turn_time); printf(".");
        }
        putchar('\n');

        //sleep(1000 * task[0].turn_time);  // 程序暂停时间（单位：ms)
        task[0].start_time = countt;
        countt += task[0].turn_time;
        task[0].end_time = countt;
    }
    printf("\n所有进程全部执行完毕！！！\n\n");

    sort(task, task + num, cmp_4); // 按照开始运行的时间从小到大排序
    Printf();
}
void PreemptiveHRRN()
{
    /**
    功能；运行抢占式 高响应比 优先调度算法执行进程，将进程的运行结束信息
          输出显示。
    */

    //备份每个进程的服务时间
    map<string, int> shift;
    shift.clear();

    for (int i = 0; i < num; i++)
        shift[ task[i].name ] = task[i].turn_time;


    //初始化进程的结束时间 and 进程的开始运行时间  -》 -1
    for (int i = 0; i < num; i++)
        task[i].end_time = task[i].start_time = -1;

    int countt = 0;  //计时器
    while (true)
    {
        for (int i = 0; i < num; i++)
            task[i].wait_time = countt - task[i].come_time;
        sort(task, task + num, cmp_3);

        if (task[0].end_time >= 0) break;


        if (task[0].start_time < 0)
            task[0].start_time = countt;

        printf("%s进程正在执行", task[0].name);
        for (int j = 0; j < 10; j++)
        {
            sleep(100); printf(".");
        }
        putchar('\n');

        //sleep(1000);  // 程序暂停时间（单位：ms)
        countt++;     //运行一个时间片  （1 s)
        task[0].turn_time--;

        if (task[0].turn_time <= 0 && task[0].end_time < 0)
            task[0].end_time = countt;
    }
    printf("所有进程全部执行完毕！！！\n\n");

    //恢复每个进程的服务时间
    for (int i = 0; i < num; i++)
        task[i].turn_time = shift[task[i].name];

    sort(task, task + num, cmp_5); // 按照开始运行的时间从小到大排序
    Printf();
}
void Menu()
{
    printf("\t命令\n");
    printf("\t0.输入进程数据信息\n");
    printf("\t1.FCFS算法\n");
    printf("\t2.SJF算法\n");
    printf("\t3.HRRN算法\n");
    printf("\t4.PreemptiveHRRN算法\n");
    printf("\t5.over!!!\n\n");
}

int main(){
    int menu;
    int flag = 1;
    printf("程序开始\n\n");
    while (flag)
    {
        Menu();
        printf("请输入命令: ");
        cin >> menu;
        switch (menu)
        {
            case 0:
                printf("请输入进程的个数:  ");
                scanf("%d", &num);
                GetData();
                break;
            case 1:
                printf("     <启动 FCFS 调度算法>\n");
                FCFS();
                break;
            case 2:
                printf("     <启动 SJF 调度算法>\n");
                SJF();
                break;
            case 3:
                printf("     <启动非抢占式 HRRN 调度算法>\n");
                HRRN();
                break;
            case 4:
                printf("     <启动抢占式 HRRN 调度算法>\n");
                PreemptiveHRRN();
                break;
            case 5:
                flag = 0;
                break;

        }
        BackData();
    }



    return 0;

}
