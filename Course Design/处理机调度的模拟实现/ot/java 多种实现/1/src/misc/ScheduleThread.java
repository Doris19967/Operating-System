package misc;

import java.util.Optional;

import javafx.concurrent.Service;
import javafx.concurrent.Task;
import javafx.scene.control.ButtonType;
import javafx.util.Callback;

/**
 * ClassName: ScheduleThread 
 * @Description: TODO
 * @author Mr_blue
 * @date 2017年7月5日
 */
public class ScheduleThread {
	private Service<Void> thread;
	private Callback<Void, Void> callback;
	
	public ScheduleThread(Task<Void> task){
		thread = new Service<Void>() {
			@Override
			protected Task<Void> createTask() {
				return task;
			}
		};
		thread.setOnSucceeded(value->{
			SimpleSuccessAlert alert = new SimpleSuccessAlert("完成", "调度完成","是否查看调度过程");
			Optional<ButtonType> optional = alert.showAndWait();
			optional.ifPresent(result->{
				if (result==ButtonType.OK) {
					callback.call(null);
				}
			});
		});
	}
	public void run(Callback<Void, Void> callback){
		this.callback = callback;
		thread.start();
	}
}
