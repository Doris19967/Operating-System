#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct PCB
{
	char ID[15];//进程名字
	int Atime; //进程到达时间
	int Stime;//进程服务时间
	int Ctime;//进程完成时间
	int ZZtime;//周转时间
	int tag;//是否运行过
	int num;//数字编号
	double DQtime;//加权周转时间
	struct PCB *next;
}PCB,*P_PCB;

void FCFS(P_PCB start);
void SJF(P_PCB start);
void QSJF(P_PCB start);
void RR(P_PCB start);
void RR1(P_PCB start);
void HRN(P_PCB start);
int process_sum = 0;//进程的总数

int Enter(P_PCB start)
{
	int i;
	PCB* LAST=start;
	printf("请输入进程的个数：");
	scanf("%d", &process_sum);
	for (i = 0; i < process_sum; i++)
	{
		//录入第i个进程的信息
		P_PCB newHead;
		newHead = (P_PCB)malloc(sizeof(PCB));//新的节点
		printf("请输入进程%d的名字:", i+1);
		scanf("%s", newHead->ID);
		printf("请输入进程%d的到达时间:", i+1);
		scanf("%d", &newHead->Atime);
		printf("请输入进程%d的服务时间:", i+1);
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
	printf("进程的信息如下：\n");
	while (p->next!= NULL)
		{
			p = p->next;
			printf("进程名字%s  ,到达时间:%d  ,服务时间:%d\n", p->ID, p->Atime, p->Stime);
		}
	return 0;
}

int Showresult(P_PCB start)
{
	int a = 0;
	P_PCB p = start;
	printf("\n进程的运行结果信息如下：\n");
	while (p->next!= NULL)
		{
			p = p->next;
			printf("进程名字%s  ,到达时间:%d  ,服务时间:%d  ,完成时间:%d  ,周转时间:%d  ,加权周转时间:%.3f\n", p->ID, p->Atime, p->Stime, p->Ctime, p->ZZtime, p->DQtime);
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
printf("F 先来先服务\n");
printf("S 短作业优先服务\n");
printf("Q 抢占式优先服务\n");
printf("R 轮转调度\n");
printf("H 高响应比优先调度\n");
printf("请输入调度算法：\n");

getchar();
scanf("%c",&c);
if(c=='0')
{
printf("程序结束退出\n");
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
printf("\n执行结果如下:\n");
printf("当前时间为：%d	,	当前执行进程为：%s	\n",f->Atime,f->ID);
for(i=1;i<process_sum;i++){
	if(f->Ctime<=l->Atime){
		l->Ctime=l->Stime+l->Atime;
		printf("当前时间为：%d	,	当前执行进程为：%s	\n",l->Atime,l->ID);
	}
	else{
		l->Ctime=l->Stime+f->Ctime;
		printf("当前时间为：%d	,	当前执行进程为：%s	\n",f->Ctime,l->ID);
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
	printf("\n执行结果如下:\n");
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
			printf("当前时间为：%d	,	当前执行进程为：%s	\n",Ctime,k->ID);
		}
		else{
			for(k=start->next;k!=NULL;k=k->next)
				if(k->tag==0)
					break;
			k->Ctime=k->Atime+k->Stime;
			printf("当前时间为：%d	,	当前执行进程为：%s	\n",k->Atime,k->ID);
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
	printf("\n执行结果如下:\n");
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
			printf("当前时间为：%d	,	当前执行进程为：%s	,	剩余执行时间为%d\n",time,k->ID,k->Stime);
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
			printf("当前时间为：%d	,	当前执行进程为：%s	,	剩余执行时间为%d\n",time,f->ID,f->Stime);
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
	printf("\n执行结果如下:\n");
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
			printf("当前时间为：%d	,	当前执行进程为：%s	\n",time,f->ID);
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
	printf("\n执行结果如下:\n");
	head->next=NULL;
	while(1){
			for(i=0;i<process_sum;i++)
				if(Start[i]->Atime==time){
					enqueue(tail,Start[i]);
				}
			if(head->next!=NULL){
				f=head->next;
				printf("当前时间为：%d	,	当前执行进程为：%s	\n",time,f->ID);
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
	printf("\n执行结果如下:\n");
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
			printf("当前时间为：%d	,	当前执行进程为：%s	\n",Ctime,k->ID);
		}
		else{
			for(k=start->next;k!=NULL;k=k->next)
				if(k->tag==0)
					break;
			k->Ctime=k->Atime+k->Stime;
			k->tag=1;
			printf("当前时间为：%d	,	当前执行进程为：%s	\n",k->Atime,k->ID);
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
