package misc;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Scanner;

import model.PCB;

/**
 * ClassName: InitializionFormFile 
 * @Description: 从文件中初始化进程队列
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class InitializationFormFile {
	private static int pid=1000;
	private static int status=3;//0就绪，1运行，2完成

	public static LinkedList<PCB> getLinkedListFormFile(){
		LinkedList<PCB> list = new LinkedList<PCB>();
		
		try {
			Scanner scanner = new Scanner(new File("src\\misc\\data.txt"));
			scanner.nextLine();
			while (scanner.hasNext()) {
				PCB pcb = new PCB();
				pcb.setStatus(status);
				pcb.setPid(pid);
				pcb.setArriveTime(scanner.nextFloat());
				pcb.setNeedTime(scanner.nextFloat());
				pcb.setPriority(scanner.nextInt());
				pid+=1;
				list.add(pcb);
			}
			scanner.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		return list;
	};
}
