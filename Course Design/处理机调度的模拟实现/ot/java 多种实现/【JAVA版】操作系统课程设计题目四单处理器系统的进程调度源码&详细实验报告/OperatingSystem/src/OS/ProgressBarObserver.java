package OS;

import java.util.Observable;
import java.util.Observer;

public class ProgressBarObserver implements Observer {
	/**
	 * 用于实现观察者 ---进度条的显示值变化时更新statusTableModel
	 * 
	 * @author SavageGarden
	 * 
	 */
	@Override
	public void update(Observable o, Object arg) {
		String showValue = (String) arg;
		MainFrame.statusTableModel.setValueAt(Integer.parseInt(showValue.split(":")[1]),
				Integer.parseInt(showValue.split(":")[0]), 5);
	}
}