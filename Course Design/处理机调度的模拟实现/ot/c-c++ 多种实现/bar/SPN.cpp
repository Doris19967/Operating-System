#include<iostream>
using namespace std;
#define MAX_NUM 5  //�������� 
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
				}*/
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

pcb *SPN_SortList(pcb *head)  //�������еĽ��̰��շ���ʱ��������� 
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
            if(q->ServeTime > q->next->ServeTime)
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

void SPN()
{
	cout<<"��̽�������:"<<endl;
	SPN_SortList(head); //�������е�Ԫ�ذ��շ���ʱ���С�������� 
	pcb* run_proc=head; //�������н��̵�ָ�� 
	time=run_proc->ArriveTime;
	while(run_proc)
	{ 
		//�����ǰʱ�̶���ҵ��û���cpu��Ҫ�ȴ� 
		run_proc->ArriveTime>time?
		(run_proc->StartTime=run_proc->ArriveTime,time=run_proc->ArriveTime): run_proc->StartTime=time; 
		cout<<endl;
			cout<<run_proc->StartTime<<"ʱ�̣�"<<run_proc->name<<"��������ִ��"<<endl;
			time+=run_proc->ServeTime;
			run_proc->FinishTime=time;
			run_proc->TurnaroundTime=run_proc->FinishTime-run_proc->ArriveTime;//��תʱ��=�������ʱ��-���̵���ʱ�� 
			cout<<run_proc->name<<"���ʱ��:"<<run_proc->FinishTime<<"	"<<"��תʱ�䣺"<<run_proc->TurnaroundTime<<"	" 
			<<"��Ӧ�ȣ�"<< (1+(run_proc->StartTime-run_proc->ArriveTime)/run_proc->ServeTime)<<endl;
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
