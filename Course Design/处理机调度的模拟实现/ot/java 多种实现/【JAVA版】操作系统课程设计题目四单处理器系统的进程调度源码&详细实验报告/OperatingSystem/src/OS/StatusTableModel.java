package OS;

import javax.swing.table.DefaultTableModel;

public class StatusTableModel extends DefaultTableModel {
	/**
	 * 状态区表格模型类
	 * 
	 * @author SavageGarden
	 * 
	 */

	public Object[] rowData = { "8","7", "7", "7", "7" ,0};

	public StatusTableModel() {
		super();
		addColumn("进程标识符");
		addColumn("进程状态");
		addColumn("进程优先数");
		addColumn("总运行时间");
		addColumn("剩余运行时间");
		addColumn("进程状态条");
	}

	/**
	 * 设置为不可编辑
	 */
	@Override
	public boolean isCellEditable(int row, int column) {
		return false;
	}

	/**
	 * 向状态区添加一个进度条
	 * 
	 */
	public void addProgressBar(Object[] object) {
		//rowData[0] = "文件" + (this.getRowCount() + 1);
		addRow(object);
	}

	@Override
	public Class getColumnClass(int columnIndex) {
		// TODO Auto-generated method stub
	//	return super.getColumnClass(columnIndex);
		return getValueAt(0, columnIndex).getClass();
	}
}