#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<memory.h>
#include<algorithm>
#include<vector>
#include<queue>
#define getpch(type) (type*)malloc(sizeof(type))
#define inf 0x3f3f3f
using namespace std;
//������ҵ��Ϣ�ṹ
typedef struct node{
	int number;         //��ҵ��
	int reach_time;     //��ҵ�ִ�ʱ��
	int need_time;      //��ҵ��ִ��ʱ��
	int privilege;      //��ҵ����Ȩ	
	float excellent;    //��Ӧ��
	int start_time;     //��ҵ��ʼʱ��
	int wait_time;      //�ȴ�ʱ��
	int tr_time;        //��תʱ��
	double wtr_time;    //��Ȩ��תʱ��
	int run_time;       //��ҵ�ۼ���ִ��ʱ��
	bool visited;       //��ҵ�Ƿ񱻷��ʹ�
	int finish_time; //��ҵ���ʱ��
	bool reached; //��ҵ�Ƿ�ִ�
}job;

//ͣ�ټ���
void _sleep(int n){
	clock_t goal;
	goal = (clock_t)n * CLOCKS_PER_SEC + clock();
	while(goal>clock());
}
//�����������
char _keygo(){
	char c;
	printf("�����������.......\n");
	c = getch();
	return c;
}

//������������
const int MAX_NUM = 10;//�����ҵ����
const int MAX_LINE=1024;//һ�е�size
int num = 0;//ʵ����ҵ����
job jobs[MAX_NUM];//��ҵ
//��������
int ready[MAX_NUM];//��¼����ʹ���ĸ���ֵ��Ϊ�������
int order[MAX_NUM];

void initial_jobs() { //��ʼ��������ҵ��Ϣ
	for(int i=0;i<MAX_NUM;i++)   {
		jobs[i].excellent=0;
		jobs[i].need_time=0;
		jobs[i].number=0;
		jobs[i].privilege=0;
		jobs[i].reach_time=0;
		jobs[i].run_time=0;
		jobs[i].start_time=0;
		jobs[i].tr_time=0;
		jobs[i].visited=false;
		jobs[i].wait_time=0;
		jobs[i].wtr_time=0;
		jobs[i].finish_time=0;
		jobs[i].reached=false;
	}     
}

void read_Jobdata(){ //��ȡ�����ļ�
	FILE *fp;
	fp = fopen("job.txt","r");
	if(fp == NULL){  //����ļ������ڣ����˳�
		printf("fail to open the file!\n");
		exit(0);
	}
	char buffer[100];
	printf("start reading...\n");
	fgets(buffer,MAX_LINE,fp);
	num++;
	while(!feof(fp)){
		fscanf(fp,"%d%d%d%d",&jobs[num].number,&jobs[num].reach_time,&jobs[num].need_time,&jobs[num].privilege);
		num++;  
	}
	num--;
	printf("read data success!\n");
	printf("��ҵ������Ϊ: %d\n",num);
	printf("%s\n",buffer);
	for(int j=1;j<=num;j++) {
		printf("%d\t%d\t\t%d\t\t%d\n",jobs[j].number,jobs[j].reach_time,jobs[j].need_time,jobs[j].privilege);
	}
	fclose(fp);
}

void initial_jobs_again(){
	for(int i=1;i<=num;i++){
		jobs[i].finish_time=0;
		jobs[i].excellent=0;
		jobs[i].tr_time=0;
		jobs[i].wtr_time=0;
		jobs[i].wait_time=0;
		jobs[i].visited=false;  
	}
} //���Ⱥ���


//�����ȷ����㷨
void FCFS(){
	int i,j,temp;
	double sum1=0; //�ܵĵȴ�ʱ��
	double sum2=0; //�ܵ���תʱ��
	double sum3=0; //�ܵĴ�Ȩ��תʱ��
	for(i = 1;i <= num; i++){
		order[i] = jobs[i].reach_time;
		ready[i] = i;   
	}
	//ð������
	for(i = 1; i <= num; i++){//���յ���ʱ���С����
		for(j = 1; j <= num-i; j++){
			if(order[j] > order[j+1]){
				temp = order[j];
				order[j] = order[j+1];
				order[j+1] = temp;
				temp = ready[j];
				ready[j] = ready[j+1];
				ready[j+1] = temp;          
			}
       }   
	}
	for(i = 1; i <= num; i++){
		printf("��%d����ҵ",ready[i]);
		printf("����ʱ�� --%d,����ʱ��--%d\n",
		jobs[ready[i]].reach_time,
		jobs[ready[i]].need_time);
		printf("����ҵ��������...........\n");
		_sleep(1);
		printf("�������\n");
		if(i==1){
			jobs[ready[i]].finish_time=jobs[ready[i]].reach_time+jobs[ready[i]].need_time;
			jobs[ready[i]].wait_time=0;
		}
		else{
			if(jobs[ready[i-1]].finish_time>jobs[ready[i]].reach_time){
			//�����һ����ҵ�����ʱ�������һ����ҵ�ĵ���ʱ�䣬����һ����ҵ�Ŀ�ʼʱ�����һ�������ʱ�俪ʼ
				jobs[ready[i]].finish_time=jobs[ready[i-1]].finish_time+jobs[ready[i]].need_time;
				jobs[ready[i]].wait_time=jobs[ready[i-1]].finish_time-jobs[ready[i]].reach_time;
			} else{
				jobs[ready[i]].finish_time=jobs[ready[i]].need_time+jobs[ready[i]].reach_time;
				jobs[ready[i]].wait_time=0;         
			}       
		}
		jobs[ready[i]].tr_time=jobs[ready[i]].finish_time-jobs[ready[i]].reach_time;
		jobs[ready[i]].wtr_time=double(jobs[ready[i]].tr_time)/jobs[ready[i]].need_time;
		printf("�ȴ�ʱ��: %d ��תʱ��: %d ��Ȩ��תʱ��: %0.2f\n",jobs[ready[i]].wait_time,jobs[ready[i]].tr_time,jobs[ready[i]].wtr_time);
		sum1+=jobs[ready[i]].wait_time;
		sum2+=jobs[ready[i]].tr_time;
		sum3+=jobs[ready[i]].wtr_time;      
	}
	printf("--------������ҵ�������------\n");
	printf("ƽ���ȴ�ʱ��: %.2f ƽ����תʱ��: %.2f ƽ����Ȩ��תʱ��: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again(); 
}

int findNextSJF(job j[MAX_NUM], int length,int time ) {    // p���Ѿ�������ӵ���������ʱ��Ľ��̵��±�    // q��û�е���Ľ�����ӵ�����絽��ʱ��Ľ��̵��±�
	int i, p, q;    int minNeedTime, minReachTime,minTime;
	p = q = -1;
	minTime = minNeedTime = minReachTime = inf;
	for( i = 1; i <= length; i++ ) {
		if(!j[i].visited){             // ��һ���
			if( j[i].reach_time<=time && j[i].need_time<=minNeedTime )
			{ 
				p = i; minNeedTime = j[i].need_time; 
			}            // �ڶ������
			else if( j[i].reach_time>time && j[i].reach_time<=minReachTime  ){
				if(j[i].need_time<minTime)
				{ 
					q = i; minReachTime = j[i].reach_time; minTime = j[i].need_time; 
				}
			}        
		}
	}
	// pΪ-1ʱ,������lastTimeʱ�̻�û���̵���,��ʱѡ����һ�����絽��Ľ���q
	if( p != -1 ) return p;    
	return q;
}

//����ҵ�����㷨
void SJF(){
	int i,j;
	double sum1=0; //�ܵĵȴ�ʱ��
	double sum2=0; //�ܵ���תʱ��
	double sum3=0; //�ܵĴ�Ȩ��תʱ��
	int finish=inf; //��ǰ���ʱ��
	for(i=1;i<=num;i++){
		finish=min(finish,jobs[i].reach_time);  
	}
	printf("����ҵ�����㷨: \n");
	for(i=1;i<=num;i++){
		int index=findNextSJF(jobs,num,finish);
		printf("��%d����ҵ",index);
		printf("����ʱ�� --%d,����ʱ��--%d\n", jobs[index].reach_time, jobs[index].need_time);
		printf("����ҵ��������...........\n");
		_sleep(1);
		printf("�������\n");
		if(jobs[index].reach_time<=finish){
			jobs[index].wait_time=finish-jobs[index].reach_time;
			jobs[index].start_time=finish;
		}
		else{
			jobs[index].start_time=jobs[index].reach_time;
			jobs[index].wait_time=0;
		}
		jobs[index].finish_time=jobs[index].start_time+jobs[index].need_time;
		jobs[index].tr_time=jobs[index].finish_time-jobs[index].reach_time;
		jobs[index].wtr_time=(double)jobs[index].tr_time/jobs[index].need_time;
		jobs[index].visited=true;
		sum1+=jobs[index].wait_time;
		sum2+=jobs[index].tr_time;
		sum3+=jobs[index].wtr_time;
		finish=jobs[index].finish_time;
		printf("�ȴ�ʱ��: %d ��תʱ��: %d ��Ȩ��תʱ��: %0.2f\n",jobs[index].wait_time,jobs[index].tr_time,jobs[index].wtr_time);    
	}
	printf("--------������ҵ�������------\n");
	printf("ƽ���ȴ�ʱ��: %.2f ƽ����תʱ��: %.2f ƽ����Ȩ��תʱ��: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();
}

int findNextHRRF(int pre){
	int current=1,i,j;    //����Ȩ=(�ȴ�ʱ��+Ҫ�����ʱ��)/Ҫ�����ʱ��
	for(i=1;i<=num;i++)    {
		if(!jobs[i].visited){
			jobs[i].wait_time=    jobs[pre].finish_time-jobs[i].reach_time;    //�ȴ�ʱ��=��һ�����̵����ʱ��-����ʱ��
			jobs[i].excellent=(float)(jobs[i].wait_time+jobs[i].need_time)/jobs[i].need_time;
		}
	}
	for(i=1;i<=num;i++)    {
		if(!jobs[i].visited)        {
			current=i;    //�ҵ���һ����û��ɵ���ҵ
			break;        
		}
	}
	for(j=i;j<=num;j++)    //�ͺ������ҵ�Ƚ�    
	{
		if(!jobs[j].visited)    //��û��ɣ����У�
		{
			if(jobs[current].reach_time<jobs[pre].finish_time)
			//�����������һ���������֮ǰ����            
			{
				if(jobs[j].excellent>jobs[current].excellent)
					current=j;    //�ҳ�����ʱ������һ���������֮ǰ������Ȩ�ߵĽ���
			}
			else    //�������������һ���������֮�󵽴�
			{
				if(jobs[j].reach_time<jobs[current].reach_time)
					current=j;    //�ҳ��Ƚ��絽���һ��
				else if(jobs[j].reach_time==jobs[current].reach_time&&jobs[j].excellent>jobs[current].excellent)   //���ͬʱ����
					current=j;    //�ҳ�����ʱ��Ƚ϶̵�һ��
			}        
		}
	}
	return current;    //���ص�ǰ����
}
//����Ӧ������
void HRRF(){
int i,j;
	double sum1=0; //�ܵĵȴ�ʱ��
	double sum2=0; //�ܵ���תʱ��
	double sum3=0; //�ܵĴ�Ȩ��תʱ��
	printf("����Ӧ�����ȵ����㷨: \n");
	int pre=1;
	jobs[1].finish_time=0;
	for(i=1;i<=num;i++){
		int index=findNextHRRF(pre);
		printf("��%d����ҵ",index);
		printf("����ʱ�� --%d,����ʱ��--%d\n",
		jobs[index].reach_time,
		jobs[index].need_time);
		printf("����ҵ��������...........\n");
		_sleep(1);
		printf("�������\n");
		if(i==1){
			jobs[index].start_time=jobs[index].reach_time;
			jobs[index].finish_time=jobs[index].start_time+jobs[index].need_time;
			jobs[index].tr_time=jobs[index].need_time;
			jobs[index].wtr_time=1.00;
			jobs[index].wait_time=0;
		} else{
			if(jobs[index].reach_time>jobs[pre].finish_time){
				jobs[index].wait_time=0;
				jobs[index].start_time=jobs[index].reach_time;
			} else{
				jobs[index].start_time= jobs[pre].finish_time;
				jobs[index].wait_time=  jobs[pre].finish_time-jobs[index].reach_time;
			}
			jobs[index].finish_time=jobs[index].start_time+jobs[index].need_time;
			jobs[index].tr_time=jobs[index].finish_time-jobs[index].reach_time;
			jobs[index].wtr_time=(double)jobs[index].tr_time/jobs[index].need_time;     
		}
		jobs[index].visited=true;
		pre=index;
		sum1+=jobs[index].wait_time;
		sum2+=jobs[index].tr_time;
		sum3+=jobs[index].wtr_time;
		printf("�ȴ�ʱ��: %d ��תʱ��: %d ��Ȩ��תʱ��: %0.2f\n",jobs[index].wait_time,jobs[index].tr_time,jobs[index].wtr_time);   
	}
	printf("--------������ҵ�������------\n");
	printf("ƽ���ȴ�ʱ��: %.2f ƽ����תʱ��: %.2f ƽ����Ȩ��תʱ��: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();
}

//���������ȷ���ʹ��ʱ��Ƭ��ת
vector<job> jobList;     //jobList����
int time_unit = 10;//ʱ��Ƭ����
void initial_job_List(){    //��������ʼ��
	for(int i=1;i<=num;i++)     {
		jobList.push_back(jobs[i]); 
	}
}

bool cmp(job a,job b)    {
	return a.reach_time<b.reach_time;
}

void RR(){
	double sum1=0; //�ܵĵȴ�ʱ��
	double sum2=0; //�ܵ���תʱ��
	double sum3=0; //�ܵĴ�Ȩ��תʱ��
	initial_job_List(); queue<job>Ready;     //��������
	sort(jobList.begin(),jobList.end(),cmp);
	int begin =(*jobList.begin()).reach_time;
	Ready.push(*jobList.begin());
	jobList.erase(jobList.begin());
	while(!jobList.empty()||!Ready.empty()){
		while(!jobList.empty()&&begin>=(*jobList.begin()).reach_time){    //������ҵ��������������
			Ready.push(*jobList.begin());
			jobList.erase(jobList.begin());
		}
		if(Ready.front().finish_time + time_unit < Ready.front().need_time){  //ʱ��Ƭ����û������,�����β
			printf("%d ����ҵִ���� %d\n",Ready.front().number,time_unit);
			Ready.front().finish_time += time_unit;
			begin += time_unit;
			while(!jobList.empty()&&begin>=(*jobList.begin()).reach_time){  //������ҵ��������������
				Ready.push(*jobList.begin());
				jobList.erase(jobList.begin());             
			}
			Ready.push(Ready.front());
			Ready.pop();
			_sleep(1);
		} else{ //��ҵ������
			if(Ready.front().need_time - Ready.front().finish_time<time_unit){
				time_unit-=Ready.front().need_time - Ready.front().finish_time;
			} else{
				time_unit=10;
			}
			printf("%d ����ҵִ���� %d\n",Ready.front().number,time_unit);
			begin += time_unit;
			Ready.front().finish_time = begin;
			Ready.front().wait_time = Ready.front().finish_time-Ready.front().reach_time-Ready.front().need_time;
			Ready.front().tr_time = Ready.front().finish_time - Ready.front().reach_time;
			Ready.front().wtr_time = (double)Ready.front().tr_time / Ready.front().need_time;
			sum1+=Ready.front().wait_time;
			sum2+=Ready.front().tr_time;
			sum3+=Ready.front().wtr_time;
			printf("ִ�������ҵ�� %d ����ҵ���ȴ�ʱ���� %d ,��תʱ���� %d ,��Ȩ��תʱ���� %.2f\n",Ready.front().number,Ready.front().wait_time,Ready.front().tr_time,Ready.front().wtr_time);         //�Ӿ����������Ƴ���ҵ
			Ready.pop();
			if(Ready.empty()&&!jobList.empty()){
				sort(jobList.begin(),jobList.end(),cmp);
				printf("�ҵ���ǰ�������ҵ��: %d\n",(*jobList.begin()).number);
				begin = (*jobList.begin()).reach_time;
			}
			if(time_unit<10){               
				time_unit=10;           
			}
			_sleep(1);
		}
	}
	printf("--------������ҵ�������------\n");
	printf("ƽ���ȴ�ʱ��: %.2f ƽ����תʱ��: %.2f ƽ����Ȩ��תʱ��: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();
}

int findNextHPF(job j[MAX_NUM], int length,int time ) {
//����ֵԽ�� ��ʾ����ȨԽ��
	// p���Ѿ�������ӵ���������Ȩ�Ľ��̵��±�
	// q��û�е���Ľ�����ӵ�����絽��ʱ��Ľ��̵��±�
	int i, p, q;
	int minReachTime,minPrivilege1;
	p = q = -1; minPrivilege1  = minReachTime = inf;
	for( i = 1; i <= length; i++ ) {
		if(!j[i].visited){
			// ��һ���
			if( j[i].reach_time<=time && j[i].privilege<=minPrivilege1 )          {
				if(j[i].privilege==j[p].privilege){   //�������Ȩһ�� ������ִ�ʱ��
					if(j[i].reach_time<j[p].reach_time){
						p=i;
					}
				}
				else{
					p = i;
					minPrivilege1 = j[i].privilege;                    
				}
			}
			// �ڶ������
			else if(j[i].reach_time>time && j[i].reach_time<=minReachTime  ){
				q = i; minReachTime = j[i].reach_time;              
			}        
		}     
	}
	// pΪ-1ʱ,������timeʱ�̻�û���̵���,��ʱѡ����һ�����絽��Ľ���q
	if( p != -1 )
		return p;
	return q;
}

//����Ȩ��������
void HPF(){
	int i,j;
	double sum1=0; //�ܵĵȴ�ʱ��
	double sum2=0; //�ܵ���תʱ��
	double sum3=0; //�ܵĴ�Ȩ��תʱ��
	int finish=inf; //��ǰ���ʱ��
	for(i=1;i<=num;i++){
		finish=min(finish,jobs[i].reach_time);  
	}
	printf("����Ȩ�������ȷ���(����ռʽ): \n");
	for(i=1;i<=num;i++){
		int index=findNextHPF(jobs,num,finish);
		printf("��%d����ҵ",index);
		printf("����ʱ�� --%d,����ʱ��--%d\n",
		jobs[index].reach_time,
		jobs[index].need_time);
		printf("����ҵ��������...........\n");
		_sleep(1);
		printf("�������\n");
		if(jobs[index].reach_time<=finish){
			jobs[index].wait_time=finish-jobs[index].reach_time;
			jobs[index].start_time=finish;      
		}
		else{
			jobs[index].start_time=jobs[index].reach_time;
			jobs[index].wait_time=0;        
		}
		jobs[index].finish_time=jobs[index].start_time+jobs[index].need_time;
		jobs[index].tr_time=jobs[index].finish_time-jobs[index].reach_time;
		jobs[index].wtr_time=(double)jobs[index].tr_time/jobs[index].need_time;
		jobs[index].visited=true;
		sum1+=jobs[index].wait_time;
		sum2+=jobs[index].tr_time;
		sum3+=jobs[index].wtr_time;
		finish=jobs[index].finish_time;
		printf("�ȴ�ʱ��: %d ��תʱ��: %d ��Ȩ��תʱ��: %0.2f\n",jobs[index].wait_time,jobs[index].tr_time,jobs[index].wtr_time);
	}
	printf("--------������ҵ�������------\n");
	printf("ƽ���ȴ�ʱ��: %.2f ƽ����תʱ��: %.2f ƽ����Ȩ��תʱ��: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();   
}

// ������
int main(){
	system("color 3f"); //�ı���ɫ
	initial_jobs(); //��ʼ��������ҵ��Ϣ
	read_Jobdata(); //��ȡ�����ļ�
	int choice = 1;
	while(choice != 0){
	printf("\n��ѡ������һ�ֵ����㷨:\n");
		printf("(1)�����ȷ���FCFS\n");
		printf("(2)����ҵ����SJF\n");
		printf("(3)����Ӧ������HRRF\n");
		printf("(4)����Ȩ��������HPF\n");
		printf("(5)ʱ��Ƭ��תRR\n");
		printf("(0)�˳�\n");
		printf("������һ�����֣�");
		scanf("%d",&choice);
		switch (choice){
			case 1:FCFS();break;
			case 2:SJF();break;
			case 3:HRRF();break;
			case 4:HPF();break;
			case 5:RR();break;
			case 0:printf("�˳�����\n");
			break;
		}
	}
	_keygo();
}



