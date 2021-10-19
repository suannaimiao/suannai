#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*常量定义*/
#define PROCESS_NAME_LEN 32   	  /*进程名长度*/
#define MIN_SLICE 10              /*最小碎片的大小*/
#define DEFAULT_MEM_SIZE 1024     /*内存大小*/
#define DEFAULT_MEM_START 0       /*起始位置*/
/* 内存分配算法 */
#define MA_FF 1
#define MA_BF 2
#define MA_WF 3
/*描述每一个空闲块的数据结构*/
struct free_block_type{
	int size;
	int start_addr;
	struct free_block_type *next;
};
/*每个进程分配到的内存块的描述*/
struct allocated_block{
	int pid;
	int size;
	int start_addr;
	char process_name[PROCESS_NAME_LEN];
	struct allocated_block *next;
};
/*指向内存中空闲块链表的首指针*/
struct free_block_type *free_block;
/*进程分配内存块链表的首指针*/
struct allocated_block *allocated_block_head = NULL;
int mem_size=DEFAULT_MEM_SIZE; /*内存大小*/
int ma_algorithm = MA_FF;      /*当前分配算法*/
static int pid = 0;            /*初始pid*/
int flag = 0;                  /*设置内存大小标志,防止重复设置*/
void display_menu();
void do_exit();
struct free_block_type *init_free_block(int mem_size);
void set_mem_size();
void set_algorithm();
void new_process();
void kill_process();
void display_mem_usage();
void rearrange(int choice);
void rearrage_FF();
void rearrage_BF();
void rearrage_WF();
main(){
    char choice;   
    pid=0;
    free_block = init_free_block(mem_size); //初始化空闲区
	display_menu();	
    while(1) {
    	printf("请选择（0-5）: ");
    	fflush(stdin);
    	choice=getchar();	//获取用户输入
    	switch(choice){
     		case '1': 
			  set_mem_size(); //设置内存大小
			  system("cls");
			  break; 	
     		case '2': 
			  set_algorithm();//设置算法
			  flag=1;
			  system("cls");
			  break;
      		case '3':
			  new_process();//创建新进程
			  flag=1; 
			  system("cls");	 
			  break;
       		case '4':
			  kill_process();//删除进程
		  	flag=1;  
		 	system("cls"); 
		  	break;
        	case '5':
		  		display_mem_usage();//显示内存使用
	        	  flag=1; 
			  break;	
      	  case '0':
			  do_exit();//释放链表并退出
			  exit(0);	
      		  default: break;   
  		 }  
   choice=getchar();
  } 
}
//紧缩处理
void free_memory_rearrage(int memory_reduce_size,int allocated_size){
	struct free_block_type *p1,*p2;
	struct allocated_block *a1,*a2;
	if(memory_reduce_size!=0) //分配完还有小块空间
	{
		p1=free_block;
		p2=p1->next;
		p1->start_addr=0;
		p1->size=memory_reduce_size;
		p1->next=NULL;
		mem_size=memory_reduce_size;  //
	}
	else{
		p2=free_block;
		free_block=NULL;
		mem_size=0;
	}
	while(p2!=NULL)//释放节点
	{
		p1=p2;
		p2=p2->next;
		free(p1);
	}
        //allocated_block 重新修改链接
		a1=(struct allocated_block *)malloc(sizeof(struct allocated_block));
		a1->pid=pid;
		a1->size=allocated_size;
		a1->start_addr=memory_reduce_size; //已申请的开始地址，从memory_reduce_size开始
		sprintf(a1->process_name, "PROCESS-%02d", pid);
		a1->next=allocated_block_head;
		a2=allocated_block_head;
		allocated_block_head=a1;
	while(a2!=NULL){
		a2->start_addr=a1->start_addr+a1->size;
		a1=a2;
		a2=a2->next;
	}
}
int allocate_mem(struct allocated_block *ab){
	//根据当前算法在空闲分区链表中搜索合适空闲分区进行分配，分配时注意以下情况：
	// 1. 找到可满足空闲分区且分配后剩余空间足够大，则分割
	// 2. 找到可满足空闲分区且但分配后剩余空间比较小，则一起分配
	// 3. 找不可满足需要的空闲分区但空闲分区之和能满足需要，则采用内存紧缩技术，进行空闲分区的合并，然后再分配
	// 4. 在成功分配内存后，应保持空闲分区按照相应算法有序
	// 5. 分配成功则返回1，否则返回-1
	struct free_block_type *fbt, *pre;
	int request_size=ab->size;
 	//int memory_count;//计算剩余分区总内存大小
	fbt = pre = free_block;
	while((pre!=NULL)&&(request_size>pre->size))//遍历查找匹配空白区
	{
		//memory_count+=pre->size;
		fbt=pre;
		pre=pre->next;   
	}
	if(!pre)  //pre=pre->next结尾
	{
		if(mem_size>=request_size)/*memory_count*/
		{
			if(mem_size>=request_size+MIN_SLICE)
				free_memory_rearrage(mem_size-request_size,request_size); //采用紧缩技术
			else	
				free_memory_rearrage(0,mem_size); //采用紧缩技术,空间全部分配
			return 0;//全部重定位,不返回上级
		}
		else
			return -1;//分配失败!
	}
	else  //内存能满足 request_size<=pre->size
	{
		if((pre->size-request_size)>MIN_SLICE)//找到可满足空闲分区且分配后剩余空间足够大，则分割
		{
		pre->size=pre->size-request_size;
		ab->start_addr=pre->start_addr+pre->size;
		}
		else//找到可满足空闲分区且但分配后剩余空间比较小，则一起分配，删除该节点
		{
			if(pre==fbt){	
				fbt=pre->next;
				free_block=fbt;
			}
			else
				fbt->next=pre->next;
			ab->start_addr=pre->start_addr;
			ab->size=pre->size;
			free(pre);//释放节点
			}
	}
	mem_size-=ab->size;//...
	rearrange(ma_algorithm);//分配成功，按照相应算法排序
    return 1;
}
void new_process(){
	struct allocated_block *ab;
	int size;
	int ret;/*ret==1表示从空闲分区分配空间成功*/
	if(mem_size==0){
		printf("内存全部分配！无法创建新进程，请先释放其他进程！\n");
		return;
	}
	ab=(struct allocated_block *)malloc(sizeof(struct allocated_block));
	if(ab==NULL){
		printf("No Mem!\n");
		exit(1);
	}
	ab->next=NULL;
	pid++;
	sprintf(ab->process_name,"PROCESS-%02d",pid);//字符串格式化
	ab->pid=pid;
	while(1){
		printf("请输入内存 %s(0-%d):",ab->process_name,mem_size);
		scanf("%d",&size);
		if(size<=mem_size&&size>0){
			ab->size=size;
			break;	
		}
		printf("请重新输入！\n");
	}
	ret=allocate_mem(ab);//从空闲内存分配空间
        /*如果此时allocated_block_head尚未赋值，则赋值*/
        if((ret==1) &&(allocated_block_head == NULL))
	allocated_block_head=ab;
  	else if(ret==1) /*分配成功，将该已分配块的描述插入已分配链表(头插<无头节点>)*/
	{
        ab->next=allocated_block_head;
        allocated_block_head=ab;
	}
	else if(ret==-1)/*分配不成功*/
	{ 
        printf("分配失败！\n");
        free(ab);    
	return;
     	}
	printf("分配成功！\n");
}
struct allocated_block *find_process(int pid){
	struct allocated_block *p;
	p=allocated_block_head;
	while(p){
	if(p->pid==pid)
		return p;
	p=p->next;
	}
	return p;
}
/*释放ab所表示的分配区*/
int free_mem(struct allocated_block *ab){ 
	int algorithm = ma_algorithm;
	struct free_block_type *fbt,*pre,*work;
	mem_size+=ab->size;
	fbt=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	if(!fbt)
		return -1;
	fbt->size = ab->size;
	fbt->start_addr=ab->start_addr;
	fbt->next=NULL;
	rearrange(MA_FF);//按地址有序排列
	// 进行可能的合并，基本策略如下
	// 1. 将新释放的结点插入到空闲分区队列末尾
	// 2. 对空闲链表按照地址有序排列
	// 3. 检查并合并相邻的空闲分区
	// 4. 将空闲链表重新按照当前算法排序
	pre=NULL;
	work=free_block;
	//查找插入位置
	while((work!=NULL)&&(fbt->start_addr>work->start_addr)){
	pre=work;
	work=work->next;
	}
 	//插入当前节点
	//回收内存四种情况
		//1）回收区与前一个空闲分区相邻接，与前一分区合并，修改前一分区的大小
		//2）回收区与插入点的后一空闲分区相邻接，将两个分区合并，形成新的分区。（用回收区的首地址作为新分区的首地址，大小为其之和）
		//3）回收区同时与前后两个空闲分区相邻接，合并三个分区，首地址为第一个分区的首址，大小为三个之和
		//4）回收区与之均不邻接，建立新表项
	if(!pre)//插入开始位置
	{
		if (!work){
			 free_block=fbt; 
		}else{
			fbt->next=work;
		    free_block=fbt;
			if(fbt->start_addr+fbt->size==work->start_addr){	
				fbt->next=work->next;
				fbt->size=fbt->size+work->size;
				free(work);
			}
		}
	}
	else{
		if(!work){
			pre->next=fbt;
			if(fbt->start_addr==pre->start_addr+pre->size){
				pre->next=work;
				pre->size=fbt->size+pre->size;
				free(fbt);
			}
		}
		else{
			fbt->next=work;
			pre->next=fbt;
		// 检查并合并相邻的空闲分区
			if((fbt->start_addr== pre->start_addr+pre->size)&&(fbt->start_addr+fbt->size == work->start_addr)){
				pre->next=work->next;
				pre->size=pre->size+fbt->size+work->size;
				free(fbt);
				free(work);
			}
			else if(fbt->start_addr== pre->start_addr+pre->size){
				pre->next=work;
				pre->size=pre->size+fbt->size;
				free(fbt);
			}
			else if(work->start_addr==fbt->start_addr+fbt->size) {
				fbt->next=work->next;
				fbt->size=work->size+fbt->size;
				free(work);
			}
		}
	}
	// 将空闲链表重新按照当前算法排序
	rearrange(ma_algorithm);  
	return 1;
}
/*释放ab数据结构节点*/
void dispose(struct allocated_block *free_ab){
	struct allocated_block *pre,*ab;
	if(free_ab==allocated_block_head)/*如果要释放第一个节点*/
	{
		allocated_block_head=free_ab->next;
		free(free_ab);
		return ;
	}
	pre=allocated_block_head;
	ab=allocated_block_head->next;
	while(ab!=free_ab){
		pre=ab;
		ab=ab->next;
	}
	pre->next=ab->next;
	free(ab);
}
void kill_process(){
	struct allocated_block *ab;
	int pid;
	printf("终止进程，输入序号 = ");
	scanf("%d",&pid);
	ab=find_process(pid);
	if(ab!=NULL){
	free_mem(ab);/*释放ab所表示的分配区*/
	dispose(ab);/*释放ab数据结构节点*/	
	printf("终止进程成功！\n");
	return;
	}
	printf("终止进程失败！\n");
}
/* 显示当前内存的使用情况，包括空闲区的情况和已经分配的情况 */
void display_mem_usage(){
	struct free_block_type *fbt=free_block;
	struct allocated_block *ab=allocated_block_head;
	/* 显示空闲区 */
	printf("----------------------------------------------------------\n");
	if(fbt==NULL)
	printf("内存全部分配!\n");
	else{
	printf("空闲存储器:\n");
	printf("%20s %20s\n", "起始地址", "大小");
	while(fbt!=NULL){
	printf("%17d %23d\n", fbt->start_addr, fbt->size);
        fbt=fbt->next;
	}
	}	printf("----------------------------------------------------------\n");
	/* 显示已分配区 */
	if(ab==NULL)
	printf("尚未开始分配!\n");
	else{
	printf("\nUsed Memory:\n");
	printf("%10s %15s %15s %10s\n", "\t序号", "进程名称", "起始地址", "大小");
    	while(ab!=NULL){
        printf("%10d %18s %12d %11d\n", ab->pid, ab->process_name, ab->start_addr, ab->size);
        ab=ab->next;
        }
	}
	printf("----------------------------------------------------------\n");
}
/*按BF算法重新整理内存空闲块链表*/
void rearrage_BF(){
	struct free_block_type *p,*p1,*p2;
	struct free_block_type *last_flag;
	p1=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	p1->next=free_block;
    free_block=p1;//不改变p1,free_block指向头p1
	if(free_block!=NULL){
		for (last_flag=NULL; last_flag!=free_block; last_flag=p){
			for (p=p1=free_block; p1->next!=NULL&&p1->next->next!=NULL&&p1->next->next!=last_flag; p1=p1->next){
			   if (p1->next->size > p1->next->next->size){
				p2 = p1->next->next;  
				p1->next->next = p2->next;
				p2->next = p1->next; 
				p1->next = p2; 
				p = p1->next->next; 
			   }
			}
		}	
	}
	p1 = free_block; 
	free_block = free_block->next; 
	free(p1); 
	p1 = NULL; 
}
/*按WF算法重新整理内存空闲块链表*/
void rearrage_WF(){
	struct free_block_type *p,*p1,*p2;
	struct free_block_type *last_flag;
	p1=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	p1->next=free_block;
    free_block=p1;//不改变p1,free_block指向头p1
	if(free_block!=NULL){
		for (last_flag=NULL; last_flag!=free_block; last_flag=p){
		for (p=p1=free_block; p1->next!=NULL&&p1->next->next!=NULL&&p1->next->next!=last_flag; p1=p1->next){
		   if (p1->next->size < p1->next->next->size) {
			p2 = p1->next->next;  
			p1->next->next = p2->next; 
			p2->next = p1->next; 
			p1->next = p2; 
			p = p1->next->next; 
		   }
		}
	}
	}
	p1 = free_block; 
	free_block = free_block->next; 
	free(p1); 
	p1 = NULL; 
}
void rearrage_FF(){
	struct free_block_type *p,*p1,*p2;
	struct free_block_type *last_flag;
	p1=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	p1->next=free_block;
    free_block=p1;//不改变p1,free_block指向头p1
	if(free_block!=NULL){
		for (last_flag=NULL; last_flag!=free_block; last_flag=p){
			for (p=p1=free_block;p1->next!=NULL&&p1->next->next!=NULL &&p1->next->next!=last_flag; p1=p1->next){
			   if (p1->next->start_addr > p1->next->next->start_addr) {
				p2 = p1->next->next;  
				p1->next->next = p2->next; 
				p2->next = p1->next; 
				p1->next = p2; 
				p = p1->next->next; 
			   }
			}
		}
	}
	p1 = free_block; 
	free_block = free_block->next; 
	free(p1); 
	p1 = NULL; 
}
struct free_block_type *init_free_block(int mem_size){
	struct free_block_type *fb;
	fb=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	if(fb==NULL){
		printf("No Mem!\n");
		exit(1);
	}
	fb->size=mem_size;
	fb->start_addr=DEFAULT_MEM_START;
	fb->next=NULL;
	return fb;
}
void display_menu(){
    printf("\n");
	printf("----------------------------------------------------------\n");
	printf("                    存储器管理实验 \n");
    printf("1 - 设置内存大小 (default=%d)\n", DEFAULT_MEM_SIZE);
    printf("2 - 选择内存分配算法\n");
    printf("3 - 创建进程 \n"); 
    printf("4 - 终止进程 \n");
    printf("5 - 显示内存使用情况 \n");
    printf("0 - 退出\n");
	printf("----------------------------------------------------------\n");
}
void rearrange(int choice){
	switch(choice){
	case 1:rearrage_FF();
	       break;
	case 2:rearrage_BF();
	       break;
	case 3:rearrage_WF();
		   break;
	}
}
void set_algorithm(){
    int algorithm;
    printf("\t1 - 首次适应算法\n");
    printf("\t2 - 最佳适应算法 \n");
    printf("\t3 - 最差适应算法 \n");
    scanf("%d", &algorithm);
    if(algorithm>=1 && algorithm <=3)  
		ma_algorithm=algorithm;
    rearrange(ma_algorithm); //按指定算法重新排列空闲区链表
}
void set_mem_size(){
    int size;
    if(flag!=0){  
        printf("无法再次设置内存大小，或您已经开始使用内存！\n");
	return;
    }
    printf("总内存大小 =");
    scanf("%d", &size);
    if(size>0){
        mem_size = size;
        free_block->size = mem_size;
    }
    flag=1;  
}
void do_exit(){
	struct free_block_type *p1,*p2;
	struct allocated_block *a1,*a2;
	p1=free_block;
	if(p1!=NULL){
	p2=p1->next;
	for(;p2!=NULL;p1=p2,p2=p2->next){
		free(p1);
	}
	free(p1);
	}
	a1=allocated_block_head;
	if(a1!=NULL){
		a2=a1->next;
		for(;a2!=NULL;a1=a2,a2=a2->next){
			free(a1);	
		}
		free(a1);
	}
}
