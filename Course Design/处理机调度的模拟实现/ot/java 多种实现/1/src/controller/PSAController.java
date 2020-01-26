package controller;

import java.util.LinkedList;
import java.util.Optional;

import algorithm.FactoryPSA;
import javafx.beans.property.SimpleObjectProperty;
import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.util.Callback;
import misc.CreateDialog;
import misc.SimpleErrorAlert;
import model.PCB;
import model.ResultModel;
/**
 * 
 * ClassName: PSAController 
 * @Description: 控制PSA算法页面的操作
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class PSAController extends Controller{
	@FXML private TableColumn<ResultModel, Integer> priorityColumn;
	@FXML 
	private void initialize() {
		setUpTableView();
		
		priorityColumn.setCellValueFactory(cellData->cellData.getValue().priorityProperty().asObject());
		priorityColumn.setCellFactory(new Cell());
		scheduler = new FactoryPSA().cteate();
	}
	//重载输入初始化方法，使用户可以手动输入优先级
	@Override
	public void initIPress() {
		Optional<LinkedList<PCB>> optional = new CreateDialog(false).showAndWait();
		optional.ifPresent(result->{
			initList(result);
			f = true;
		});
	}
	
}
