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
//定义作业信息结构
typedef struct node{
	int number;         //作业号
	int reach_time;     //作业抵达时间
	int need_time;      //作业的执行时间
	int privilege;      //作业优先权	
	float excellent;    //响应比
	int start_time;     //作业开始时间
	int wait_time;      //等待时间
	int tr_time;        //周转时间
	double wtr_time;    //带权周转时间
	int run_time;       //作业累计已执行时间
	bool visited;       //作业是否被访问过
	int finish_time; //作业完成时间
	bool reached; //作业是否抵达
}job;

//停顿几秒
void _sleep(int n){
	clock_t goal;
	goal = (clock_t)n * CLOCKS_PER_SEC + clock();
	while(goal>clock());
}
//按任意键继续
char _keygo(){
	char c;
	printf("按任意键继续.......\n");
	c = getch();
	return c;
}

//数据设置区域
const int MAX_NUM = 10;//最大作业数量
const int MAX_LINE=1024;//一行的size
int num = 0;//实际作业数量
job jobs[MAX_NUM];//作业
//就绪队列
int ready[MAX_NUM];//记录排序使用哪个数值作为排序对象
int order[MAX_NUM];

void initial_jobs() { //初始化所有作业信息
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

void read_Jobdata(){ //读取数据文件
	FILE *fp;
	fp = fopen("job.txt","r");
	if(fp == NULL){  //如果文件不存在，则退出
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
	printf("作业的数量为: %d\n",num);
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
} //调度函数


//先来先服务算法
void FCFS(){
	int i,j,temp;
	double sum1=0; //总的等待时间
	double sum2=0; //总的周转时间
	double sum3=0; //总的带权周转时间
	for(i = 1;i <= num; i++){
		order[i] = jobs[i].reach_time;
		ready[i] = i;   
	}
	//冒泡排序
	for(i = 1; i <= num; i++){//按照到达时间大小排序
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
		printf("第%d个作业",ready[i]);
		printf("到达时间 --%d,服务时间--%d\n",
		jobs[ready[i]].reach_time,
		jobs[ready[i]].need_time);
		printf("本作业正在运行...........\n");
		_sleep(1);
		printf("运行完毕\n");
		if(i==1){
			jobs[ready[i]].finish_time=jobs[ready[i]].reach_time+jobs[ready[i]].need_time;
			jobs[ready[i]].wait_time=0;
		}
		else{
			if(jobs[ready[i-1]].finish_time>jobs[ready[i]].reach_time){
			//如果上一个作业的完成时间大于下一个作业的到达时间，则下一个作业的开始时间从上一个的完成时间开始
				jobs[ready[i]].finish_time=jobs[ready[i-1]].finish_time+jobs[ready[i]].need_time;
				jobs[ready[i]].wait_time=jobs[ready[i-1]].finish_time-jobs[ready[i]].reach_time;
			} else{
				jobs[ready[i]].finish_time=jobs[ready[i]].need_time+jobs[ready[i]].reach_time;
				jobs[ready[i]].wait_time=0;         
			}       
		}
		jobs[ready[i]].tr_time=jobs[ready[i]].finish_time-jobs[ready[i]].reach_time;
		jobs[ready[i]].wtr_time=double(jobs[ready[i]].tr_time)/jobs[ready[i]].need_time;
		printf("等待时间: %d 周转时间: %d 带权周转时间: %0.2f\n",jobs[ready[i]].wait_time,jobs[ready[i]].tr_time,jobs[ready[i]].wtr_time);
		sum1+=jobs[ready[i]].wait_time;
		sum2+=jobs[ready[i]].tr_time;
		sum3+=jobs[ready[i]].wtr_time;      
	}
	printf("--------所有作业调度完毕------\n");
	printf("平均等待时间: %.2f 平均周转时间: %.2f 平均带权周转时间: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again(); 
}

int findNextSJF(job j[MAX_NUM], int length,int time ) {    // p是已经到达且拥有最短运行时间的进程的下标    // q是没有到达的进程中拥有最早到达时间的进程的下标
	int i, p, q;    int minNeedTime, minReachTime,minTime;
	p = q = -1;
	minTime = minNeedTime = minReachTime = inf;
	for( i = 1; i <= length; i++ ) {
		if(!j[i].visited){             // 第一情况
			if( j[i].reach_time<=time && j[i].need_time<=minNeedTime )
			{ 
				p = i; minNeedTime = j[i].need_time; 
			}            // 第二种情况
			else if( j[i].reach_time>time && j[i].reach_time<=minReachTime  ){
				if(j[i].need_time<minTime)
				{ 
					q = i; minReachTime = j[i].reach_time; minTime = j[i].need_time; 
				}
			}        
		}
	}
	// p为-1时,代表在lastTime时刻还没进程到达,此时选择下一个最早到达的进程q
	if( p != -1 ) return p;    
	return q;
}

//短作业优先算法
void SJF(){
	int i,j;
	double sum1=0; //总的等待时间
	double sum2=0; //总的周转时间
	double sum3=0; //总的带权周转时间
	int finish=inf; //当前完成时间
	for(i=1;i<=num;i++){
		finish=min(finish,jobs[i].reach_time);  
	}
	printf("短作业优先算法: \n");
	for(i=1;i<=num;i++){
		int index=findNextSJF(jobs,num,finish);
		printf("第%d个作业",index);
		printf("到达时间 --%d,服务时间--%d\n", jobs[index].reach_time, jobs[index].need_time);
		printf("本作业正在运行...........\n");
		_sleep(1);
		printf("运行完毕\n");
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
		printf("等待时间: %d 周转时间: %d 带权周转时间: %0.2f\n",jobs[index].wait_time,jobs[index].tr_time,jobs[index].wtr_time);    
	}
	printf("--------所有作业调度完毕------\n");
	printf("平均等待时间: %.2f 平均周转时间: %.2f 平均带权周转时间: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();
}

int findNextHRRF(int pre){
	int current=1,i,j;    //优先权=(等待时间+要求服务时间)/要求服务时间
	for(i=1;i<=num;i++)    {
		if(!jobs[i].visited){
			jobs[i].wait_time=    jobs[pre].finish_time-jobs[i].reach_time;    //等待时间=上一个进程的完成时间-到达时间
			jobs[i].excellent=(float)(jobs[i].wait_time+jobs[i].need_time)/jobs[i].need_time;
		}
	}
	for(i=1;i<=num;i++)    {
		if(!jobs[i].visited)        {
			current=i;    //找到第一个还没完成的作业
			break;        
		}
	}
	for(j=i;j<=num;j++)    //和后面的作业比较    
	{
		if(!jobs[j].visited)    //还没完成（运行）
		{
			if(jobs[current].reach_time<jobs[pre].finish_time)
			//如果进程在上一个进程完成之前到达            
			{
				if(jobs[j].excellent>jobs[current].excellent)
					current=j;    //找出到达时间在上一个进程完成之前，优先权高的进程
			}
			else    //如果进程是在上一个进程完成之后到达
			{
				if(jobs[j].reach_time<jobs[current].reach_time)
					current=j;    //找出比较早到达的一个
				else if(jobs[j].reach_time==jobs[current].reach_time&&jobs[j].excellent>jobs[current].excellent)   //如果同时到达
					current=j;    //找出服务时间比较短的一个
			}        
		}
	}
	return current;    //返回当前进程
}
//高相应比优先
void HRRF(){
int i,j;
	double sum1=0; //总的等待时间
	double sum2=0; //总的周转时间
	double sum3=0; //总的带权周转时间
	printf("高响应比优先调度算法: \n");
	int pre=1;
	jobs[1].finish_time=0;
	for(i=1;i<=num;i++){
		int index=findNextHRRF(pre);
		printf("第%d个作业",index);
		printf("到达时间 --%d,服务时间--%d\n",
		jobs[index].reach_time,
		jobs[index].need_time);
		printf("本作业正在运行...........\n");
		_sleep(1);
		printf("运行完毕\n");
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
		printf("等待时间: %d 周转时间: %d 带权周转时间: %0.2f\n",jobs[index].wait_time,jobs[index].tr_time,jobs[index].wtr_time);   
	}
	printf("--------所有作业调度完毕------\n");
	printf("平均等待时间: %.2f 平均周转时间: %.2f 平均带权周转时间: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();
}

//按照先来先服务并使用时间片轮转
vector<job> jobList;     //jobList向量
int time_unit = 10;//时间片长度
void initial_job_List(){    //给向量初始化
	for(int i=1;i<=num;i++)     {
		jobList.push_back(jobs[i]); 
	}
}

bool cmp(job a,job b)    {
	return a.reach_time<b.reach_time;
}

void RR(){
	double sum1=0; //总的等待时间
	double sum2=0; //总的周转时间
	double sum3=0; //总的带权周转时间
	initial_job_List(); queue<job>Ready;     //就绪队列
	sort(jobList.begin(),jobList.end(),cmp);
	int begin =(*jobList.begin()).reach_time;
	Ready.push(*jobList.begin());
	jobList.erase(jobList.begin());
	while(!jobList.empty()||!Ready.empty()){
		while(!jobList.empty()&&begin>=(*jobList.begin()).reach_time){    //有新作业到达，加入就绪队列
			Ready.push(*jobList.begin());
			jobList.erase(jobList.begin());
		}
		if(Ready.front().finish_time + time_unit < Ready.front().need_time){  //时间片用完没运行完,加入队尾
			printf("%d 号作业执行了 %d\n",Ready.front().number,time_unit);
			Ready.front().finish_time += time_unit;
			begin += time_unit;
			while(!jobList.empty()&&begin>=(*jobList.begin()).reach_time){  //有新作业到达，加入就绪队列
				Ready.push(*jobList.begin());
				jobList.erase(jobList.begin());             
			}
			Ready.push(Ready.front());
			Ready.pop();
			_sleep(1);
		} else{ //作业运行完
			if(Ready.front().need_time - Ready.front().finish_time<time_unit){
				time_unit-=Ready.front().need_time - Ready.front().finish_time;
			} else{
				time_unit=10;
			}
			printf("%d 号作业执行了 %d\n",Ready.front().number,time_unit);
			begin += time_unit;
			Ready.front().finish_time = begin;
			Ready.front().wait_time = Ready.front().finish_time-Ready.front().reach_time-Ready.front().need_time;
			Ready.front().tr_time = Ready.front().finish_time - Ready.front().reach_time;
			Ready.front().wtr_time = (double)Ready.front().tr_time / Ready.front().need_time;
			sum1+=Ready.front().wait_time;
			sum2+=Ready.front().tr_time;
			sum3+=Ready.front().wtr_time;
			printf("执行完的作业是 %d 号作业，等待时间是 %d ,周转时间是 %d ,带权周转时间是 %.2f\n",Ready.front().number,Ready.front().wait_time,Ready.front().tr_time,Ready.front().wtr_time);         //从就绪队列中移除作业
			Ready.pop();
			if(Ready.empty()&&!jobList.empty()){
				sort(jobList.begin(),jobList.end(),cmp);
				printf("找到当前最早的作业是: %d\n",(*jobList.begin()).number);
				begin = (*jobList.begin()).reach_time;
			}
			if(time_unit<10){               
				time_unit=10;           
			}
			_sleep(1);
		}
	}
	printf("--------所有作业调度完毕------\n");
	printf("平均等待时间: %.2f 平均周转时间: %.2f 平均带权周转时间: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();
}

int findNextHPF(job j[MAX_NUM], int length,int time ) {
//优先值越低 表示优先权越高
	// p是已经到达且拥有最高优先权的进程的下标
	// q是没有到达的进程中拥有最早到达时间的进程的下标
	int i, p, q;
	int minReachTime,minPrivilege1;
	p = q = -1; minPrivilege1  = minReachTime = inf;
	for( i = 1; i <= length; i++ ) {
		if(!j[i].visited){
			// 第一情况
			if( j[i].reach_time<=time && j[i].privilege<=minPrivilege1 )          {
				if(j[i].privilege==j[p].privilege){   //如果优先权一致 则按最早抵达时间
					if(j[i].reach_time<j[p].reach_time){
						p=i;
					}
				}
				else{
					p = i;
					minPrivilege1 = j[i].privilege;                    
				}
			}
			// 第二种情况
			else if(j[i].reach_time>time && j[i].reach_time<=minReachTime  ){
				q = i; minReachTime = j[i].reach_time;              
			}        
		}     
	}
	// p为-1时,代表在time时刻还没进程到达,此时选择下一个最早到达的进程q
	if( p != -1 )
		return p;
	return q;
}

//优先权高者优先
void HPF(){
	int i,j;
	double sum1=0; //总的等待时间
	double sum2=0; //总的周转时间
	double sum3=0; //总的带权周转时间
	int finish=inf; //当前完成时间
	for(i=1;i<=num;i++){
		finish=min(finish,jobs[i].reach_time);  
	}
	printf("优先权高者优先服务(非抢占式): \n");
	for(i=1;i<=num;i++){
		int index=findNextHPF(jobs,num,finish);
		printf("第%d个作业",index);
		printf("到达时间 --%d,服务时间--%d\n",
		jobs[index].reach_time,
		jobs[index].need_time);
		printf("本作业正在运行...........\n");
		_sleep(1);
		printf("运行完毕\n");
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
		printf("等待时间: %d 周转时间: %d 带权周转时间: %0.2f\n",jobs[index].wait_time,jobs[index].tr_time,jobs[index].wtr_time);
	}
	printf("--------所有作业调度完毕------\n");
	printf("平均等待时间: %.2f 平均周转时间: %.2f 平均带权周转时间: %.2f",sum1/num,sum2/num,sum3/num);
	initial_jobs_again();   
}

// 主函数
int main(){
	system("color 3f"); //改变颜色
	initial_jobs(); //初始化所有作业信息
	read_Jobdata(); //读取数据文件
	int choice = 1;
	while(choice != 0){
	printf("\n请选择其中一种调度算法:\n");
		printf("(1)先来先服务FCFS\n");
		printf("(2)短作业优先SJF\n");
		printf("(3)高响应比优先HRRF\n");
		printf("(4)优先权高者优先HPF\n");
		printf("(5)时间片轮转RR\n");
		printf("(0)退出\n");
		printf("请输入一个数字：");
		scanf("%d",&choice);
		switch (choice){
			case 1:FCFS();break;
			case 2:SJF();break;
			case 3:HRRF();break;
			case 4:HPF();break;
			case 5:RR();break;
			case 0:printf("退出程序\n");
			break;
		}
	}
	_keygo();
}



