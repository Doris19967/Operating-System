#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
typedef int QElemType;
int MaxNume=100;
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
LinkQueue Queue;

typedef struct process_FCFS{
	char name;//������
	float arriveTIME;//����ʱ��
	float serveTIME;//����ʱ��
	float needTIME;//ʣ����Ҫ�ķ���ʱ��
	float finishTIME;//���ʱ��
	float roundTIME;//��תʱ��
	float daiquanTIME;//��Ȩ��תʱ��
	struct process_FCFS *link;//�ṹ��ָ��
}FCFS; 
FCFS *p,*q,*head=NULL;
struct process_FCFS a[100];

	float pian=1;
	float TIME;
    int n;//���̸���
bool flags=true;//��־С��ʱ��Ƭ��ʱ��Ƭ�����ù�	


FCFS inital(struct process_FCFS a[],int n);
void print(struct process_FCFS a[],int n);
void Fcfs(struct process_FCFS a[],int n);
struct process_FCFS *sortarriveTIME(struct process_FCFS a[],int n);
bool finished(struct process_FCFS a[],int n);
int InitQueue(LinkQueue &Q);
int DestroyQueue(LinkQueue &Q);
int EnQueue(LinkQueue &Q,QElemType e);
int RollQueue(LinkQueue &Q);
int getNextProcess(struct process_FCFS a[],int n,float dTime);
int killPian(int t,float TIMERemaining,bool flag);
struct process_FCFS *sortRR(struct process_FCFS a[],int n);


int InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	Q.front->next=NULL;
	return 1;
}
int DestroyQueue(LinkQueue &Q){
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}

	return 1;
}

int EnQueue(LinkQueue &Q,QElemType e){                //����һ���ڵ㵽��β
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(Q.front ==Q.rear )
		Q.front ->next =p;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return 1;
}
 int RollQueue(LinkQueue &Q){
	QueuePtr p;
	QElemType e;
	if(Q.front ==Q.rear )
		return 0;//�����ѿ�
	p=Q.front->next  ;
	e=p->data ;
	if(a[e].needTIME >0){
		if(p==Q.rear )
			return 1;
		else{
		Q.front->next =p->next ;
		Q.rear ->next =p;
		p->next =NULL;
		Q.rear =p;
		return 1;
		}
	}
	else if(a[e].needTIME ==0){
		if(p==Q.rear ){
			Q.front =Q.rear ;
			return 0;
		}
		else{
		Q.front->next =p->next ;
		free(p);
		return 1;
		}

	}

}
//������ʱ�����ð������
struct process_FCFS *sortarriveTIME(struct process_FCFS a[],int n)
{
	int i,j;
	struct process_FCFS t;
	int flag;
	for(i=1;i<n;i++)
	{
		flag=0;
		for(j=0;j<n-i;j++)
		{
			if(a[j].arriveTIME>a[j+1].arriveTIME)
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				flag=1;//����
			}
		}
		if(flag==0)//���һ��������û�����κν��������������
			break;
	}
	return a;
}
bool finished(struct process_FCFS a[],int n){
	for(int k=0;k<n;k++){
		if(a[k].needTIME>0)
			return false;
	}
	return true;
}

int killPian(int t,float TIMERemaining,bool flag){
	if(pian<1&&pian>0){
		flags=true;
	}
	if(a[t].needTIME>TIMERemaining){
			a[t].needTIME=a[t].needTIME-TIMERemaining;
			TIME=TIME+TIMERemaining;
			if(flags)
				pian=1;
			if(flag)
				t=getNextProcess(a,n,TIMERemaining);
			return t;
		}
		else if(a[t].needTIME==TIMERemaining){
				TIME=TIME+TIMERemaining;
				a[t].needTIME=0;
				a[t].finishTIME=TIME;
				a[t].roundTIME=TIME-a[t].arriveTIME;
				a[t].daiquanTIME=a[t].roundTIME/a[t].serveTIME;
				if(flags)
					pian=1;
				if(flag)
					t=getNextProcess(a,n,TIMERemaining);
				return t;
		}
		else if(a[t].needTIME<TIMERemaining){
			a[t].finishTIME=TIME+a[t].needTIME;
			a[t].roundTIME=a[t].finishTIME-a[t].arriveTIME;
			a[t].daiquanTIME=a[t].roundTIME/a[t].serveTIME;
			
			TIMERemaining=TIMERemaining-a[t].needTIME;
			TIME=TIME+a[t].needTIME;
			t=getNextProcess(a,n,TIMERemaining+a[t].needTIME);
			if(flags)
				pian=1;
			if(t==-1)
				return -1;
			else{
				killPian(t,TIMERemaining,false);
			}

		}

}
int getNextProcess(struct process_FCFS a[],int n,float dTime){    //������һ�����еĽ��̺�
	for(int l=0;l<n;l++){
		if(a[l].arriveTIME>TIME-dTime&&a[l].arriveTIME<=TIME)
			EnQueue(Queue,l);
	}
	int m=RollQueue(Queue);
	if(m==0&&!finished(a,n)){               //Խ����ʱ��հ�
		for(int r=0;r<n;r++){
			if(a[r].arriveTIME>TIME){
				
				for(int kk=0;kk>=0;kk++){
					if(TIME+kk*pian<=a[r].arriveTIME&&TIME+(kk+1)*pian>a[r].arriveTIME){
						break;
					}
					pian=pian-(a[r].arriveTIME-TIME-kk*pian);
				}
//				pian=pian-(a[r].arriveTIME-TIME-kk*pian);
				TIME=a[r].arriveTIME;
				EnQueue(Queue,r);
				flags=false;
			}
		}
	}
	else if(m==0&&finished(a,n)){
			return -1;                   //��ʣ�����Ҫִ�еĽ���
	}
	return Queue.front->next->data;                         
}
struct process_FCFS *sortRR(struct process_FCFS a[],int n){
	TIME=a[0].arriveTIME;
	int q=0;
	for(int pp=0;pp<n;pp++){
		if(a[pp].arriveTIME==a[0].arriveTIME ){
			EnQueue(Queue,pp);
		}
	}
	while(q!=-1){
		q=killPian(q,pian,true);
	}
	return a;
}

void print(struct process_FCFS a[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("here");
		printf("��������%c",a[i].name);
		printf("����ʱ�䣺%f",a[i].arriveTIME);
		printf("����ʱ�䣺%f",a[i].serveTIME);
		printf("���ʱ�䣺%f",a[i].finishTIME);
		printf("��תʱ�䣺%f",a[i].roundTIME);
		printf("��Ȩ��תʱ�䣺%f",a[i].daiquanTIME);
		printf("\n");
	}
}

//������
int main()
{
	InitQueue(Queue);
	n=5;//������ 
	srand(time(0));
	for(int i=0;i<n;i++)
	{
		printf("print %d process name:",i+1);
		scanf("%s",&a[i].name);
		printf("arrivetime");
		scanf("%f",&a[i].arriveTIME);
		printf("servetime");
		scanf("%f",&a[i].serveTIME);
		a[i].needTIME=a[i].serveTIME ;
	}
	*sortarriveTIME(a,n);
	*sortRR(a,n);
	printf("ʱ��Ƭ��ת�㷨\n");
	print(a,n);
	DestroyQueue(Queue);
	for(;;) ;
	return 0; 
}
