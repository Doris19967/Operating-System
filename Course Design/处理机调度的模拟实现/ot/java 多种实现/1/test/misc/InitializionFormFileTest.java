package misc;

import java.util.LinkedList;

import org.junit.Test;

import model.PCB;

/**
 * ClassName: InitializionFormFileTest 
 * @Description: 单元测试
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class InitializionFormFileTest {
	@Test
	public void test(){
		InitializationFormFile initializion = new InitializationFormFile();
		@SuppressWarnings("static-access")
		LinkedList<PCB> list = initializion.getLinkedListFormFile();
		for(PCB pcb : list){
			System.out.println("-------------------");
			System.out.println(pcb.getArriveTime());
			System.out.println(pcb.getNeedTime());
			System.out.println(pcb.getPriority());
		}
	}
	
}
