#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct process_FCFS{
	char name;//������
	float arrivetime;//����ʱ��
	float servetime;//����ʱ��
	float finishtime;//���ʱ��
	float roundtime;//��תʱ��
	float daiquantime;//��Ӧ��
	struct process_FCFS *link;//�ṹ��ָ��
}FCFS; 
FCFS *p,*q,*head=NULL;
struct process_FCFS a[100];

FCFS inital(struct process_FCFS a[],int n);
void print(struct process_FCFS a[],int n);
void Fcfs(struct process_FCFS a[],int n);
struct process_FCFS *sortarrivetime(struct process_FCFS a[],int n);

struct process_FCFS *sortarrivetime(struct process_FCFS a[],int n)
{
	int i,j;
	struct process_FCFS t;
	int flag;
	for(i=1;i<n;i++)
	{
		flag=0;
		for(j=0;j<n-i;j++)
		{
			if(a[j].arrivetime>a[j+1].arrivetime)
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

void Fcfs(struct process_FCFS a[],int n)
{
	int i;
	a[0].finishtime=a[0].arrivetime+a[0].servetime;
    a[0].roundtime=a[0].finishtime-a[0].arrivetime;
	a[0].daiquantime=a[0].roundtime/a[0].servetime;
	for(i=1;i<n;i++)
	{
		if(a[i].arrivetime<a[i-1].finishtime)
		{
			a[i].finishtime=a[i-1].finishtime+a[i].servetime;
		    a[i].roundtime=a[i].finishtime-a[i].arrivetime;
		    a[i].daiquantime=a[i].roundtime/a[i].servetime;
		}
		else
		{
			a[i].finishtime=a[i].arrivetime+a[i].servetime;
            a[i].roundtime=a[i].finishtime-a[i].arrivetime;
	        a[i].daiquantime=a[i].roundtime/a[i].servetime;
		}
	}
	printf("�����ȷ���\n");
	print(a,n);
	
}

void print(struct process_FCFS a[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("��������%c ",a[i].name);
		printf("����ʱ�䣺%f ",a[i].arrivetime);
		printf("����ʱ�䣺%f ",a[i].servetime);
		printf("���ʱ�䣺%f ",a[i].finishtime);
		printf("��תʱ�䣺%f ",a[i].roundtime);
		printf("��Ӧ�ȣ�%f ",a[i].daiquantime);
		printf("\n");
	}
}

//������
int main()
{
	int n,i;
	n=10;//������ 
	srand(time(0));
	for(i=0;i<n;i++)
	{
		a[i].name=65+i; 
		a[i].arrivetime=((float)(rand()%100)/10);
		a[i].servetime=((float)(rand()%100)/10+rand()%10);
	}
	*sortarrivetime(a,n);
	Fcfs(a,n);
	for(;;);
	return 0;
}
