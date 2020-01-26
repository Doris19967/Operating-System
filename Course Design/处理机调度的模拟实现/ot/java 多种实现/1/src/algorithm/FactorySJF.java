package algorithm;
import java.util.LinkedList;

import model.PCB;

/**
 * 
 * ClassName: FactorySJF 
 * @Description: 生产SJF算法
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class FactorySJF implements Factory{
	@Override
	public SJF cteate() {
		// 工厂方法 生产SJF算法
		LinkedList<PCB> list=new LinkedList<PCB>();
		SJF sjf=new SJF(list);
		return sjf;
	}
}
