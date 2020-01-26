package algorithm;

import java.util.ArrayList;
import java.util.LinkedList;

import javafx.collections.ObservableList;
import model.PCB;
import model.ResultModel;

public abstract class Scheduler {
	protected ArrayList<String> sequence;
	protected LinkedList<PCB> List;
	public void addProcess(PCB pcb){
		this.List.add(pcb);
	}
	public void deleteProcess(PCB pcb){
		for(int i1=0;i1<this.List.size();i1++)
		{
			if(pcb.getPid()==this.List.get(i1).getPid())
				this.List.remove(i1);
		}
	}
	public void clearList()
	{
		this.List.clear();
	}
	public ArrayList<ResultModel> runProcess(){
		return null;
	};
	public abstract void dynamicRun(ObservableList<ResultModel> List);
	public ArrayList<String> getList()
	{
		return this.sequence;
	}
}


