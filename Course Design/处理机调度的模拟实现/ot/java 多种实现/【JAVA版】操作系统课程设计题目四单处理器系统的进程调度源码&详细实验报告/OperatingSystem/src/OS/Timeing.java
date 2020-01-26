package OS;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JLabel;

public class Timeing implements Runnable {
	JLabel label;
	int i = 0;

	public Timeing(JLabel label) {
		this.label = label;
	}

	@Override
	public void run() {

		while (MainFrame.start_time == true) {
			i++;
			label.setText(Integer.toString(i));
			try {
				Thread.sleep(1000);
			} catch (InterruptedException ex) {
				Logger.getLogger(Timeing.class.getName()).log(Level.SEVERE,
						null, ex);
			}
		}
	}

}
