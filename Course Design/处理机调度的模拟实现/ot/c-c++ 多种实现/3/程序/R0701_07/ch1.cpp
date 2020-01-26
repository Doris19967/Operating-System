#include<iostream>  
#include<stdio.h>  
#include<string.h>  
#include <iomanip>
using namespace std;

const int PCB=10; //����10������
void readData();//��������
int quantity;

typedef struct process
{  
    char pname[20];//������  
    struct process *next;   
	int BurstTime;//����ʱ��  
	int priority; // ����Խ�����ȼ�Խ��
	char Status;
}PROCESS;

PROCESS pcbs[PCB];

PROCESS * in_queue(PROCESS *head,PROCESS *p); //����
PROCESS *init() //���̳�ʼ��
{
	cout<<"��ʼ������\n";
	int i=0;
	char a='y';
	PROCESS *head_new; //���еĶ�ͷ
	head_new=(struct process*)malloc(sizeof(struct process));////???
	if(!head_new) 
		exit(1);
	head_new=NULL;
	while((i<PCB) &&(a=='Y'||a=='y'))
	{
		struct process *s;
		s=(struct process *)malloc(sizeof(struct process));       //???
		if(!s) exit(1);
		cout<<"�����������������ʱ�䡢��������\n";
		cin>>pcbs[i].pname;
		cin>>pcbs[i].BurstTime;
		cin>>pcbs[i].priority;
		cout<<"״̬Ĭ��ΪR\n";
		pcbs[i].Status='R';
		s->next=NULL;            //��
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

PROCESS *in_queue(PROCESS *head,PROCESS *p) //��Ӻ���
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

int high_priority() //ѡ�����ȼ����Ľ���
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

int JudgeAllE()  //�ж��Ƿ����н���ִ�����
{
	for (int i=0;i<quantity;i++)
	{
		if (pcbs[i].Status =='R')
			return 1;
	}
	return 0;
}

//�����������㷨  
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
					cout<<"���н�������"<<pcbs[j].pname <<"\n";
				} 
				if (pcbs[j].BurstTime ==0)
				{
					pcbs[j].Status ='E';
				}
			}		
		} 
		cout<< "��ǰ����״̬��\n";		//�������
		readData();
		cout<<"------------------------------------------------\n";
    }  
}  

void readData() //��Ϊָ��ѭ�� 
{
    cout<<"������ ����ʱ�� ������ ����״̬\n";  
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
	cout<<"��������"<<endl;
	cin>>a;
}