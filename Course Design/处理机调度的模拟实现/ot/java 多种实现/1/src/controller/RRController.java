package controller;

import java.util.LinkedList;

import com.sun.org.apache.bcel.internal.generic.NEW;

import algorithm.FactoryRR;
import javafx.fxml.FXML;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.TableColumn;
import misc.SimpleErrorAlert;
import model.PCB;
import model.ResultModel;

/**
 * 
 * ClassName: RRController 
 * @Description: 控制RR算法页面的操作
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class RRController extends Controller{
	@FXML private TableColumn<ResultModel, Float> needColumn;
	
	@FXML private void initialize(){
		setUpTableView();
		//填充表格元素
		needColumn.setCellValueFactory(cellData->cellData.getValue().needTimeProperty().asObject());
		needColumn.setCellFactory(new CellFloat());
		scheduler = new FactoryRR().cteate();
	}
}