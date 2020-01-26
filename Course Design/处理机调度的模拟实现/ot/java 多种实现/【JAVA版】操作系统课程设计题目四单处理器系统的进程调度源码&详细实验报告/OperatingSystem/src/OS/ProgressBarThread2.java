package OS;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import javax.swing.JTable;

public class ProgressBarThread2 extends Thread {

	ArrayList<PCB> arraylist;
	JTable statusTable;
	Queue<PCB>[] queue = new LinkedList[5];

	public ProgressBarThread2(JTable statusTable, ArrayList<PCB> arraylist) {
		this.arraylist = arraylist;
		this.statusTable = statusTable;
	}

	@Override
	public void run() {
		int size = 0;
		queue[0] = new LinkedList();
		queue[1] = new LinkedList();
		queue[2] = new LinkedList();
		queue[3] = new LinkedList();
		queue[4] = new LinkedList();
		while (size != arraylist.size()) {
			arraylist.get(size).psw = size;
			if (arraylist.get(size).pri == 4)
				queue[4].offer(arraylist.get(size));
			else if (arraylist.get(size).pri == 3)
				queue[3].offer(arraylist.get(size));
			else if (arraylist.get(size).pri == 2)
				queue[2].offer(arraylist.get(size));
			else if (arraylist.get(size).pri == 1)
				queue[1].offer(arraylist.get(size));
			else
				queue[0].offer(arraylist.get(size));

			size++;
		}
		size = 4;
		int number = size;

		while (number >= 0) {
			while (!queue[size].isEmpty()) {
				PCB pcb = queue[size].poll();
				if (pcb.time <= 0)
					continue;

				statusTable.setValueAt(--pcb.time, pcb.psw, 4);
				statusTable.setValueAt("ÔËÐÐÌ¬", pcb.psw, 1);
				if (pcb.pri != 0)
					statusTable.setValueAt(--pcb.pri, pcb.psw, 2);

				statusTable
						.setValueAt(
								(arraylist.get(pcb.psw).total - arraylist
										.get(pcb.psw).time)
										* 100
										/ arraylist.get(pcb.psw).total,
								pcb.psw, 5);

				try {
					Thread.sleep(1000);
				} catch (InterruptedException ex) {

				}
				statusTable.setValueAt("¾ÍÐ÷Ì¬", pcb.psw, 1);
				if (pcb.time == 0)
					statusTable.setValueAt("ÖÕÖ¹Ì¬", pcb.psw, 1);
				else if (pcb.pri == 0)
					queue[0].offer(pcb);
				else
					queue[size - 1].offer(pcb);

			}
			number--;
			size--;
		}
		MainFrame.start_time = false;
	}

}
