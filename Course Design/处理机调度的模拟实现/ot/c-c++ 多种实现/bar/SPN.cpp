#include<iostream>
using namespace std;
#define MAX_NUM 5  //进程数量 
//定义进程控制块的结构
typedef struct pcb_struct
{
	char name[2];  //进程名称
	char ProcState; //进程状态
	int ArriveTime;  //进程到达时间
	int StartTime;  //进程开始时间
	int FinishTime;  //进程结束时间
	int ServeTime;  //进程服务时间
	int RunTime;  //已经占用cpu时间
	int MoreTime; //进程还需要运行时间
	int TurnaroundTime; //进程周转时间 
	struct pcb_struct *next;  //结构体指针 
} pcb;

int time=0; //cpu时间
pcb* head=NULL; //链表头指针 
//pcb* tail=NULL;  //链表尾指针

//进程初始化，输入各进程的名称，到达时间，服务时间， 
void FCFS_initial()
{
	cout<<"请输入"<<MAX_NUM<<"个进程的进程名、达到时间、服务时间" <<endl;
	for(int i=1;i<=MAX_NUM;i++) 
	{
		pcb* new_proc=NULL;
		if((new_proc=new pcb)==NULL)
		{
			cout<<"创建新进程失败"<<endl;
			return;
		}
		cout<<"第"<<i<<"个进程:"<<endl;
			cin>>new_proc->name;
			cin>>new_proc->ArriveTime;
			cin>>new_proc->ServeTime;
	
		new_proc->StartTime=0;  //开始时间置0 
		new_proc->FinishTime=0; //结束时间置0 
		new_proc->ProcState= 'w';  //进程状态置为等待 
		new_proc->RunTime=0;	//已经占用cpu时间置0 
		new_proc->MoreTime=0; //进程还需要运行时间置0 
		new_proc->TurnaroundTime=0; //进程的周转时间置为0 	
		new_proc->next=NULL;   //新进程尾指针悬空 
		if(head==NULL)  //输入第一个进程时
		{	
			head=new_proc;//头指针指向第一个进程 
		//	tail=head;
		} 
		else
		{
			if(head->ArriveTime>new_proc->ArriveTime)  //新进程的到达时间小于第一个进程的达到时间，置于第一个节点之前 
			{
				new_proc->next=head;
				head=new_proc;
			}
			else
			{
				pcb *iterator_proc=head; //用来遍历寻找的指针
				while(iterator_proc->next!=NULL&&iterator_proc->next->ArriveTime<new_proc->ArriveTime) //遍历链表，找到新进程的放置位置
				{
					iterator_proc=iterator_proc->next;
				} 
			/*	if(iterator_proc->next==NULL) //如果遍历到尾节点 
				{
					tail=new_proc;  //改变尾指针 
				}*/
				new_proc->next=iterator_proc->next;
				iterator_proc->next=new_proc;  
			} 
		} 
	}
}
pcb *ArriveTime_SortList(pcb *head)  //对链表中的进程按照到达时间进行排序 
{
    //链表快速排序
    if(head == NULL || head->next == NULL)	return head;
    pcb *p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        pcb* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->ArriveTime > q->next->ArriveTime)
            {
            	//交换了节点名、到达时间、服务时间，相当于交换了两个节点本身 
            	swap(q->name, q->next->name);
            	swap(q->ArriveTime, q->next->ArriveTime);
                swap(q->ServeTime, q->next->ServeTime);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}

pcb *SPN_SortList(pcb *head)  //对链表中的进程按照服务时间进行排序 
{
    //链表快速排序
    if(head == NULL || head->next == NULL)	return head;
    pcb *p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        pcb* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->ServeTime > q->next->ServeTime)
            {
            	//交换了节点名、到达时间、服务时间，相当于交换了两个节点本身 
            	swap(q->name, q->next->name);
            	swap(q->ArriveTime, q->next->ArriveTime);
                swap(q->ServeTime, q->next->ServeTime);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}

void SPN()
{
	cout<<"最短进程优先:"<<endl;
	SPN_SortList(head); //对链表中的元素按照服务时间从小到大排序 
	pcb* run_proc=head; //遍历运行进程的指针 
	time=run_proc->ArriveTime;
	while(run_proc)
	{ 
		//如果当前时刻短作业还没到达，cpu需要等待 
		run_proc->ArriveTime>time?
		(run_proc->StartTime=run_proc->ArriveTime,time=run_proc->ArriveTime): run_proc->StartTime=time; 
		cout<<endl;
			cout<<run_proc->StartTime<<"时刻，"<<run_proc->name<<"进程正在执行"<<endl;
			time+=run_proc->ServeTime;
			run_proc->FinishTime=time;
			run_proc->TurnaroundTime=run_proc->FinishTime-run_proc->ArriveTime;//周转时间=进程完成时间-进程到达时间 
			cout<<run_proc->name<<"完成时间:"<<run_proc->FinishTime<<"	"<<"周转时间："<<run_proc->TurnaroundTime<<"	" 
			<<"响应比："<< (1+(run_proc->StartTime-run_proc->ArriveTime)/run_proc->ServeTime)<<endl;
		cout<<endl;
		run_proc=run_proc->next;
	
	} 
	cout<<endl;
}
int main()
{
	FCFS_initial();
	SPN();
	return 0;
}
