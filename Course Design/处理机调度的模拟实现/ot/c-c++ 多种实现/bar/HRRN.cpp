#include<iostream>
using namespace std;
#define MAX_NUM 3  //进程数量 
#define INF 100000 //无穷大 
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
	float ResponseRatio; //响应比 
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
				}
			*/
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
pcb *HRRN_SortList(pcb *head)  //对链表中的进程按照响应比从大到小排序 
{
    //链表快速排序
    if(head == NULL || head->next == NULL)	return head;
    //计算响应比 
    pcb* iterator_proc=head; 
	for(int i=1;i<=MAX_NUM;i++)
	{
		if(iterator_proc->ArriveTime<=time&&iterator_proc->ProcState!='f')  //进程此刻已经到来，并且还未运行结束 
			iterator_proc->ResponseRatio=(1.0+(time-iterator_proc->ArriveTime)/iterator_proc->ServeTime);
		else
			iterator_proc->ResponseRatio=-1;
		iterator_proc=iterator_proc->next;
	}
    pcb *p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        pcb* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->ResponseRatio < q->next->ResponseRatio)
            { 
            	swap(q->name, q->next->name);
            	swap(q->ArriveTime, q->next->ArriveTime);
                swap(q->ServeTime, q->next->ServeTime);
                swap(q->MoreTime, q->next->MoreTime);
                swap(q->ProcState, q->next->ProcState);
                swap(q->RunTime, q->next->RunTime);
                swap(q->ResponseRatio, q->next->ResponseRatio);
                isChange = true;
            }
        }
        p = q;
    }
   iterator_proc=head; 
   for(int i=1;i<=MAX_NUM;i++)
	{
		iterator_proc=iterator_proc->next;
	}
    return head;
}

void HRRN()
{
	cout<<"HRRN:"<<endl;
	ArriveTime_SortList(head); //对链表中的元素按照到达时间（此时等于剩余时间）从小到大排序
	time=0; //cpu时间置0 
	pcb* run_proc=head; //遍历运行进程的指针 
	pcb* new_proc=head; //遍历修改PCB的状态的指针 
	int process_count=0;
	for(int i=1;i<=MAX_NUM;i++)
	{
		new_proc->StartTime=0;  //开始时间置0 
		new_proc->FinishTime=0; //结束时间置0 
		new_proc->RunTime=0;	//已经占用cpu时间置0 
		new_proc->ProcState='w';  //进程状态置为等待 
		new_proc->MoreTime=new_proc->ServeTime; //进程还需要运行时间初始值与服务时间相等 
		new_proc->TurnaroundTime=0; //进程的周转时间置为0 	
		new_proc->ResponseRatio=-1.0; //响应比设置为-1 
		new_proc=new_proc->next;
			
	}
    while(process_count < MAX_NUM)
	{
				cout<<time<<"时刻 ，"<<run_proc->name<<"进程正在执行"<<endl;	
				run_proc->StartTime=time; //修改开始运行时间 
				//思路是每运行一个时间刻度，进行一次检查 
			    run_proc->RunTime++;  
				time++;
				run_proc->MoreTime=run_proc->ServeTime-run_proc->RunTime;
			if(run_proc->MoreTime <= 0)
			{
					cout<<time<<"时刻，"<<run_proc->name<<"进程运行结束"<<endl;		
					run_proc->FinishTime=time;
					run_proc->TurnaroundTime=run_proc->FinishTime-run_proc->ArriveTime;//周转时间=进程完成时间-进程到达时间 
					cout<<run_proc->name<<"完成时间:"<<run_proc->FinishTime<<"	"<<"周转时间："<<run_proc->TurnaroundTime<<"	" 
					<<"响应比："<< (1+(run_proc->StartTime-run_proc->ArriveTime)/run_proc->ServeTime)<<endl;				
					run_proc->ProcState = 'f' ; //状态修改 
					run_proc->ResponseRatio=-2 ; //响应比设置为-2 
					process_count++;  //完成进程数+1 			
			}
			else
			{
			        cout<<time<<"时刻 ，"<<run_proc->name<<" 进入运行判定  " <<endl;
					cout<<"已经运行了"<<run_proc->RunTime<<"还需要执行"<<run_proc->MoreTime<<endl;
			}		
			if(run_proc->ProcState=='f')  //当前进程运行完成，则进入下一个进程 
			{
				if(process_count < MAX_NUM)  //判断是否还有进程待运行 
					run_proc=run_proc->next;  
				else 
					break;					
				if (run_proc->ProcState=='w' )  //还未结束的进程 
				{
					if(time<run_proc->ArriveTime)  //如果进程当前还没到来 
					{
						time=run_proc->ArriveTime;
					}
								
				}
				else 
				{
					for( ; run_proc->ProcState=='f' && run_proc->next!=NULL ; )
						run_proc=run_proc->next;  //搜索还未结束的下一个进程 
				}
			} 
			else //否则根据响应比从大到小排序 
			{
				HRRN_SortList(head); 
				run_proc=head;  
				if(run_proc->ArriveTime>time&&run_proc->ProcState=='w')  //如果当前进程还未到来
				{
					time=run_proc->ArriveTime;
				}
			}				
	}
}
int main()
{
	FCFS_initial();
	HRRN();	
	return 0;
}
