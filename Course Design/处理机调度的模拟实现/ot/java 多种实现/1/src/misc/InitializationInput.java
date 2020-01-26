package misc;

import java.util.LinkedList;

import model.PCB;

/**
 * ClassName: initializationInput 
 * @Description: TODO
 * @author Mr_blue
 * @date 2017年6月29日
 */
public class InitializationInput {
	private static int pid=1000;
	private static int status=3;//0就绪，1运行，2完成
	private static LinkedList<PCB> list = new LinkedList<PCB>();
	
	public static void setInput(String arriveTime,String needTime,String priority){
		PCB pcb = new PCB();
		pcb.setStatus(status);
		pcb.setPid(pid);
		pcb.setArriveTime(Integer.valueOf(arriveTime));
		pcb.setNeedTime(Integer.valueOf(needTime));
		pcb.setPriority(Integer.valueOf(priority));
		pid+=1;
		list.add(pcb);
	}
	public static LinkedList<PCB> getLinkedListFormFile(){
		return list;
	}
}
