import sys
from os_designer import Ui_MainWindow  # 这里的first是.ui文件生成的.py文件名
from PyQt5 import QtWidgets

# 这个类继承界面UI类


class mywindow(QtWidgets.QWidget, Ui_MainWindow):
    def __init__(self):
        super(mywindow, self).__init__()
        self.setupUi(self)


# 调用show
if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    myshow = mywindow()
    myshow.show()
    sys.exit(app.exec_())
