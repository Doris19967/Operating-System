package algorithm;

import java.util.ArrayList;
import java.util.LinkedList;

import javafx.collections.ObservableList;
import model.PCB;
import model.ResultModel;

public class PSA extends Scheduler{
	public PSA(LinkedList<PCB> list)
	{
		//this.List =new LinkedList<PCB>();
		List = list;
		sequence=new ArrayList<String>();
	}
	
	public void sort(ObservableList<ResultModel> List) {
		for(int i=0;i<List.size();i++)
		{
			 for(int j=0;j<=i;j++)
			 {
				 if(List.get(i).getPcb().getArriveTime()<List.get(j).getPcb().getArriveTime())
				 {
					 PCB temp=new PCB();
					 //赋值给中间值
					 
					 temp.setArriveTime(List.get(i).getPcb().getArriveTime());
					 temp.setFinishTime(List.get(i).getPcb().getFinishTime());
					 temp.setPid(List.get(i).getPcb().getPid());
					 temp.setNeedTime(List.get(i).getPcb().getNeedTime());
					 
					 temp.setStatus(List.get(i).getStatus());
					 temp.setPid(List.get(i).getPid());
					 temp.setStartTime(List.get(i).getStartTime());
					 temp.setFinishTime(List.get(i).getFinishTime());
					 //----------------
					 List.set(i, List.get(j));
					 ResultModel tResultModel=new ResultModel();
					 tResultModel.setPcb(temp);
						tResultModel.setNeedTime(temp.getNeedTime());
						tResultModel.setServerTime(temp.getServiceTime());
						tResultModel.setPriority(temp.getPriority());
						tResultModel.setStatus(3);
						tResultModel.setPid(temp.getPid());
						tResultModel.setStartTime(temp.getStartTime());
						tResultModel.setFinishTime(temp.getFinishTime());
					 //---------------
					 List.set(j, tResultModel);
				 }
			 }
		}
		
	}
	public void dynamicRun(ObservableList<ResultModel> List)
	{
		sort(List);
		out(List);
		System.out.println("+++++++++++++开始运行+++++++++");
		float nowtime=0;
		int value=0;
		int end=0;
		/*PCB t=new PCB();
		float endtime=0;
		int value=0;
		 
		nowtime++;
		 t.setArriveTime(this.List.get(0).getArriveTime());
		 t.setFinishTime(this.List.get(0).getFinishTime());
		 t.setPid(this.List.get(0).getPid());
		 t.setNeedTime(this.List.get(0).getNeedTime()-1);
		 t.setPriority(this.List.get(0).getPriority()+3);
		 t.setStatus(1);//完成的任务设置为2，就绪的为0，运行的为1
		 t.setStartTime(this.List.get(0).getArriveTime());
		this.List.set(0, t);*/
		for(;end<List.size();)
		{
			ResultModel tResultModel=new ResultModel();
			PCB tPcb=new PCB();
			setready(nowtime,List);
			out(List);
			value=findHigh(nowtime,List);
			
			if(value==-1)//没有任务到达的情况，cpu空闲
			{
				sequence.add("-1");	
				nowtime++;
				System.out.println("cpu空闲||||||||||||||||||||||||||||||||||||||||||");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				 //t1.setStatus(2);
				 //this.List.set(i, t1);
			}
			else if(value>=0)
			{
				
				if(List.get(value).getStartTime()==0&&List.get(value).getStartTime()!=List.get(value).getPcb().getArriveTime())//如果是第一次运行设置其运行时间
				{
					System.out.println("第"+List.get(value).getPid()+"个开始----------");
					tPcb.setStartTime(nowtime);
				}
				else {
					tPcb.setStartTime(List.get(value).getStartTime());
					tResultModel.setStartTime(List.get(value).getStartTime());
				}
					
				
				
				
				tPcb.setArriveTime(List.get(value).getPcb().getArriveTime());
				tPcb.setPid(List.get(value).getPid());
				tPcb.setNeedTime(List.get(value).getPcb().getNeedTime()-1);
				tPcb.setServiceTime(List.get(value).getPcb().getServiceTime()+1);
				
				tPcb.setPriority(List.get(value).getPcb().getPriority()+3);
				tPcb.setStatus(1);
				
				tResultModel.setPid(tPcb.getPid());
				tResultModel.setStartTime(tPcb.getStartTime());
				tResultModel.setNeedTime(tPcb.getNeedTime());
				tResultModel.setServerTime(tPcb.getServiceTime());
				tResultModel.setArriveTime(tPcb.getArriveTime());
				tResultModel.setPriority(tPcb.getPriority());
				tResultModel.setStatus(1);
				if(tPcb.getNeedTime()==0)//如果任务结束设置其结束时间和设置状态为结束
				{
					tPcb.setFinishTime(nowtime+1);
					tResultModel.setFinishTime(nowtime+1);
					tPcb.setStatus(2);
					tResultModel.setStatus(2);
					tResultModel.setTurnaroundTime(tPcb.getFinishTime()-tPcb.getArriveTime());
					tResultModel.setRturnaroundTime((tPcb.getFinishTime()-tPcb.getArriveTime())/tPcb.getServiceTime());
					//System.out.println("第"+value+"个结束");
					end++;
				}
				tResultModel.setPcb(tPcb);
				List.set(value,tResultModel);
				sequence.add(String.valueOf(List.get(value).getPid()));	
				System.out.println(value);
				 System.out.println("名字"+List.get(value).getPid()+" "+value);
			     System.out.println("优先级"+List.get(value).getPcb().getPriority());
			     System.out.println("到达时间"+List.get(value).getPcb().getArriveTime());
			     System.out.println("开始时间"+List.get(value).getStartTime());
			     System.out.println("需要时间"+List.get(value).getPcb().getNeedTime());
			     System.out.println("服务时间"+List.get(value).getPcb().getServiceTime());
			     System.out.println("完成时间"+List.get(value).getFinishTime());
			     System.out.println("状态"+List.get(value).getPcb().getStatus());
			     System.out.println("-----");
			     try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				aging(List);
				
				 //t1.setStatus(2);
				 //this.List.set(value, t1);
				nowtime++;
				//out();
			}
			
		}
		
		
	}
	public int findHigh(float nowtime,ObservableList<ResultModel> List)
	{
		int value=-1;
		float high=10000;
		/*if(this.List.get(i).getArriveTime()>nowtime)
		{
			return -1;
		}*/
		//ResultModel tResultModel=new ResultModel();
		for(int i1=0;i1<List.size();i1++)
		{
			//PCB tPcb=new PCB();
			if(List.get(i1).getPcb().getArriveTime()<=nowtime&&List.get(i1).getPcb().getNeedTime()>0)
			{
				/*t1.setStartTime(this.List.get(value).getStartTime());
				t1.setArriveTime(this.List.get(value).getArriveTime());
				t1.setPid(this.List.get(value).getPid());
				t1.setNeedTime(this.List.get(value).getNeedTime());
				t1.setPriority(this.List.get(value).getPriority());
				t1.setStatus(0);
				this.List.set(i1, t1);*/
				if(high>List.get(i1).getPcb().getPriority())
				{
					high=List.get(i1).getPcb().getPriority();
					value=i1;
				}
				
			}
			//float min=this.List.get(i).getServiceTime();
		}
		
		return value;
	}
	public void setready(float nowtime,ObservableList<ResultModel> List)
	{
		System.out.println("===========有队列到达=============");
		for(int i1=0;i1<List.size();i1++)
		{
			PCB tPcb=new PCB();
			ResultModel tResultModel=new ResultModel();
			if(List.get(i1).getPcb().getArriveTime()<=nowtime&&(List.get(i1).getPcb().getStatus()==3||List.get(i1).getPcb().getStatus()==1))
			{
				tPcb.setStartTime(List.get(i1).getPcb().getStartTime());
				tPcb.setArriveTime(List.get(i1).getPcb().getArriveTime());
				tPcb.setPid(List.get(i1).getPcb().getPid());
				tPcb.setServiceTime(List.get(i1).getPcb().getServiceTime());
				tPcb.setNeedTime(List.get(i1).getPcb().getNeedTime());
				tPcb.setPriority(List.get(i1).getPcb().getPriority());
				tPcb.setFinishTime(List.get(i1).getPcb().getFinishTime());
				
				tPcb.setStatus(0);
				tResultModel.setPcb(tPcb);
				tResultModel.setNeedTime(tPcb.getNeedTime());
				tResultModel.setServerTime(tPcb.getServiceTime());
				tResultModel.setPriority(tPcb.getPriority());
				tResultModel.setStatus(0);
				tResultModel.setPid(List.get(i1).getPcb().getPid());
				tResultModel.setStartTime(tPcb.getStartTime());
				tResultModel.setArriveTime(tPcb.getArriveTime());
				tResultModel.setFinishTime(List.get(i1).getPcb().getFinishTime());
				List.set(i1, tResultModel);
				
				System.out.println("名字"+List.get(i1).getPid()+" "+i1);
				System.out.println("状态"+List.get(i1).getPcb().getStatus());
			    System.out.println("优先级"+List.get(i1).getPcb().getPriority());
			}
			
			//float min=this.List.get(i).getServiceTime();
		}
		System.out.println("==============================");
	}
	public void aging(ObservableList<ResultModel> List)
	{
		for(int i1=0;i1<List.size();i1++)
		{
			PCB tPcb=new PCB();
			ResultModel tResultModel=new ResultModel();
			if(List.get(i1).getPcb().getStatus()==0)
			{
				tPcb.setStartTime(List.get(i1).getStartTime());
				tPcb.setArriveTime(List.get(i1).getPcb().getArriveTime());
				tPcb.setPid(List.get(i1).getPcb().getPid());
				tPcb.setNeedTime(List.get(i1).getPcb().getNeedTime());
				tPcb.setServiceTime(List.get(i1).getPcb().getServiceTime());
				if(List.get(i1).getPcb().getPriority()-3<=0)
				{
					tPcb.setPriority(0);
				}
				else {
					tPcb.setPriority(List.get(i1).getPcb().getPriority()-3);
				}
				
				tPcb.setFinishTime(List.get(i1).getPcb().getFinishTime());
				tPcb.setStatus(0);
				tResultModel.setPcb(tPcb);
				tResultModel.setPid(tPcb.getPid());
				tResultModel.setNeedTime(tPcb.getNeedTime());
				tResultModel.setServerTime(tPcb.getServiceTime());
				tResultModel.setPriority(tPcb.getPriority());
				tResultModel.setStatus(0);
				tResultModel.setStartTime(tPcb.getStartTime());
				tResultModel.setArriveTime(tPcb.getArriveTime());
				tResultModel.setFinishTime(tPcb.getFinishTime());
				List.set(i1, tResultModel);
				System.out.println("老化结果（（（（））））））");
				 System.out.println("名字"+List.get(i1).getPid()+" "+i1);
			     System.out.println("优先级"+List.get(i1).getPcb().getPriority());
			     System.out.println("到达时间"+List.get(i1).getPcb().getArriveTime());
			     System.out.println("开始时间"+List.get(i1).getStartTime());
			     System.out.println("状态"+List.get(i1).getPcb().getStatus());
			     System.out.println("需要时间"+List.get(i1).getPcb().getNeedTime());
			     System.out.println("服务时间"+List.get(i1).getPcb().getServiceTime());
			     System.out.println("完成时间"+List.get(i1).getFinishTime());
			
				
			}
			//float min=this.List.get(i).getServiceTime();
		}
	}
	public void out(ObservableList<ResultModel> List)
	{
		System.out.println("<<<<<<<<<<<<<<<所有进程情况>>>>>>>>>>>>>>>>>>>>");
		for(int i1=0;i1<List.size();i1++)
		{
		     System.out.println("名字"+List.get(i1).getPid()+" "+i1);
		     System.out.println("优先级"+List.get(i1).getPriority());
		     System.out.println("到达时间"+List.get(i1).getPcb().getArriveTime());
		     System.out.println("开始时间"+List.get(i1).getStartTime());
		     System.out.println("状态"+List.get(i1).getStatus());
		     System.out.println("需要时间"+List.get(i1).getNeedTime());
		     System.out.println("服务时间"+List.get(i1).getPcb().getServiceTime());
		     System.out.println("完成时间"+List.get(i1).getFinishTime());
		}
		System.out.println("<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>");
	}
	public void out1()
	{
		System.out.println("<<<<<<<<<<<<<<<所有进程情况>>>>>>>>>>>>>>>>>>>>");
		for(int i1=0;i1<this.List.size();i1++)
		{
		     System.out.println("名字"+this.List.get(i1).getPid()+" "+i1);
		     System.out.println("优先级"+this.List.get(i1).getPriority());
		     System.out.println("到达时间"+this.List.get(i1).getArriveTime());
		     System.out.println("开始时间"+this.List.get(i1).getStartTime());
		     System.out.println("状态"+this.List.get(i1).getStatus());
		     System.out.println("需要时间"+this.List.get(i1).getNeedTime());
		     System.out.println("服务时间"+this.List.get(i1).getServiceTime());
		     System.out.println("完成时间"+this.List.get(i1).getFinishTime());
		}
		System.out.println("<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>");
	}

	@Override
	public ArrayList<ResultModel> runProcess() {
		// TODO Auto-generated method stub
		return null;
	}
}
