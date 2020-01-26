# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'os_designer.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QTableView, QHeaderView
from PyQt5.Qt import QTableWidgetItem
from Processor import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(758, 600)
        # 进程调度
        self.p = Process()
        process_list = self.create_list()
        self.test = self.p.Progress(process_list)
        # UI界面
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.fcfs_button = QtWidgets.QPushButton(self.centralwidget)
        self.fcfs_button.setGeometry(QtCore.QRect(30, 530, 91, 23))
        self.fcfs_button.setObjectName("fcfs_button")
        self.fcfs_button.clicked.connect(MainWindow.FCFS_Test)
        self.sjf_button = QtWidgets.QPushButton(self.centralwidget)
        self.sjf_button.setGeometry(QtCore.QRect(140, 530, 101, 23))
        self.sjf_button.setObjectName("sjf_button")
        self.sjf_button.clicked.connect(MainWindow.SJF_Test)
        self.rr_button = QtWidgets.QPushButton(self.centralwidget)
        self.rr_button.setGeometry(QtCore.QRect(260, 530, 101, 23))
        self.rr_button.setObjectName("rr_button")
        self.rr_button.clicked.connect(MainWindow.RR_Test)
        self.static_button = QtWidgets.QPushButton(self.centralwidget)
        self.static_button.setGeometry(QtCore.QRect(380, 530, 121, 23))
        self.static_button.setObjectName("static_button")
        self.static_button.clicked.connect(MainWindow.static_priority_Test)
        self.hrrn_button = QtWidgets.QPushButton(self.centralwidget)
        self.hrrn_button.setGeometry(QtCore.QRect(530, 530, 221, 23))
        self.hrrn_button.setObjectName("hrrn_button")
        self.hrrn_button.clicked.connect(MainWindow.HRRN_Test)
        self.title = QtWidgets.QLabel(self.centralwidget)
        self.title.setGeometry(QtCore.QRect(240, 40, 171, 41))
        self.title.setAlignment(QtCore.Qt.AlignCenter)
        self.title.setObjectName("title")
        self.result_table = QtWidgets.QTableWidget(self.centralwidget)
        self.result_table.setGeometry(QtCore.QRect(90, 140, 611, 311))
        self.result_table.setRowCount(8)
        self.result_table.setColumnCount(8)
        self.result_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.x = self.result_table.columnCount()  # 获取当前表格共有多少列
        self.y = self.result_table.rowCount()  # 获取当前表格共有多少行
        self.result_table.setObjectName("result_table")
        # 添加列
        for i in range(0, self.x):
            item = QtWidgets.QTableWidgetItem()
            self.result_table.setHorizontalHeaderItem(i, item)

        # 禁止编辑
        for i in range(0, self.y):
            for j in range(0, self.x):
                item = QtWidgets.QTableWidgetItem()
                item.setFlags(QtCore.Qt.ItemIsSelectable |
                              QtCore.Qt.ItemIsEnabled)
                self.result_table.setItem(i, j, item)
        self.avg_label = QtWidgets.QLabel(self.centralwidget)
        self.avg_label.setGeometry(QtCore.QRect(40, 480, 111, 16))
        self.avg_label.setAlignment(QtCore.Qt.AlignCenter)
        self.avg_label.setObjectName("avg_label")
        self.avg_w_label = QtWidgets.QLabel(self.centralwidget)
        self.avg_w_label.setGeometry(QtCore.QRect(280, 480, 111, 16))
        self.avg_w_label.setAlignment(QtCore.Qt.AlignCenter)
        self.avg_w_label.setObjectName("avg_w_label")
        self.time_label = QtWidgets.QLabel(self.centralwidget)
        self.time_label.setGeometry(QtCore.QRect(500, 480, 111, 16))
        self.time_label.setAlignment(QtCore.Qt.AlignCenter)
        self.time_label.setObjectName("time_label")
        self.insert_button = QtWidgets.QPushButton(self.centralwidget)
        self.insert_button.setGeometry(QtCore.QRect(100, 90, 75, 23))
        self.insert_button.setObjectName("insert_button")
        self.avg_value = QtWidgets.QLineEdit(self.centralwidget)
        self.avg_value.setGeometry(QtCore.QRect(150, 480, 113, 20))
        self.avg_value.setFocusPolicy(QtCore.Qt.NoFocus)
        self.avg_value.setObjectName("avg_value")
        self.avg_w_value = QtWidgets.QLineEdit(self.centralwidget)
        self.avg_w_value.setGeometry(QtCore.QRect(390, 480, 113, 20))
        self.avg_w_value.setFocusPolicy(QtCore.Qt.NoFocus)
        self.avg_w_value.setObjectName("avg_w_value")
        self.time_value = QtWidgets.QLineEdit(self.centralwidget)
        self.time_value.setGeometry(QtCore.QRect(580, 480, 113, 20))
        self.avg_w_value.setObjectName("time_value")
        # MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 758, 23))
        self.menubar.setObjectName("menubar")
        self.menu = QtWidgets.QMenu(self.menubar)
        self.menu.setObjectName("menu")
        self.menu_2 = QtWidgets.QMenu(self.menubar)
        self.menu_2.setObjectName("menu_2")
        # MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        # MainWindow.setStatusBar(self.statusbar)
        self.menubar.addAction(self.menu.menuAction())
        self.menubar.addAction(self.menu_2.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.fcfs_button.setText(_translate("MainWindow", "先来先服务"))
        self.sjf_button.setText(_translate("MainWindow", "短作业优先"))
        self.rr_button.setText(_translate("MainWindow", "时间片轮转"))
        self.static_button.setText(_translate("MainWindow", "静态优先级"))
        self.hrrn_button.setText(_translate("MainWindow", "最高响应比"))
        self.title.setText(_translate(
            "MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">处理机调度算法</span></p></body></html>"))
        item = self.result_table.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "进程名"))
        item = self.result_table.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "到达时间"))
        item = self.result_table.horizontalHeaderItem(2)
        item.setText(_translate("MainWindow", "服务时间"))
        item = self.result_table.horizontalHeaderItem(3)
        item.setText(_translate("MainWindow", "优先级"))
        item = self.result_table.horizontalHeaderItem(4)
        item.setText(_translate("MainWindow", "开始时间"))
        item = self.result_table.horizontalHeaderItem(5)
        item.setText(_translate("MainWindow", "结束时间"))
        item = self.result_table.horizontalHeaderItem(6)
        item.setText(_translate("MainWindow", "周转时间"))
        item = self.result_table.horizontalHeaderItem(7)
        item.setText(_translate("MainWindow", "带权周转时间"))
        __sortingEnabled = self.result_table.isSortingEnabled()
        self.result_table.setSortingEnabled(False)
        self.result_table.setSortingEnabled(__sortingEnabled)
        self.avg_label.setText(_translate("MainWindow", "平均周转时间:"))
        self.avg_w_label.setText(_translate("MainWindow", "平均带权周转时间:"))
        self.time_label.setText(_translate("MainWindow", "时间片:"))
        self.insert_button.setText(_translate("MainWindow", "添加进程"))
        self.menu.setTitle(_translate("MainWindow", "文件"))
        self.menu_2.setTitle(_translate("MainWindow", "帮助"))
        f_list = self.create_list()
        for i in range(0, len(f_list)):
            # 进程名
            name = '{}'.format(f_list[i].name)
            n_data = QTableWidgetItem(str(name))
            self.result_table.setItem(i, 0, n_data)
            # 到达时间
            arrival_time = '{}'.format('%.2f' % f_list[i].arrival_time)
            a_data = QTableWidgetItem(str(arrival_time))
            self.result_table.setItem(i, 1, a_data)
            # 服务时间
            service_time = '{}'.format('%.2f' % f_list[i].service_time)
            s_data = QTableWidgetItem(str(service_time))
            self.result_table.setItem(i, 2, s_data)
            # 优先级
            priority = '{}'.format('%.2f' % f_list[i].priority)
            p_data = QTableWidgetItem(str(priority))
            self.result_table.setItem(i, 3, p_data)

    def create_list(self):
        process_list = []
        # 测试数据1
        # A = self.p.processor('A', 0, 6, 2)
        # B = self.p.processor('B', 2, 2, 1)
        # C = self.p.processor('C', 4, 5, 4)
        # D = self.p.processor('D', 5, 4, 5)
        # E = self.p.processor('E', 10, 3, 3)
        # 测试数据2
        A = self.p.processor('A', 0, 3, 4)
        B = self.p.processor('B', 4, 6, 2)
        C = self.p.processor('C', 6, 4, 1)
        D = self.p.processor('D', 2, 5, 3)
        E = self.p.processor('E', 10, 2, 5)
        process_list.append(A)
        process_list.append(B)
        process_list.append(C)
        process_list.append(D)
        process_list.append(E)
        return process_list

    # 先来先服务测试
    def FCFS_Test(self):
        process_list = self.create_list()
        self.test = self.p.Progress(process_list)
        f_list, avg_time, avg_w_time = self.test.FCFS()
        for i in range(0, len(f_list)):
            # 进程名
            name = '{}'.format(f_list[i].name)
            n_data = QTableWidgetItem(str(name))
            self.result_table.setItem(i, 0, n_data)
            # 到达时间
            arrival_time = '{}'.format('%.2f' % f_list[i].arrival_time)
            a_data = QTableWidgetItem(str(arrival_time))
            self.result_table.setItem(i, 1, a_data)
            # 服务时间
            service_time = '{}'.format('%.2f' % f_list[i].service_time)
            s_data = QTableWidgetItem(str(service_time))
            self.result_table.setItem(i, 2, s_data)
            # 优先级
            priority = '{}'.format('%.2f' % f_list[i].priority)
            p_data = QTableWidgetItem(str(priority))
            self.result_table.setItem(i, 3, p_data)
            # 开始时间
            start_time = '{}'.format('%.2f' % f_list[i].start_time)
            start_data = QTableWidgetItem(str(start_time))
            self.result_table.setItem(i, 4, start_data)
            # 结束时间
            finish_time = '{}'.format('%.2f' % f_list[i].finish_time)
            f_data = QTableWidgetItem(str(finish_time))
            self.result_table.setItem(i, 5, f_data)
            # 周转时间
            turnover_time = '{}'.format('%.2f' % f_list[i].turnover_time)
            t_data = QTableWidgetItem(str(turnover_time))
            self.result_table.setItem(i, 6, t_data)
            # 带权周转时间
            weight_time = '{}'.format('%.2f' % f_list[i].weight_time)
            w_data = QTableWidgetItem(str(weight_time))
            self.result_table.setItem(i, 7, w_data)

        s_avg_time = "{}".format('%.2f' % avg_time)
        s_avg_w_time = "{}".format('%.2f' % avg_w_time)
        self.avg_value.setText(s_avg_time)
        self.avg_w_value.setText(s_avg_w_time)
        self.time_value.clear()

    # 轮转调度测试
    def RR_Test(self):
        process_list = self.create_list()
        self.test = self.p.Progress(process_list)
        time_block = 3
        # time_block = int(self.time_value.text())
        r_list, avg_time, avg_w_time = self.test.RR(time_block)
        for i in range(0, len(r_list)):
            # 进程名
            name = '{}'.format(r_list[i].name)
            n_data = QTableWidgetItem(str(name))
            self.result_table.setItem(i, 0, n_data)
            # 到达时间
            arrival_time = '{}'.format('%.2f' % r_list[i].arrival_time)
            a_data = QTableWidgetItem(str(arrival_time))
            self.result_table.setItem(i, 1, a_data)
            # 服务时间
            service_time = '{}'.format('%.2f' % r_list[i].service_time)
            s_data = QTableWidgetItem(str(service_time))
            self.result_table.setItem(i, 2, s_data)
            # 优先级
            priority = '{}'.format('%.2f' % r_list[i].priority)
            p_data = QTableWidgetItem(str(priority))
            self.result_table.setItem(i, 3, p_data)
            # 开始时间
            start_time = '{}'.format('%.2f' % r_list[i].start_time)
            start_data = QTableWidgetItem(str(start_time))
            self.result_table.setItem(i, 4, start_data)
            # 结束时间
            finish_time = '{}'.format('%.2f' % r_list[i].finish_time)
            f_data = QTableWidgetItem(str(finish_time))
            self.result_table.setItem(i, 5, f_data)
            # 周转时间
            turnover_time = '{}'.format('%.2f' % r_list[i].turnover_time)
            t_data = QTableWidgetItem(str(turnover_time))
            self.result_table.setItem(i, 6, t_data)
            # 带权周转时间
            weight_time = '{}'.format('%.2f' % r_list[i].weight_time)
            w_data = QTableWidgetItem(str(weight_time))
            self.result_table.setItem(i, 7, w_data)

        s_avg_time = "{}".format('%.2f' % avg_time)
        s_avg_w_time = "{}".format('%.2f' % avg_w_time)
        self.avg_value.setText(s_avg_time)
        self.avg_w_value.setText(s_avg_w_time)
        s_time = "{}".format('%.2f' % time_block)
        self.time_value.setText(s_time)

    # 基于最高响应比优先的动态优先级调度测试
    def HRRN_Test(self):
        process_list = self.create_list()
        self.test = self.p.Progress(process_list)
        queen, avg_time, avg_w_time = self.test.HRRN()
        for i in range(0, len(queen)):
            # 进程名
            name = '{}'.format(queen[i].name)
            n_data = QTableWidgetItem(str(name))
            self.result_table.setItem(i, 0, n_data)
            # 到达时间
            arrival_time = '{}'.format('%.2f' % queen[i].arrival_time)
            a_data = QTableWidgetItem(str(arrival_time))
            self.result_table.setItem(i, 1, a_data)
            # 服务时间
            service_time = '{}'.format('%.2f' % queen[i].service_time)
            s_data = QTableWidgetItem(str(service_time))
            self.result_table.setItem(i, 2, s_data)
            # 优先级
            priority = '{}'.format('%.2f' % queen[i].priority)
            p_data = QTableWidgetItem(str(priority))
            self.result_table.setItem(i, 3, p_data)
            # 开始时间
            start_time = '{}'.format('%.2f' % queen[i].start_time)
            start_data = QTableWidgetItem(str(start_time))
            self.result_table.setItem(i, 4, start_data)
            # 结束时间
            finish_time = '{}'.format('%.2f' % queen[i].finish_time)
            f_data = QTableWidgetItem(str(finish_time))
            self.result_table.setItem(i, 5, f_data)
            # 周转时间
            turnover_time = '{}'.format('%.2f' % queen[i].turnover_time)
            t_data = QTableWidgetItem(str(turnover_time))
            self.result_table.setItem(i, 6, t_data)
            # 带权周转时间
            weight_time = '{}'.format('%.2f' % queen[i].weight_time)
            w_data = QTableWidgetItem(str(weight_time))
            self.result_table.setItem(i, 7, w_data)

        s_avg_time = "{}".format('%.2f' % avg_time)
        s_avg_w_time = "{}".format('%.2f' % avg_w_time)
        self.avg_value.setText(s_avg_time)
        self.avg_w_value.setText(s_avg_w_time)
        self.time_value.clear()

    # 基于静态优先级的调度测试
    def static_priority_Test(self):
        process_list = self.create_list()
        self.test = self.p.Progress(process_list)
        static_list, avg_time, avg_w_time = self.test.static_priority()
        for i in range(0, len(static_list)):
            # 进程名
            name = '{}'.format(static_list[i].name)
            n_data = QTableWidgetItem(str(name))
            self.result_table.setItem(i, 0, n_data)
            # 到达时间
            arrival_time = '{}'.format('%.2f' % static_list[i].arrival_time)
            a_data = QTableWidgetItem(str(arrival_time))
            self.result_table.setItem(i, 1, a_data)
            # 服务时间
            service_time = '{}'.format('%.2f' % static_list[i].service_time)
            s_data = QTableWidgetItem(str(service_time))
            self.result_table.setItem(i, 2, s_data)
            # 优先级
            priority = '{}'.format('%.2f' % static_list[i].priority)
            p_data = QTableWidgetItem(str(priority))
            self.result_table.setItem(i, 3, p_data)
            # 开始时间
            start_time = '{}'.format('%.2f' % static_list[i].start_time)
            start_data = QTableWidgetItem(str(start_time))
            self.result_table.setItem(i, 4, start_data)
            # 结束时间
            finish_time = '{}'.format('%.2f' % static_list[i].finish_time)
            f_data = QTableWidgetItem(str(finish_time))
            self.result_table.setItem(i, 5, f_data)
            # 周转时间
            turnover_time = '{}'.format('%.2f' % static_list[i].turnover_time)
            t_data = QTableWidgetItem(str(turnover_time))
            self.result_table.setItem(i, 6, t_data)
            # 带权周转时间
            weight_time = '{}'.format('%.2f' % static_list[i].weight_time)
            w_data = QTableWidgetItem(str(weight_time))
            self.result_table.setItem(i, 7, w_data)

        s_avg_time = "{}".format('%.2f' % avg_time)
        s_avg_w_time = "{}".format('%.2f' % avg_w_time)
        self.avg_value.setText(s_avg_time)
        self.avg_w_value.setText(s_avg_w_time)
        self.time_value.clear()

    # SJF测试
    def SJF_Test(self):
        process_list = self.create_list()
        self.test = self.p.Progress(process_list)
        list, avg_time, avg_w_time = self.test.SJF()
        for i in range(0, len(list)):
            # 进程名
            name = '{}'.format(list[i].name)
            n_data = QTableWidgetItem(str(name))
            self.result_table.setItem(i, 0, n_data)
            # 到达时间
            arrival_time = '{}'.format('%.2f' % list[i].arrival_time)
            a_data = QTableWidgetItem(str(arrival_time))
            self.result_table.setItem(i, 1, a_data)
            # 服务时间
            service_time = '{}'.format('%.2f' % list[i].service_time)
            s_data = QTableWidgetItem(str(service_time))
            self.result_table.setItem(i, 2, s_data)
            # 优先级
            priority = '{}'.format('%.2f' % list[i].priority)
            p_data = QTableWidgetItem(str(priority))
            self.result_table.setItem(i, 3, p_data)
            # 开始时间
            start_time = '{}'.format('%.2f' % list[i].start_time)
            start_data = QTableWidgetItem(str(start_time))
            self.result_table.setItem(i, 4, start_data)
            # 结束时间
            finish_time = '{}'.format('%.2f' % list[i].finish_time)
            f_data = QTableWidgetItem(str(finish_time))
            self.result_table.setItem(i, 5, f_data)
            # 周转时间
            turnover_time = '{}'.format('%.2f' % list[i].turnover_time)
            t_data = QTableWidgetItem(str(turnover_time))
            self.result_table.setItem(i, 6, t_data)
            # 带权周转时间
            weight_time = '{}'.format('%.2f' % list[i].weight_time)
            w_data = QTableWidgetItem(str(weight_time))
            self.result_table.setItem(i, 7, w_data)

        s_avg_time = "{}".format('%.2f' % avg_time)
        s_avg_w_time = "{}".format('%.2f' % avg_w_time)
        self.avg_value.setText(s_avg_time)
        self.avg_w_value.setText(s_avg_w_time)
        self.time_value.clear()
