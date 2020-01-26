#include<iostream>
using namespace std;
#define MAX_NUM 3  //�������� 
#define INF 100000 //����� 
//������̿��ƿ�Ľṹ
typedef struct pcb_struct
{
	char name[2];  //��������
	char ProcState; //����״̬
	int ArriveTime;  //���̵���ʱ��
	int StartTime;  //���̿�ʼʱ��
	int FinishTime;  //���̽���ʱ��
	int ServeTime;  //���̷���ʱ��
	int RunTime;  //�Ѿ�ռ��cpuʱ��
	int MoreTime; //���̻���Ҫ����ʱ��
	int TurnaroundTime; //������תʱ�� 
	float ResponseRatio; //��Ӧ�� 
	struct pcb_struct *next;  //�ṹ��ָ�� 
} pcb;

int time=0; //cpuʱ��
pcb* head=NULL; //����ͷָ�� 
//pcb* tail=NULL;  //����βָ��

//���̳�ʼ������������̵����ƣ�����ʱ�䣬����ʱ�䣬 
void FCFS_initial()
{
	cout<<"������"<<MAX_NUM<<"�����̵Ľ��������ﵽʱ�䡢����ʱ��" <<endl;
	
	for(int i=1;i<=MAX_NUM;i++) 
	{
		pcb* new_proc=NULL;
		if((new_proc=new pcb)==NULL)
		{
			cout<<"�����½���ʧ��"<<endl;
			return;
		}
		cout<<"��"<<i<<"������:"<<endl;
			cin>>new_proc->name;
			cin>>new_proc->ArriveTime;
			cin>>new_proc->ServeTime;
	
		new_proc->StartTime=0;  //��ʼʱ����0 
		new_proc->FinishTime=0; //����ʱ����0 
		new_proc->ProcState= 'w';  //����״̬��Ϊ�ȴ� 
		new_proc->RunTime=0;	//�Ѿ�ռ��cpuʱ����0 
		new_proc->MoreTime=0; //���̻���Ҫ����ʱ����0 
		new_proc->TurnaroundTime=0; //���̵���תʱ����Ϊ0 	
		new_proc->next=NULL;   //�½���βָ������ 
		if(head==NULL)  //�����һ������ʱ
		{	
			head=new_proc;//ͷָ��ָ���һ������ 
		//	tail=head;
		} 
		else
		{
			if(head->ArriveTime>new_proc->ArriveTime)  //�½��̵ĵ���ʱ��С�ڵ�һ�����̵Ĵﵽʱ�䣬���ڵ�һ���ڵ�֮ǰ 
			{
				new_proc->next=head;
				head=new_proc;
			}
			else
			{
				pcb *iterator_proc=head; //��������Ѱ�ҵ�ָ��
				while(iterator_proc->next!=NULL&&iterator_proc->next->ArriveTime<new_proc->ArriveTime) //���������ҵ��½��̵ķ���λ��
				{
					iterator_proc=iterator_proc->next;
				} 
			/*	if(iterator_proc->next==NULL) //���������β�ڵ� 
				{
					tail=new_proc;  //�ı�βָ�� 
				}
			*/
				new_proc->next=iterator_proc->next;
				iterator_proc->next=new_proc;  
			} 
		} 
	}
}
pcb *ArriveTime_SortList(pcb *head)  //�������еĽ��̰��յ���ʱ��������� 
{
    //�����������
    if(head == NULL || head->next == NULL)	return head;
    pcb *p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        pcb* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->ArriveTime > q->next->ArriveTime)
            {
            	//�����˽ڵ���������ʱ�䡢����ʱ�䣬�൱�ڽ����������ڵ㱾�� 
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
pcb *HRRN_SortList(pcb *head)  //�������еĽ��̰�����Ӧ�ȴӴ�С���� 
{
    //�����������
    if(head == NULL || head->next == NULL)	return head;
    //������Ӧ�� 
    pcb* iterator_proc=head; 
	for(int i=1;i<=MAX_NUM;i++)
	{
		if(iterator_proc->ArriveTime<=time&&iterator_proc->ProcState!='f')  //���̴˿��Ѿ����������һ�δ���н��� 
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
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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
	ArriveTime_SortList(head); //�������е�Ԫ�ذ��յ���ʱ�䣨��ʱ����ʣ��ʱ�䣩��С��������
	time=0; //cpuʱ����0 
	pcb* run_proc=head; //�������н��̵�ָ�� 
	pcb* new_proc=head; //�����޸�PCB��״̬��ָ�� 
	int process_count=0;
	for(int i=1;i<=MAX_NUM;i++)
	{
		new_proc->StartTime=0;  //��ʼʱ����0 
		new_proc->FinishTime=0; //����ʱ����0 
		new_proc->RunTime=0;	//�Ѿ�ռ��cpuʱ����0 
		new_proc->ProcState='w';  //����״̬��Ϊ�ȴ� 
		new_proc->MoreTime=new_proc->ServeTime; //���̻���Ҫ����ʱ���ʼֵ�����ʱ����� 
		new_proc->TurnaroundTime=0; //���̵���תʱ����Ϊ0 	
		new_proc->ResponseRatio=-1.0; //��Ӧ������Ϊ-1 
		new_proc=new_proc->next;
			
	}
    while(process_count < MAX_NUM)
	{
				cout<<time<<"ʱ�� ��"<<run_proc->name<<"��������ִ��"<<endl;	
				run_proc->StartTime=time; //�޸Ŀ�ʼ����ʱ�� 
				//˼·��ÿ����һ��ʱ��̶ȣ�����һ�μ�� 
			    run_proc->RunTime++;  
				time++;
				run_proc->MoreTime=run_proc->ServeTime-run_proc->RunTime;
			if(run_proc->MoreTime <= 0)
			{
					cout<<time<<"ʱ�̣�"<<run_proc->name<<"�������н���"<<endl;		
					run_proc->FinishTime=time;
					run_proc->TurnaroundTime=run_proc->FinishTime-run_proc->ArriveTime;//��תʱ��=�������ʱ��-���̵���ʱ�� 
					cout<<run_proc->name<<"���ʱ��:"<<run_proc->FinishTime<<"	"<<"��תʱ�䣺"<<run_proc->TurnaroundTime<<"	" 
					<<"��Ӧ�ȣ�"<< (1+(run_proc->StartTime-run_proc->ArriveTime)/run_proc->ServeTime)<<endl;				
					run_proc->ProcState = 'f' ; //״̬�޸� 
					run_proc->ResponseRatio=-2 ; //��Ӧ������Ϊ-2 
					process_count++;  //��ɽ�����+1 			
			}
			else
			{
			        cout<<time<<"ʱ�� ��"<<run_proc->name<<" ���������ж�  " <<endl;
					cout<<"�Ѿ�������"<<run_proc->RunTime<<"����Ҫִ��"<<run_proc->MoreTime<<endl;
			}		
			if(run_proc->ProcState=='f')  //��ǰ����������ɣ��������һ������ 
			{
				if(process_count < MAX_NUM)  //�ж��Ƿ��н��̴����� 
					run_proc=run_proc->next;  
				else 
					break;					
				if (run_proc->ProcState=='w' )  //��δ�����Ľ��� 
				{
					if(time<run_proc->ArriveTime)  //������̵�ǰ��û���� 
					{
						time=run_proc->ArriveTime;
					}
								
				}
				else 
				{
					for( ; run_proc->ProcState=='f' && run_proc->next!=NULL ; )
						run_proc=run_proc->next;  //������δ��������һ������ 
				}
			} 
			else //���������Ӧ�ȴӴ�С���� 
			{
				HRRN_SortList(head); 
				run_proc=head;  
				if(run_proc->ArriveTime>time&&run_proc->ProcState=='w')  //�����ǰ���̻�δ����
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
