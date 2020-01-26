package misc;

import java.util.LinkedList;
import java.util.Random;

import model.PCB;

public class InitializationRandom {
	public static int pidmin=1000;
	
	public static LinkedList<PCB> getLinkedListrandom(int num) {
		LinkedList<PCB> list = new LinkedList<PCB>();
		for(int i = 0 ; i < num ; i++){
			Random random = new Random();
			float arrivetime = random.nextInt(20)+1;
			float needtime = random.nextInt(20)+1;
			int priority = random.nextInt(200)+1;
			PCB aPcb = new PCB();
			aPcb.setArriveTime(arrivetime);
			aPcb.setNeedTime(needtime);
			aPcb.setPriority(priority);
			aPcb.setState(3);
			int pid = pidmin;
			pidmin++;
			list.add(aPcb);
			aPcb.setPid(pid);
		}
		return list;	
	}
}

