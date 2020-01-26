#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct PCB
{
	char ID[15];//��������
	int Atime; //���̵���ʱ��
	int Stime;//���̷���ʱ��
	int Ctime;//�������ʱ��
	int ZZtime;//��תʱ��
	int tag;//�Ƿ����й�
	int num;//���ֱ��
	double DQtime;//��Ȩ��תʱ��
	struct PCB *next;
}PCB,*P_PCB;

void FCFS(P_PCB start);
void SJF(P_PCB start);
void QSJF(P_PCB start);
void RR(P_PCB start);
void RR1(P_PCB start);
void HRN(P_PCB start);
int process_sum = 0;//���̵�����

int Enter(P_PCB start)
{
	int i;
	PCB* LAST=start;
	printf("��������̵ĸ�����");
	scanf("%d", &process_sum);
	for (i = 0; i < process_sum; i++)
	{
		//¼���i�����̵���Ϣ
		P_PCB newHead;
		newHead = (P_PCB)malloc(sizeof(PCB));//�µĽڵ�
		printf("���������%d������:", i+1);
		scanf("%s", newHead->ID);
		printf("���������%d�ĵ���ʱ��:", i+1);
		scanf("%d", &newHead->Atime);
		printf("���������%d�ķ���ʱ��:", i+1);
		scanf("%d", &newHead->Stime);
		printf("------------------------------------\n");
		/*system("cls");*/

		newHead->next = LAST->next;
		LAST->next = newHead;
		LAST=newHead;
	}
	return 0;
}

int Show(P_PCB start)
{
	int a = 0;
	P_PCB p = start;
	printf("���̵���Ϣ���£�\n");
	while (p->next!= NULL)
		{
			p = p->next;
			printf("��������%s  ,����ʱ��:%d  ,����ʱ��:%d\n", p->ID, p->Atime, p->Stime);
		}
	return 0;
}

int Showresult(P_PCB start)
{
	int a = 0;
	P_PCB p = start;
	printf("\n���̵����н����Ϣ���£�\n");
	while (p->next!= NULL)
		{
			p = p->next;
			printf("��������%s  ,����ʱ��:%d  ,����ʱ��:%d  ,���ʱ��:%d  ,��תʱ��:%d  ,��Ȩ��תʱ��:%.3f\n", p->ID, p->Atime, p->Stime, p->Ctime, p->ZZtime, p->DQtime);
		}
	return 0;
}

int main()
{
P_PCB start;
char c;
start = (P_PCB)malloc(sizeof(PCB));
start->next = NULL;
Enter(start);
Show(start);
while(1)
{
printf("------------------------------------\n");
printf("F �����ȷ���\n");
printf("S ����ҵ���ȷ���\n");
printf("Q ��ռʽ���ȷ���\n");
printf("R ��ת����\n");
printf("H ����Ӧ�����ȵ���\n");
printf("����������㷨��\n");

getchar();
scanf("%c",&c);
if(c=='0')
{
printf("��������˳�\n");
break;
}
switch(c)
{
case 'F': FCFS(start);break;
case 'S': SJF(start);break;
case 'Q': QSJF(start);break;
case 'R': RR(start);break;
case 'r': RR1(start);break;
case 'H': HRN(start);break;
default:printf("error");
}
}
return 0;
}

void FCFS(P_PCB start)
{
int i;
P_PCB f=start->next;
P_PCB l=f->next;
f->Ctime=f->Atime+f->Stime;
printf("\nִ�н������:\n");
printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",f->Atime,f->ID);
for(i=1;i<process_sum;i++){
	if(f->Ctime<=l->Atime){
		l->Ctime=l->Stime+l->Atime;
		printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",l->Atime,l->ID);
	}
	else{
		l->Ctime=l->Stime+f->Ctime;
		printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",f->Ctime,l->ID);
		}
	f=l;
	l=l->next;
}
f=start->next;
for(i=0;i<process_sum;i++){
f->ZZtime=f->Ctime-f->Atime;
f->DQtime=(float)f->ZZtime/(float)f->Stime;
f=f->next;
}
Showresult(start);
}

void enqueue(P_PCB &tail,P_PCB l){
	tail->next=l;
	l->next=NULL;
	tail=l;
}

void lunzhuan(P_PCB &head,P_PCB &tail){
	P_PCB p=head->next;
	if(p!=NULL&&p->next!=NULL){
		head->next=p->next;
		tail->next=p;
		p->next=NULL;
		tail=p;
	}
}

void outqueue(P_PCB &head,P_PCB &tail){
	P_PCB p=head->next;
	if(p==tail)
		tail=head;
	if(p!=NULL)
		head->next=p->next;
}

/*void nextjob(P_PCB start,P_PCB f){
	P_PCB k;
	P_PCB wait= (P_PCB)malloc(sizeof(PCB));
	int minstime;
	wait->next=null;
	for(k=start->next;k!=null;k=k->next){
		if(strcmp(k->ID,f->ID)!=0&&k->Atime<f->Ctime)
			enqueue(wait,k);
		if
	


	}
}*/

void SJF(P_PCB start){
	int minstime;
	int find;
	int Ctime=0;
	P_PCB i,j,k;
	int m;
	printf("\nִ�н������:\n");
	for(i=start->next;i!=NULL;i=i->next)
		i->tag=0;
	for(i=start->next;i!=NULL;i=i->next){
		find=0;
		minstime=10000;
		for(j=start->next;j!=NULL;j=j->next){
			if(j->tag==0&&j->Atime<=Ctime&&j->Stime<=minstime){
				minstime=j->Stime;
				k=j;
				find=1;
			}
		}
		if(find==1){
			k->Ctime=Ctime+k->Stime;
			k->tag=1;
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",Ctime,k->ID);
		}
		else{
			for(k=start->next;k!=NULL;k=k->next)
				if(k->tag==0)
					break;
			k->Ctime=k->Atime+k->Stime;
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",k->Atime,k->ID);
			k->tag=1;
		}
		Ctime=k->Ctime;
	}
	i=start->next;
	for(m=0;m<process_sum;m++){
		i->ZZtime=i->Ctime-i->Atime;
		i->DQtime=(float)i->ZZtime/(float)i->Stime;
		i=i->next;
	}
	Showresult(start);
}

void QSJF(P_PCB start){
	int num=0,time=0;
	int minstime=10000;
	int find;
	int Stime[100];
	P_PCB i,j,k,f;
	int m;
	i=start->next;
	printf("\nִ�н������:\n");
	for(m=0;m<process_sum;m++,i=i->next){
		i->tag=0;
		i->num=m;
		Stime[m]=i->Stime;
	}
	while(1){
		find=0;
		for(j=start->next;j!=NULL;j=j->next){
			if(j->tag!=1&&j->Atime<=time&&j->Stime<minstime){
				minstime=j->Stime;
				k=j;
				find=1;
			}
		}
		if(find==1){
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	,	ʣ��ִ��ʱ��Ϊ%d\n",time,k->ID,k->Stime);
			k->Stime--;
			minstime--;
			time++;
			f=k;
			if(k->Stime==0){
				k->Ctime=time;
				k->Stime=Stime[k->num];
				k->tag=1;
				num++;
				minstime=10000;
			}
		}
		else{
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	,	ʣ��ִ��ʱ��Ϊ%d\n",time,f->ID,f->Stime);
			f->Stime--;
			minstime--;
			time++;
			if(f->Stime==0){
				f->Ctime=time;
				f->Stime=Stime[f->num];
				f->tag=1;
				num++;
				minstime=10000;
			}
		}
		if(num==process_sum)
			break;
	}
	i=start->next;
	for(m=0;m<process_sum;m++){
		i->ZZtime=i->Ctime-i->Atime;
		i->DQtime=(float)i->ZZtime/(float)i->Stime;
		i=i->next;
	}
	Showresult(start);
}


void RR(P_PCB start)
{
	int i,flag=0,num=0,lunzhuan=0;
	int time;
	int Stime[100];
	P_PCB f=start->next,k;
	P_PCB wait= (P_PCB)malloc(sizeof(PCB));
	wait->next=NULL;
	time=0;
	k=start->next;
	printf("\nִ�н������:\n");
	for(i=0;i<process_sum;i++){
		Stime[i]=k->Stime;
		k->num=i;
		k=k->next;
	}
	for(k=start->next;k!=NULL;k=k->next)
		k->tag=0;
	while(1){
		flag=0;
		for(k=start->next;k!=NULL;k=k->next){
			if(k->Atime==time)
				k->tag=1;
		}
		/*Showresult(start);
		for(k=start->next;k!=NULL;k=k->next){
			printf("tag=%d\nAtime=%d\n",k->tag,k->Atime);
		}
		printf("time=%d\n",time);*/
		for(k=start->next;k!=NULL;k=k->next)
			if(k->tag==1)
				break;
		if(k==NULL){
			k=start->next;
			lunzhuan=0;
		}
		if(lunzhuan==1){
			while(f->next!=NULL){
				if(f->next->tag==1){
					f=f->next;
					flag=1;
					break;
				}
				else
					f=f->next;
			}
			if(f->next==NULL&&flag==0)
				f=k;
		}
		else
			f=k;
		if(f->tag==1){
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",time,f->ID);
			f->Stime--;
			time++;
			if(f->Stime==0){
				f->tag=2;
				f->Stime=Stime[f->num];
				f->Ctime=time;
				num++;
			}
			lunzhuan=1;
		}
		else 
			time++;
		if(num==process_sum)
			break;
	}
	f=start->next;
	for(i=0;i<process_sum;i++){
		f->ZZtime=f->Ctime-f->Atime;
		f->DQtime=(float)f->ZZtime/(float)f->Stime;
		f=f->next;
	}
	Showresult(start);
}

void RR1(P_PCB start)
{
	P_PCB Start[100];
	int Stime[100];
	P_PCB p=start->next;
	P_PCB f,k;
	int i,time=0,num=0;
	P_PCB head= (P_PCB)malloc(sizeof(PCB));
	P_PCB tail=head;
	for(i=0;i<process_sum;i++,p=p->next){
		Stime[i]=p->Stime;
		Start[i]=p;
		p->num=i;
	}
	printf("\nִ�н������:\n");
	head->next=NULL;
	while(1){
			for(i=0;i<process_sum;i++)
				if(Start[i]->Atime==time){
					enqueue(tail,Start[i]);
				}
			if(head->next!=NULL){
				f=head->next;
				printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",time,f->ID);
				f->Stime--;
				time++;
				if(f->Stime==0){
					Start[f->num]->Ctime=time;
					Start[f->num]->Stime=Stime[f->num];
					num++;
					outqueue(head,tail);
				}
				else {
					lunzhuan(head,tail);
				}
			}
			else
				time++;
		if(num==process_sum)
			break;
	}
	for(i=0;i<process_sum;i++){
		Start[i]->ZZtime=Start[i]->Ctime-Start[i]->Atime;
		Start[i]->DQtime=(float)Start[i]->ZZtime/(float)Start[i]->Stime;
	}
	start->next=Start[0];
	Start[process_sum-1]->next=NULL;
	for(i=0;i<process_sum-1;i++){
		Start[i]->next=Start[i+1];
	}
	Showresult(start);
}

void HRN(P_PCB start)
{
	float max;
	int find;
	int Ctime=0;
	P_PCB i,j,k;
	int m;
	printf("\nִ�н������:\n");
	for(i=start->next;i!=NULL;i=i->next)
		i->tag=0;
	for(i=start->next;i!=NULL;i=i->next){
		find=0;
		max=0;
		for(j=start->next;j!=NULL;j=j->next){
			if(j->tag==0&&j->Atime<Ctime&&(float)(Ctime-j->Atime+j->Stime)/(float)j->Stime>max){
				max=(float)(Ctime-j->Atime+j->Stime)/(float)j->Stime;
				k=j;
				find=1;
			}
		}
		if(find==1){
			k->Ctime=Ctime+k->Stime;
			k->tag=1;
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",Ctime,k->ID);
		}
		else{
			for(k=start->next;k!=NULL;k=k->next)
				if(k->tag==0)
					break;
			k->Ctime=k->Atime+k->Stime;
			k->tag=1;
			printf("��ǰʱ��Ϊ��%d	,	��ǰִ�н���Ϊ��%s	\n",k->Atime,k->ID);
		}
		Ctime=k->Ctime;
	}
	i=start->next;
	for(m=0;m<process_sum;m++){
		i->ZZtime=i->Ctime-i->Atime;
		i->DQtime=(float)i->ZZtime/(float)i->Stime;
		i=i->next;
	}
	Showresult(start);
}
