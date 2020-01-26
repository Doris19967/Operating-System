package OS;

import javax.swing.JProgressBar;

/**
 * 
 * @author laudukang
 */
public class PCB {

	int name; // 进程标识符
	int status; // 进程状态
	int pri; // 进程优先数
	int total;// 进程总时间
	int time; // 剩余运行时间， 以时间片为单位， 当减至 0 时该进程终止
	int next; // 下一个进程控制块的位置
	int psw;//状态字
	JProgressBar bar;//进度条
	
	public PCB(int name, int status, int pri, int total, int time,JProgressBar bar) {
		this.name = name;
		this.status = status;
		this.pri = pri;
		this.total = total;
		this.time = time;
		this.bar=bar;
	}

	public PCB(int name, int status, int pri, int total, int time) {
		this.name = name;
		this.status = status;
		this.pri = pri;
		this.total = total;
		this.time = time;
	}

}
