#include<iostream>  
#include<stdio.h>  
#include<string.h>  
#include <iomanip>
using namespace std;

const int PCB=10; //定义10个进程
void readData();//声明函数
int quantity;

typedef struct process
{  
    char pname[20];//进程名  
    struct process *next;   
	int BurstTime;//所需时间  
	int priority; // 数字越大优先级越高
	char Status;
}PROCESS;

PROCESS pcbs[PCB];

PROCESS * in_queue(PROCESS *head,PROCESS *p); //声明
PROCESS *init() //进程初始化
{
	cout<<"初始化程序：\n";
	int i=0;
	char a='y';
	PROCESS *head_new; //队列的队头
	head_new=(struct process*)malloc(sizeof(struct process));////???
	if(!head_new) 
		exit(1);
	head_new=NULL;
	while((i<PCB) &&(a=='Y'||a=='y'))
	{
		struct process *s;
		s=(struct process *)malloc(sizeof(struct process));       //???
		if(!s) exit(1);
		cout<<"请输入进程名、运行时间、优先数：\n";
		cin>>pcbs[i].pname;
		cin>>pcbs[i].BurstTime;
		cin>>pcbs[i].priority;
		cout<<"状态默认为R\n";
		pcbs[i].Status='R';
		s->next=NULL;            //？
		in_queue(head_new,s);
		i++;
		cout<<"do u want to insert process more ?? 'Y'or'N'\n";
		cin>>a;
		cout<<"------------------------------------------------\n";

	}
	quantity=i;
	return head_new;
}

 void version()  
{  
    cout<<endl<<endl;  
    cout<<"-----------------------------------------------"<<endl;  
    cout<<"-----             Kala                      ---"<<endl;  
	cout<<"-----------------------------------------------"<<endl;  
    cout<<endl<<endl;  
}  

PROCESS *in_queue(PROCESS *head,PROCESS *p) //入队函数
{
	if(head==NULL)
	{
		head=p;
		p->next=NULL;
	}
	else 
	{
		p->next=head;
		head=p;
	}
	return head;
}

int high_priority() //选择优先级最大的进程
{
	int i,high=-100;
	for (i=0;i<quantity;i++)
	{
		if (high <pcbs[i].priority&& pcbs[i].Status =='R')
			high=pcbs[i].priority ;
	}
	cout<<"high="<<high<<endl;
	return high;
}

int JudgeAllE()  //判断是否所有进程执行完毕
{
	for (int i=0;i<quantity;i++)
	{
		if (pcbs[i].Status =='R')
			return 1;
	}
	return 0;
}

//优先数调度算法  
void privilege()  
{  
	int j,high;  
    while(JudgeAllE()) 
    {  
		high=high_priority();
		for(j=0;j<quantity;j++)  
        {
            if(pcbs[j].priority == high)
			{
				if(pcbs[j].Status =='R')  
				{
					pcbs[j].priority --;
					pcbs[j].BurstTime --;
					cout<<"运行进程名："<<pcbs[j].pname <<"\n";
				} 
				if (pcbs[j].BurstTime ==0)
				{
					pcbs[j].Status ='E';
				}
			}		
		} 
		cout<< "当前进程状态：\n";		//输出进程
		readData();
		cout<<"------------------------------------------------\n";
    }  
}  

void readData() //改为指针循环 
{
    cout<<"进程名 运行时间 优先数 进程状态\n";  
    for(int i=0;i<quantity;i++)  
    {  
        cout<<"   "<<pcbs[i].pname<<"       "<<pcbs[i].BurstTime<<"       "<<pcbs[i].priority<<"     "<<pcbs[i].Status <<endl;  
    }  
}  

void main()
{
	version();
	char a;
	init();
	readData();
	privilege();
	cout<<"结束程序"<<endl;
	cin>>a;
}