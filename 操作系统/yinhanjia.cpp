#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int i,j,k,l;
int flag;
char c;
typedef struct Banker{
	int *Available;		//可利用资源向量
	int **Max;			//最大需求矩阵
	int **Allocation;	//分配矩阵
	int **Need;			//需求矩阵
	int **Requst;		//申请各类资源数量
	int *Work;			//工作向量
	int *Finish;		//结束向量
}Process;
int Bank(Process *process,int m,int n);
int Safe(Process *process,int m,int n);
void Max(Process *process,int m,int n);
void Need(Process *process,int m,int n);
void Allocation(Process *process,int m,int n);
void Available(Process *process,int n);
int Requst(Process *process,int m,int n);

int Bank(Process *process,int m,int n)
{
	do	//资源请求失败或者系统不安全时flag=0,并重新输入。
	{
		if((flag=Requst(process,m,n))==1)
		{
			printf("请求并试分配成功。\n");
			for(j=0;j<n;j++)
			{
				(process->Available)[j]-=(process->Requst)[l][j];
				(process->Allocation)[l][j]+=(process->Requst)[l][j];
				(process->Need)[l][j]-=(process->Requst)[l][j];
			}
		}
		if(flag==1&&(flag=Safe(process,m,n))==0)//系统不安全，撤销资源试分配
		{
			printf("撤销资源试分配。\n");
			for(j=0;j<n;j++)
				{
					(process->Available)[j]+=(process->Requst)[l][j];
					(process->Allocation)[l][j]-=(process->Requst)[l][j];
					(process->Need)[l][j]+=(process->Requst)[l][j];	
				}
		}
	}while(flag==0);
	if(flag==1) 
	{
		printf("分配成功。\n");
		printf("是否继续请求资源分配？输入Y继续，输入y结束：\n");
		getchar();
		c=getchar();
		if(c=='Y')return 1;
		if(c=='y')return 0;
	}
}
int Safe(Process *process,int m,int n)
{
	(process->Work)=(int *)malloc(sizeof(int)*n);
	for(j=0;j<n;j++)
		(process->Work)[j]=(process->Available)[j];//系统可提供给进程继续运行所需的各类资源数目
	
	(process->Finish)=(int *)malloc(sizeof(int)*m);
	for(i=0;i<m;i++)
		(process->Finish)[i]=FALSE;
	k=m;
	int flag1;				//当有不符合条件的资源时标记为0
	int flag2;				//当所有进程不都分配成功时标记为0
	int *s=(int *)malloc(sizeof(int)*m);//记录安全序列
	do
	{
		for(i=0;i<m;i++)		//一轮分配
			if((process->Finish)[i]==FALSE)
			{
				flag1=1;
				for(j=0;j<n;j++)
					if((process->Need)[i][j]>(process->Work)[j])
						flag1=0;//有不符合条件的资源
				if(flag1==1)
				{
					for(j=0;j<n;j++)
						*((process->Work)+j)+=*((process->Allocation)[i]+j);
					(process->Finish)[i]=TRUE;
					*s=i;
					s++;
				}
			}
		k--;//每完成一次进程分配时k减1,以便跳出循环和防止死循环
	}while(k>0);
	flag2=1;
	for(i=0;i<m;i++)	//判断是否所有进程都完成
	{
		if((process->Finish)[i]==FALSE)
		{
			flag2=0;
			break;
		}
	}
	if(flag2==0)
	{
		printf("当前状态不安全！\n");
		return 0;
	}
	else
	{
		printf("当前状态安全！\n");
		for(i=0;i<m;i++)s--;
		printf("安全序列为：");
		for(i=0;i<m;i++)
			printf("P%d ",s[i]);
		printf("\n");
		free(s);
		return 1;
	}
}
void Max(Process *process,int m,int n)
{
	process->Max=(int **)malloc(sizeof(int *)*m);//分配m个指针，用来指向数组的首地址
	for(i=0;i<m;i++)
		(process->Max)[i]=(int *)malloc(sizeof(int)*n);//为每个数组分配n个指针元素
	printf("输入各进程对各类资源的最大需求量：\n");
	for(i=0;i<m;i++)
	{
		printf("P%d:\n",i);
		for(j=0;j<n;j++)
		{
			scanf("%d",((process->Max)[i]+j));
		}
	}
}
void Need(Process *process,int m,int n)
{
	process->Need=(int **)malloc(sizeof(int *)*m);
	for(i=0;i<m;i++)
		(process->Need)[i]=(int *)malloc(sizeof(int)*n);
	printf("输入各进程对各类资源的需求量：\n");
	for(i=0;i<m;i++)
	{
		printf("P%d:\n",i);
		for(j=0;j<n;j++)
		{
			scanf("%d",((process->Need)[i]+j));
		}
	}
}
void Allocation(Process *process,int m,int n)
{
	process->Allocation=(int **)malloc(sizeof(int *)*m);
	for(i=0;i<m;i++)
		(process->Allocation)[i]=(int *)malloc(sizeof(int)*n);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			*((process->Allocation)[i]+j)=(*((process->Max)[i]+j))-(*((process->Need)[i]+j));
}
void Available(Process *process,int n)
{
	process->Available=(int *)malloc(sizeof(int)*n);
	printf("输入系统可用资源数：\n");
	for(i=0;i<n;i++)
		scanf("%d",&(process->Available)[i]);
}
int Requst(Process *process,int m,int n)
{
	process->Requst=(int **)malloc(sizeof(int *)*m);
	for(i=0;i<m;i++)
		(process->Requst)[i]=(int *)malloc(sizeof(int)*n);
	printf("输入进程名及其资源请求量：\n");
	scanf("%d",&i);
	l=i;
	for(j=0;j<n;j++)
		scanf("%d",(process->Requst)[i]+j);
	int flag1=1;//申请量大于需求量时标记为0
	int flag2=1;//申请量大于可利用资源量时标记为0
	for(j=0;j<n;j++)//检查申请量是否小于等于需求量
		if((process->Requst)[i][j]>(process->Need)[i][j])
			flag1=0;
	if(flag1==0)
	{
		printf("不允许申请量大于需求量!请重新输入。\n");
		return 0;
	}
	if(flag1==1)
	{
		for(j=0;j<n;j++)//检查申请量是否小于等于系统中的可利用资源量
			if((process->Requst)[i][j]>(process->Available)[j])
				flag2=0;
		if(flag2==0)
		{
			printf("不允许申请量大于可利用资源量!请重新输入。\n");
			return 0;
		}
		else return 1;
	}
}
int main()
{	
	Process process;
	int m,n;
	printf("请输入进程数：");
	scanf("%d",&m);
	printf("请输入资源种类数：");
	scanf("%d",&n);
	Max(&process,m,n);
	Need(&process,m,n);
	Allocation(&process,m,n);
	Available(&process,n);
	Safe(&process,m,n);
	while(Bank(&process,m,n));
	return 0;
}