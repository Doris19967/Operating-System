package algorithm;

import java.util.LinkedList;

import model.PCB;

/**
 * ClassName: FactoryPSA 
 * @Description: 生产PSA算法
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class FactoryPSA implements Factory{

	@Override
	public Scheduler cteate() {
		LinkedList<PCB> list=new LinkedList<PCB>();
		PSA psa = new PSA(list);
		return psa;
	}
	
}
