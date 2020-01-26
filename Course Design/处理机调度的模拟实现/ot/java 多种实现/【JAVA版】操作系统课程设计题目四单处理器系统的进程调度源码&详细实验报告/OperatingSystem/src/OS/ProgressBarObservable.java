package OS;

import java.util.Observable;

public class ProgressBarObservable extends Observable {
	/**
	 * 用于实现观察者观察的对象---进度条的显示值
	 * 
	 * @author SavageGarden
	 * 
	 */
	private String price;

	public String getPrice() {
		return price;
	}

	public void setPrice(String price) {
		this.price = price;
		setChanged();
		notifyObservers(price);
	}
}