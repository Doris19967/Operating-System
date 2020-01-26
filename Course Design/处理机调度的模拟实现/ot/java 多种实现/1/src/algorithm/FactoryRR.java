package algorithm;

import java.util.LinkedList;

import model.PCB;

/**
 * ClassName: FactoryRR 
 * @Description: 生产RR算法
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class FactoryRR implements Factory{

	@Override
	public Scheduler cteate() {
		LinkedList<PCB> list=new LinkedList<PCB>();
		return new RR(list);
	}
	
}
