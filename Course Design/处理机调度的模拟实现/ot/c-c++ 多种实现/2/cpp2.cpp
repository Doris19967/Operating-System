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
int choiceOrder = 0;//��ҵ��ѡ�����еĴ���

//��ҵ���ƿ�
struct Job
{
char userName[10];
//�û���
char jobName[10]; 
//��ҵ��
char state; 
//��ҵ״̬,W��ʾ�󱸣�R��ʾִ�У�F��ʾ���
int reachTime[2];
//����0��ʾСʱ,1��ʾ����
int runTime;
//���������ʱ�䣬�Է���Ϊ��λ
int resourceMainMemory;
//������ڴ�ռ䣬��λΪKB
int resourceTapeNum;
//����ĴŴ�����
int order;
//��ѡ�����еĴ���������ԽС��ʾԽ�ȱ�ѡ��
JCB* next;
// ָ�룬ָ����һ��JCB
}*headJCB=NULL,*endJCB=NULL,*headJCBFish=NULL,*endJCBFish;


//���̿��ƿ�
struct pcb{    
/*������̿��ƿ�PCB*/
char name[10];
//�洢�û���
char state;
//״̬
int grade;
//���еļ���, ���ֵΪMAXQUEUENUM
int ntime;   
//�ٶ�ʱ��Ƭ�Է���Ϊ��λ
int rtime;
//�Ѿ����е�ʱ��
struct pcb* link;
}*head[MAXQUEUENUM],*end[MAXQUEUENUM],*p; 

typedef struct pcb PCB;


//���̿��ƿ���ز���
void createPCB(JCB* jcbObj)
//�������̿��ƿ麯��,��ptr��ָ����̲����һ���е�ĩβ
{
p=getpch(PCB);
strcpy(p->name,jcbObj->jobName);
p->state = 'w';
//��ʼ��Ϊ��״̬
p->grade = 1;
//��ʼ�����м���Ϊ1
p->ntime = jcbObj->runTime;
p->rtime = 0;
//�����е�ʱ���ʼ��Ϊ0
p->link = NULL;
//��ʼ��û��������һ��
}

//���´�����PCB����ӵ���Ӧ��ŵ�PCB������
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
/*��ʾ�ض�PCB�����Ϣ*/
{

printf("\n ��ҵ��\t ״̬ \t �ȼ�\t ��Ҫʱ��\t ����ʱ�� \n");
printf("%s	",pr->name);
printf("%c	",pr->state);
printf("%d	",pr->grade);
printf("%d	",pr->ntime);
printf("%d	",pr->rtime);
printf("\n");
}

void check(PCB* ptr)
/*�������̲鿴����*/
{
int j = 0;
printf("\n ****��ǰ�������еĽ�����:%s",ptr->name);
/*��ʾ��ǰ���еĽ���*/
//printf("***************��ǰ������Ϣ***************************");
disp(ptr);

printf("\n****��ǰ��������״̬Ϊ:\n");
/*��ʾ��������״̬*/
for(j=ptr->grade-1; j<MAXQUEUENUM; j++)
{
PCB*  temp =  NULL;
if(j==ptr->grade-1)
//��Ϊ��ǰ���У�Ҫ���⿼��
{
if(head[j]->link == NULL)
continue;
temp = head[j]->link;
}
else if(head[j] == NULL)
//�ն��У�����
continue;
else
temp = head[j];
while(temp)
//��ӡ����PCB������Ϣ
{        disp(temp);
temp = temp->link;
}
}
}

//��ʾ����PCB�����е�PCB�����Ϣ
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

//��ͬ�����Ľ���ʱ��Ƭ���ȵļ���
int runTime(int grade)
{
return (int)pow(2,grade-1);
}

//���ٽ��̼���Ӧ����ҵ
void jobInvoke();
//��ǰ����
void addFinishJob(JCB* finishJCB);
//��ǰ����

void destroy()
{
char jobName[10];
JCB* temp = headJCB;
JCB* pre = NULL;
//һ������ָ��
printf("����[%s]�Ѿ������,��Ӧ��ҵ[%s]��ɣ��Ѿ�����ҵ������ɾ��......\n",p->name,p->name);
strcpy(jobName,p->name);
free(p);
p = NULL;
//����ҵ���е���ɾ���ý��̶�Ӧ����ҵ
while(temp)
{
if(strcmp(temp->jobName,jobName)==0)
//˵������ҵ�Ѿ���ɣ���ɾ��
{
temp->state = 'F';
if(headJCB == endJCB)
{//˵��ֻ��һ����ҵ
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);
endJCB = NULL;    printf("\naaa1\n");
}
else if(headJCB == temp)
{//˵����һ����ҵ�Ѿ������
headJCB = headJCB->next;
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);     printf("\naaa2\n");
}else if(endJCB == temp)
{//˵�����һ����ҵ�����
endJCB = pre;
tatalResourceMainMemory += temp->resourceMainMemory;
totalResourceTapeNum += temp->resourceTapeNum;
temp->next = NULL;
addFinishJob(temp);     printf("\naaa3\n");
}else
{//��һ������
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

//�������к���
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
if(head[i] == NULL)//��ֻ��һ��pcb�飬��ȡ�ߺ�βָ��Ӧ��Ϊ��
end[i] = NULL;
p->link = NULL;
if(runTime(p->grade)+p->rtime < p->ntime)
{
//�Ѹý��̲嵽��һ���е�ĩβ
p->rtime += runTime(p->grade);
if(p->grade ==  MAXQUEUENUM)//���һ�����У���Ȼ�嵽������
addPCBIntoList(MAXQUEUENUM-1);

else//�嵽��һ�����е���
addPCBIntoList(p->grade++);
return ;
}
else
//˵���ý����Ѿ����
destroy();
return ;
}
}



//��ҵ���ƿ���ز���


void addJCB(JCB* newJCB)
//����ҵ���ƿ���ӵ�����ҵ������
{
if(newJCB==NULL)
return ;
if(headJCB==NULL)
{//δ����ҵ
endJCB = headJCB = newJCB;
}
else
{//����δ�գ�ֱ�Ӳ��뵽��β
endJCB->next = newJCB;
endJCB = endJCB->next;
}
newJCB = NULL;
}

//Ϊ�µ���ҵ����JCB���ƿ�
void createJCB()
{
JCB* newJCB = getpch(JCB);
//����洢�ռ�
if(newJCB == NULL)
{
printf("ϵͳ�ڴ治��!\n");
exit(-1);
}
printf("----���������û���: ");
scanf("%s",newJCB->userName);
printf("\n----����������ҵ��: ");
scanf("%s",newJCB->jobName);
printf("\n----����������ҵ�ĵ���ʱ��:(��13 20)");
scanf("%d %d",&newJCB->reachTime[0],&newJCB->reachTime[1]);
printf("\n----������������ʱ��: ");
scanf("%d",&newJCB->runTime);
printf("\n----�����������������ռ�(K): ");
scanf("%d",&newJCB->resourceMainMemory);
printf("\n----������������ĴŴ�����: ");
scanf("%d",&newJCB->resourceTapeNum);
newJCB->order = 0;
newJCB->state = 'w';
newJCB->next = NULL;
getchar();
addJCB(newJCB);
//��ӵ�JCB����
printf("������ҵ�ɹ�.\n");
jobInvoke();
//��ҵ����
}

//��̬��������ʼ��������ҵ���ƿ飬��������ָ��
JCB* initJCB(char* userName,  char* jobName, char state, int reachTime[], int runTime,
int resourceMainMemory, int resourceTapeNum)
{
JCB* newJCB = (JCB*)malloc(sizeof(JCB));
if(newJCB == NULL)
{
printf("�ڴ�ռ䲻��!");
exit(1);
}
strcpy(newJCB->userName,userName);
//�û�������
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
//����ָ��
}

//ϵͳ�Զ���������ʼ��5����ҵ���ƿ�
void initJCBLinkList()
{
JCB* newJCB = NULL;
int reachTime[5][2]={9,0,9,20,9,30,9,35,9,45};
newJCB = initJCB("�û�һ","��ҵһ",'w',reachTime[0],15,20,2);
addJCB(newJCB);
newJCB = initJCB("�û���","��ҵ��",'w',reachTime[1],18,60,1);
addJCB(newJCB);
newJCB = initJCB("�û���","��ҵ��",'w',reachTime[2],9,45,3);
addJCB(newJCB);
newJCB = initJCB("�û���","��ҵ��",'w',reachTime[3],12,10,2);
addJCB(newJCB);
newJCB = initJCB("�û���","��ҵ��",'w',reachTime[4],6,25,3);
addJCB(newJCB);
}

void dispMenu()
{
system("cls");
printf("********************************************************");
printf("\t\t\t  ��ҵ����ģ�����    ��ʤ�� �������  3109006516   \n");
printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
printf("��\t\t1:  ������ҵ        \n");
printf("��\t\t2:  ��ѯ��ҵ״̬    \n");
printf("��\t\t3:  ��ѯ�������ҵ  \n");
printf("��\t\t4:  �鿴��ǰ����    \n");
printf("��\t\t5:  ִ��            \n");
printf("��\t\t6:  �˳�            \n");
}

//��ӡ�����ҵ���е���Ϣ
void dispJCBLinkList()
{
JCB* jcbTemp = headJCB;
if(jcbTemp == NULL)
{
printf("��ǰû����ҵ���ں󱸶��е���\n");
return ;
}
printf("�û���\t��ҵ��\t״̬\t����ʱ��\t����ʱ��\t����\t�Ŵ���\t���ô���\n");
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
//��ҵ���Ⱥ���ģ��
{
JCB* temp = headJCB;
while(temp)
{
if(temp->resourceMainMemory<=tatalResourceMainMemory
&& temp->resourceTapeNum<=totalResourceTapeNum  && temp->state=='w')
{
//��ʱ�ɽ�����ҵ�����ڴ�
tatalResourceMainMemory -= temp->resourceMainMemory;
totalResourceTapeNum -= temp->resourceTapeNum;
temp->state = 'R';
temp->order = ++choiceOrder;
printf("ע��!��ҵ%s�ѱ������ڴ�����...\n",temp->jobName);
createPCB(temp);
addPCBIntoList(0);
}
temp = temp->next;
}
}
//������ɵ�JCB����ӵ��������ҵ������
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

//��ӡ��������������ҵ����Ϣ
void printFinishJCB()
{
JCB* jcbTemp = headJCBFish;
if(jcbTemp == NULL)
{
printf("��ǰû����ҵ�Ѿ����\n");
return ;
}
printf("�û���\t��ҵ��\t״̬\t����ʱ��\t����ʱ��\t����\t�Ŵ���\t���ô���\n");
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
initJCBLinkList(); //��ҵ�Զ���ʼ��
printf("ϵͳ���Զ����5����ҵ�ĳ�ʼ������.\n");
jobInvoke();//��ʼ����ҵ�Ľ��̵���
while(!quit)
{
char choice;
printf("�밴�س�������.");
getchar();
dispMenu();
printf("������ָ��: ");

scanf("%c",&choice);
switch(choice)
{
case '1'://�����ҵ
createJCB();
break;

case '2'://�鿴��ҵ
dispJCBLinkList();
break;             

case '3'://��ѯ�������ҵ
printFinishJCB();
break;
case '4':
printf("��ǰ�������еĽ���״̬����:\n");
printAllProcesses();
break;
case '5'://ִ�н���
run();
break;
case '6'://�˳�whileѭ��
quit = 1;
break;

default:
printf("��Чָ�����������ָ��.\n");
break;
}
getchar();
}
printf("��л���Ա�ϵͳ��ʹ��.\n");
printf("��������뿪.");
getchar();
return 0;
}
