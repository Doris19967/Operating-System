package misc;

import java.io.IOException;
import java.util.LinkedList;
import java.util.Optional;

import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import model.PCB;
import view.ViewHelp;

/**
 * ClassName: CreateDialog 
 * @Description: 创建输入初始化对话框
 * @author Mr_blue
 * @date 2017年6月29日
 */
public class CreateDialog {
	private static int pid = 1000;
	private Dialog<LinkedList<PCB>> dialog;  
	
	public CreateDialog(boolean isDisable){
		dialog = new Dialog<LinkedList<PCB>>();

		dialog.setTitle("输入");
		dialog.setHeaderText("请输入进程的到达时间，需要时间和优先级");
		ButtonType nextButtonType = new ButtonType("下一步",ButtonData.NEXT_FORWARD);
		ButtonType finishButtonType = new ButtonType("完成",ButtonData.FINISH);
		dialog.getDialogPane().getButtonTypes().addAll(nextButtonType,finishButtonType);

		GridPane grid = new GridPane();
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(20, 150, 10, 10));

		TextField arriveTime = new TextField();
		TextField needTime = new TextField();
		TextField priority = new TextField("0");
		Label pidLabel = new Label("1000");
		priority.setDisable(isDisable); //禁止用户输入优先级
		
		grid.add(new Label("pid:"), 0, 0);
		grid.add(pidLabel, 1, 0);
		grid.add(new Label("到达时间:"), 0, 1);
		grid.add(arriveTime, 1, 1);
		grid.add(new Label("需要时间:"), 0, 2);
		grid.add(needTime, 1, 2);
		grid.add(new Label("优先级:"), 0, 3);
		grid.add(priority, 1, 3);

		//设置对话框内的布局
		dialog.getDialogPane().setContent(grid);
		
		//对话框内的点击事件
		dialog.setResultConverter(value->{
			if (value == nextButtonType) {
				if (Regular_expression.isNumeric(arriveTime.getText()) 
						&& Regular_expression.isNumeric(needTime.getText())) {
					InitializationInput.setInput(arriveTime.getText(), needTime.getText(),priority.getText());
					arriveTime.setText("");
					needTime.setText("");
					priority.setText("0");
					pidLabel.setText(String.valueOf(pid));
					pid++;
					return null; //当返回值为null时showAndWait()不会返回结果
				} else {
					SimpleErrorAlert alert = new SimpleErrorAlert("错误", "输入格式错误", "请重新输入");
					alert.show();
				} 
			} if (value == finishButtonType) {
				dialog.hide();
				dialog.close();
				return InitializationInput.getLinkedListFormFile(); //返回已经初始化的PCB队列
			}
			return null;
		});
	}
	//显示对话框并等待返回结果
	public Optional<LinkedList<PCB>> showAndWait(){
		return dialog.showAndWait();
	}
}
