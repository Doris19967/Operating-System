#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include<windows.h>

#define MAXQUEUENUM 10
#define getpch(type)(type*)malloc(sizeof(type))
typedef struct Job JCB;
int tatalResourceMainMemory = 100;
int totalResourceTapeNum = 5;
int choiceOrder = 0;//作业被选中运行的次数

//作业控制块
struct Job
{
char userName[10];
//用户名
char jobName[10]; 
//作业名
char state; 
//作业状态,W表示后备，R表示执行，F表示完成
int reachTime[2];
//索引0表示小时,1表示分钟
int runTime;
//所需的运行时间，以分钟为单位
int resourceMainMemory;
//所需的内存空间，单位为KB
int resourceTapeNum;
//所需的磁带机数
int order;
//被选中运行的次数，数字越小表示越先被选中
JCB* next;
// 指针，指向下一个JCB
}*headJCB=NULL,*endJCB=NULL,*headJCBFish=NULL,*endJCBFish;


//进程控制块
struct pcb{    
/*定义进程控制块PCB*/
char name[10];
//存储用户名
char state;
//状态
int grade;
//队列的级数, 最大值为MAXQUEUENUM
int ntime;   
//假定时间片以分钟为单位
int rtime;
//已经运行的时间
struct pcb* link;
}*head[MAXQUEUENUM],*end[MAXQUEUENUM],*p; 

typedef struct pcb PCB;


//进程控制块相关操作
void createPCB(JCB* jcbObj)
//建立进程控制块函数,把ptr所指向进程插入第一队列的末尾
{
p=getpch(PCB);
strcpy(p->name,jcbObj->jobName);
p->state = 'w';
//初始化为后备状态
p->grade = 1;
//初始化队列级别为1
p->ntime = jcbObj->runTime;
p->rtime = 0;
//已运行的时间初始化为0
p->link = NULL;
//初始化没有连接下一个
}

//把新创建的PCB块添加到对应序号的PCB链当中
void  addPCBIntoList(int index)
{
if(head[index]==NULL)
head[index] = end[index] = p;
else
{
end[index]->link = p;
end[index] = end[index]->link;
}
p = NULL;
}


void disp(PCB *pr)
/*显示特定PCB块的信息*/
{

printf("\n 作业名\t 状态 \t 等级\t 需要时间\t 运行时间 \n");
printf("%s	",pr->name);
printf("%c	",pr->state);
printf("%d	",pr->grade);
printf("%d	",pr->ntime);
printf("%d	",pr->rtime);
printf("\n");
}

void check(PCB* ptr)
/*建立进程查看函数*/
{
int j = 0;
printf("\n ****当前正在运行的进程是:%s",ptr->name);
/*显示当前运行的进程*/
//printf("***************当前进程信息***************************");
disp(ptr);

printf("\n****当前就绪队列状态为:\n");
/*显示就绪队列状态*/
for(j=ptr->grade-1; j<MAXQUEUENUM; j++)
{
PCB*  temp =  NULL;
if(j==ptr->grade-1)
//还为当前队列，要特殊考虑
{
if(head[j]->link == NULL)
continue;
temp = head[j]->link;
}
else if(head[j] == NULL)
//空队列，跳过
continue;
else
temp = head[j];
while(temp)
//打印出本PCB链的信息
{        disp(temp);
temp = temp->link;
}
}
}

//显示所有PCB队列中的PCB块的信息
void printAllProcesses()
{
int i;
for(i=0; i<MAXQUEUENUM; i++)
{
PCB* temp = head[i];
while(temp)
{
disp(temp);
temp =  temp->link;
}
}
}

//不同级数的进程时间片长度的计算
int runTime(int grade)
{
return (int)pow(2,grade-1);
}

//销毁进程及对应的作业
void jobInvoke();
//提前声明
void addFinishJob(JCB* finishJCB);
//提前声明

void destroy()
{
char jobName[10];
JCB* temp = headJCB;
JCB* pre = NULL;
//一个辅助指针
printf("进程[%s]已经完成了,对应作业[%s]完成，已经从作业队列中删除......\n",p->name,p->name);
strcpy(jobName,p->name);
free(p);
p = NULL;
//从作业队列当中删除该进程对应的作业
while(temp)
{
if(strcmp(temp->jobName,jobName)==0)
//说明该作业已经完成，可删除
{
temp->state = 'F';
if(headJCB == endJCB)
{//说明只有一个作业
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);
endJCB = NULL;    printf("\naaa1\n");
}
else if(headJCB == temp)
{//说明第一个作业已经完成了
headJCB = headJCB->next;
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);     printf("\naaa2\n");
}else if(endJCB == temp)
{//说明最后一个作业完成了
endJCB = pre;
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);     printf("\naaa3\n");
}else
{//最一般的情况
pre->next = temp->next;
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);      printf("\naaa4\n");
}
}
pre = temp;
if(temp)
temp = temp->next;
}
jobInvoke();
}

//进程运行函数
void run()
{
int i;
for(i=0; i<MAXQUEUENUM; i++)
{        
if(head[i] == NULL)
continue;
p = head[i];
check(p);

head[i] = head[i]->link;
if(head[i] == NULL)//若只有一个pcb块，则取走后尾指针应赋为空
end[i] = NULL;
p->link = NULL;
if(runTime(p->grade)+p->rtime < p->ntime)
{
//把该进程插到下一队列的末尾
p->rtime += runTime(p->grade);
if(p->grade ==  MAXQUEUENUM)//最后一个队列，仍然插到本队列
addPCBIntoList(MAXQUEUENUM-1);

else//插到下一个队列当中
addPCBIntoList(p->grade++);
return ;
}
else
//说明该进程已经完成
destroy();
return ;
}
}



//作业控制块相关操作


void addJCB(JCB* newJCB)
//把作业控制块添加到后备作业链当中
{
if(newJCB==NULL)
return ;
if(headJCB==NULL)
{//未有作业
endJCB = headJCB = newJCB;
}
else
{//队列未空，直接插入到队尾
endJCB->next = newJCB;
endJCB = endJCB->next;
}
newJCB = NULL;
}

//为新的作业创建JCB控制块
void createJCB()
{
JCB* newJCB = getpch(JCB);
//分配存储空间
if(newJCB == NULL)
{
printf("系统内存不够!\n");
exit(-1);
}
printf("----》请输入用户名: ");
scanf("%s",newJCB->userName);
printf("\n----》请输入作业名: ");
scanf("%s",newJCB->jobName);
printf("\n----》请输入作业的到达时间:(如13 20)");
scanf("%d %d",&newJCB->reachTime[0],&newJCB->reachTime[1]);
printf("\n----》请输入运行时间: ");
scanf("%d",&newJCB->runTime);
printf("\n----》请输入所需的主存空间(K): ");
scanf("%d",&newJCB->resourceMainMemory);
printf("\n----》请输入所需的磁带机数: ");
scanf("%d",&newJCB->resourceTapeNum);
newJCB->order = 0;
newJCB->state = 'w';
newJCB->next = NULL;
getchar();
addJCB(newJCB);
//添加到JCB链中
printf("创建作业成功.\n");
jobInvoke();
//作业调度
}

//动态创建并初始化单个作业控制块，并返回其指针
JCB* initJCB(char* userName,  char* jobName, char state, int reachTime[], int runTime,
int resourceMainMemory, int resourceTapeNum)
{
JCB* newJCB = (JCB*)malloc(sizeof(JCB));
if(newJCB == NULL)
{
printf("内存空间不够!");
exit(1);
}
strcpy(newJCB->userName,userName);
//用户名复制
strcpy(newJCB->jobName,jobName);
newJCB->state = state;
newJCB->reachTime[0] = reachTime[0];
newJCB->reachTime[1] = reachTime[1];
newJCB->runTime = runTime;
newJCB->resourceMainMemory = resourceMainMemory;
newJCB->resourceTapeNum = resourceTapeNum;
newJCB->next = NULL;
newJCB->order = 0;
return newJCB;
//返回指针
}

//系统自动创建并初始化5个作业控制块
void initJCBLinkList()
{
JCB* newJCB = NULL;
int reachTime[5][2]={9,0,9,20,9,30,9,35,9,45};
newJCB = initJCB("用户一","作业一",'w',reachTime[0],15,20,2);
addJCB(newJCB);
newJCB = initJCB("用户二","作业二",'w',reachTime[1],18,60,1);
addJCB(newJCB);
newJCB = initJCB("用户三","作业三",'w',reachTime[2],9,45,3);
addJCB(newJCB);
newJCB = initJCB("用户四","作业四",'w',reachTime[3],12,10,2);
addJCB(newJCB);
newJCB = initJCB("用户五","作业五",'w',reachTime[4],6,25,3);
addJCB(newJCB);
}

void dispMenu()
{
system("cls");
printf("********************************************************");
printf("\t\t\t  作业调度模拟程序    高胜立 网络二班  3109006516   \n");
printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
printf("→\t\t1:  增加作业        \n");
printf("→\t\t2:  查询作业状态    \n");
printf("→\t\t3:  查询已完成作业  \n");
printf("→\t\t4:  查看当前进程    \n");
printf("→\t\t5:  执行            \n");
printf("→\t\t6:  退出            \n");
}

//打印输出作业队列的信息
void dispJCBLinkList()
{
JCB* jcbTemp = headJCB;
if(jcbTemp == NULL)
{
printf("当前没有作业处于后备队列当中\n");
return ;
}
printf("用户名\t作业名\t状态\t到达时间\t运行时间\t主存\t磁带机\t调用次序\n");
while(jcbTemp)
{
printf("%s\t",jcbTemp->userName);
printf("%s\t",jcbTemp->jobName);
printf("%c\t",jcbTemp->state);
if(jcbTemp->reachTime[1] != 0)
printf("%d:%d\t\t",jcbTemp->reachTime[0],jcbTemp->reachTime[1]);
else
printf("%d:%d0\t\t",jcbTemp->reachTime[0],jcbTemp->reachTime[1]);
printf("%d\t\t",jcbTemp->runTime);
printf("%dK\t",jcbTemp->resourceMainMemory);
printf("%d\t",jcbTemp->resourceTapeNum);
printf("%d\n",jcbTemp->order);
jcbTemp = jcbTemp->next;
}
}

void jobInvoke()
//作业调度核心模块
{
JCB* temp = headJCB;
while(temp)
{
if(temp->resourceMainMemory<=tatalResourceMainMemory
&& temp->resourceTapeNum<=totalResourceTapeNum  && temp->state=='w')
{
//此时可将此作业调进内存
tatalResourceMainMemory -= temp->resourceMainMemory;
totalResourceTapeNum -= temp->resourceTapeNum;
temp->state = 'R';
temp->order = ++choiceOrder;
printf("注意!作业%s已被调入内存运行...\n",temp->jobName);
createPCB(temp);
addPCBIntoList(0);
}
temp = temp->next;
}
}
//把已完成的JCB块添加到已完成作业链当中
void addFinishJob(JCB* finishJCB)
{
if(headJCBFish==NULL)
headJCBFish = endJCBFish = finishJCB;
else
{
endJCBFish->next = finishJCB;
endJCBFish = endJCBFish->next;
}
}

//打印输出所有已完成作业的信息
void printFinishJCB()
{
JCB* jcbTemp = headJCBFish;
if(jcbTemp == NULL)
{
printf("当前没有作业已经完成\n");
return ;
}
printf("用户名\t作业名\t状态\t到达时间\t运行时间\t主存\t磁带机\t调用次序\n");
while(jcbTemp)
{
printf("%s\t",jcbTemp->userName);
printf("%s\t",jcbTemp->jobName);
printf("%c\t",jcbTemp->state);
if(jcbTemp->reachTime[1] != 0)
printf("%d:%d\t\t",jcbTemp->reachTime[0],jcbTemp->reachTime[1]);
else
printf("%d:%d0\t\t",jcbTemp->reachTime[0],jcbTemp->reachTime[1]);
printf("%d\t\t",jcbTemp->runTime);
printf("%dK\t",jcbTemp->resourceMainMemory);
printf("%d\t",jcbTemp->resourceTapeNum);
printf("%d\n",jcbTemp->order);
jcbTemp = jcbTemp->next;
}
}

int main()
{
int quit = 0;
dispMenu();
initJCBLinkList(); //作业自动初始化
printf("系统已自动完成5个作业的初始化任务.\n");
jobInvoke();//初始化作业的进程调度
while(!quit)
{
char choice;
printf("请按回车键继续.");
getchar();
dispMenu();
printf("请输入指令: ");

scanf("%c",&choice);
switch(choice)
{
case '1'://添加作业
createJCB();
break;

case '2'://查看作业
dispJCBLinkList();
break;             

case '3'://查询已完成作业
printFinishJCB();
break;
case '4':
printf("当前正在运行的进程状态如下:\n");
printAllProcesses();
break;
case '5'://执行进程
run();
break;
case '6'://退出while循环
quit = 1;
break;

default:
printf("无效指令，请重新输入指令.\n");
break;
}
getchar();
}
printf("感谢您对本系统的使用.\n");
printf("按任意键离开.");
getchar();
return 0;
}
