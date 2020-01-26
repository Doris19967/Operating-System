class Process:
    class processor:
        def __init__(self, name, arrival_time, service_time, priority):
            self.name = name    # 进程名称
            self.arrival_time = arrival_time   # 到达时间
            self.service_time = service_time   # 服务时间
            self.priority = priority    # 静态优先级
            self.left_service_time = service_time  # 剩余需要服务的时间
            self.start_time = 0    # 开始执行时间
            self.finish_time = 0     # 完成时间
            self.turnover_time = 0  # 周转时间
            self.weight_time = 0      # 带权周转时间
            self.response_ratio = 0                             # 响应比
            self.used_time = 0          # 已经使用的时间，也就是（服务时间 - 剩余服务时间）
            self.ready = False         # 记录就绪状态
            self.over = False          # 记录完成状态

    class Progress:
        def __init__(self, process_list):
            self.x = len(process_list)          # 进程个数
            self.p = self.sort(process_list)           # 进程结构

        def sort(self, process_list):
            # 对进程按到达时间排序
            for i in range(0, self.x):
                for j in range(0, i):       # 按照各进程到达时间升序，对进程排序
                    if process_list[j].arrival_time > process_list[i].arrival_time:
                        temp = process_list[j]
                        process_list[j] = process_list[i]
                        process_list[i] = temp
            return process_list

        # 先来先服务  也可以称为先进先出
        def FCFS(self):
            sum_cycling_time = 0         # 记录周转总和
            sum_w_cycling_time = 0        # 记录带权周转总和
            avg_time = 0        # 平均周转时间
            avg_w_time = 0      # 平均带权周转时间
            # 初始化第一个进程的开始时间（即到达时间），和结束时间。
            self.p[0].start_time = self.p[0].arrival_time
            self.p[0].finish_time = self.p[0].service_time + \
                self.p[0].start_time
            self.p[0].turnover_time = self.p[0].finish_time - \
                self.p[0].arrival_time      # 计算周转时间
            self.p[0].weight_time = self.p[0].turnover_time / \
                self.p[0].service_time           # 计算带权周转时间
            sum_cycling_time += self.p[0].turnover_time
            sum_w_cycling_time += self.p[0].weight_time
            for i in range(1, self.x):
                # 判断到达时间与前一个进程的完成时间
                if self.p[i].arrival_time < self.p[i - 1].finish_time:
                    self.p[i].start_time = self.p[i - 1].finish_time
                else:
                    self.p[i].start_time = self.p[i].arrival_time
                # 完成时间等于开始时间+服务时间
                self.p[i].finish_time = self.p[i].service_time + \
                    self.p[i].start_time
                self.p[i].turnover_time = self.p[i].finish_time - \
                    self.p[i].arrival_time      # 计算周转时间
                self.p[i].weight_time = self.p[i].turnover_time / \
                    self.p[i].service_time           # 计算带权周转时间
                # 周转时间求和
                sum_cycling_time += self.p[i].turnover_time
                sum_w_cycling_time += self.p[i].weight_time
            avg_time = sum_cycling_time / self.x      # 平均周转时间
            avg_w_time = sum_w_cycling_time / self.x   # 平均带权周转时间
            return self.p, avg_time, avg_w_time

        # 轮转调度  以一个周期性间隔产生时钟中断，此时当前正在运行的进程被置于就绪队列，基于FCFS选择下一个就绪进程             运行。
        def RR(self, time_block):
            sum_cycling_time = 0         # 记录周转总和
            sum_w_cycling_time = 0        # 记录带权周转总和
            avg_time = 0        # 平均周转时间
            avg_w_time = 0      # 平均带权周转时间
            pre_processes = []    # running_time等于进程到达时间时会将其入队
            over_processes = []  # 完成队列
            flag = 0            # 记录完成的进程数
            running_time = 0           # 模拟运行时间
            pre_processes.append(self.p[0])  # 先将第一个进程入队

            # 初始化开始时间
            for i in range(0, self.x):
                self.p[i].start_time = self.p[i].arrival_time

            while(flag != self.x):
                # 是否进程入队的优先级高于进程从队首切换到队尾的优先级？
                # 执行当前队首进程，如果一个时间片内不能执行完，则放入队列尾部
                # 判断时间片是否大于剩余服务时间
                if time_block >= pre_processes[0].left_service_time:
                    for i in range(pre_processes[0].left_service_time):
                        pre_processes[0].left_service_time -= 1
                        running_time += 1

                        for i in range(self.x):
                            if running_time == self.p[i].arrival_time:
                                pre_processes.append(self.p[i])         # 就绪队列进入队尾

                        if pre_processes[0].left_service_time == 0:
                            # 计算完成时间
                            pre_processes[0].finish_time = running_time
                            # 计算周转时间
                            pre_processes[0].turnover_time = pre_processes[0].finish_time \
                                - pre_processes[0].arrival_time
                            # 计算带权周转时间
                            pre_processes[0].weight_time = float(pre_processes[0].turnover_time) / \
                                pre_processes[0].service_time
                    flag += 1           # 完成的进程数自增
                    over_processes.append(
                        pre_processes.pop(0))  # 进程结束从就绪队列出队进完成队列
                    continue   # 直接结束此次循环，下面内容不执行
                else:  # 剩余服务时间大于一个时间片
                    for i in range(time_block):
                        pre_processes[0].left_service_time -= 1
                        running_time += 1

                        for i in range(self.x):  # 判断此时有没有就绪队列加入队尾
                            if running_time == self.p[i].arrival_time:
                                pre_processes.append(self.p[i])
                    # 一个时间片结束进程从队头切换至队尾
                    pre_processes.append(pre_processes.pop(0))
            for i in range(0, len(over_processes)):
                # 周转时间求和
                sum_cycling_time += over_processes[i].turnover_time
                sum_w_cycling_time += over_processes[i].weight_time
            avg_time = sum_cycling_time / len(over_processes)      # 平均周转时间
            avg_w_time = sum_w_cycling_time / len(over_processes)   # 平均带权周转时间
            return over_processes, avg_time, avg_w_time

        # 最高响应比优先  R=(w+s)/s，其中R表示响应比，w表示已经等待的时间，s表示期待服务的时间
        def HRRN(self):
            sum_cycling_time = 0
            sum_w_cycling_time = 0
            pre_processes = []
            over_processes = []
            running_time = 0
            flag = 0
            pre_processes.append(self.p[0])
            while(flag != self.x):
                # 计算响应比
                for j in range(len(pre_processes)):
                    pre_processes[j].response_ratio = (running_time - pre_processes[j].arrival_time +
                                                       pre_processes[j].service_time) / pre_processes[j].service_time
                # 找到响应比最大的进程
                max_rr = 0
                for i in range(len(pre_processes)):
                    if pre_processes[i].response_ratio >= pre_processes[max_rr].response_ratio:
                        max_rr = i
                for i in range(pre_processes[max_rr].service_time):
                    running_time += 1
                    for k in range(self.x):  # 就绪队列入队
                        if (self.p[k].arrival_time == running_time):
                            pre_processes.append(self.p[k])
                # 计算属性
                pre_processes[max_rr].finish_time = running_time
                pre_processes[max_rr].turnover_time = pre_processes[max_rr].finish_time - \
                    pre_processes[max_rr].arrival_time
                pre_processes[max_rr].weight_time = pre_processes[max_rr].turnover_time / \
                    pre_processes[max_rr].service_time
                sum_cycling_time += pre_processes[max_rr].turnover_time
                sum_w_cycling_time += pre_processes[max_rr].weight_time
                over_processes.append(pre_processes.pop(max_rr))
                flag += 1
            over_processes[0].start_time = over_processes[0].arrival_time
            for i in range(1, len(over_processes)):
                over_processes[i].start_time = over_processes[i - 1].finish_time
            avg_time = sum_cycling_time / len(over_processes)      # 平均周转时间
            avg_w_time = sum_w_cycling_time / len(over_processes)   # 平均带权周转时间
            return over_processes, avg_time, avg_w_time

        # 基于静态优先级的调度
        def static_priority(self):
            sum_cycling_time = 0
            sum_w_cycling_time = 0
            # 新建输出队列
            pre_processes = []
            over_processes = []
            pre_processes.append(self.p[0])
            max_key = 0
            running_time = 0
            flag = 0
            while flag != self.x:
                max_key = 0
                max = pre_processes[0].priority
                for k in range(len(pre_processes)):
                    if pre_processes[k].priority < max:
                        max = pre_processes[k].priority
                        max_key = k
                for j in range(pre_processes[max_key].service_time):
                    pre_processes[max_key].left_service_time -= 1
                    running_time += 1
                    if pre_processes[max_key].left_service_time == 0:
                        pre_processes[max_key].finish_time = running_time
                        pre_processes[max_key].turnover_time = pre_processes[max_key].finish_time - \
                            pre_processes[max_key].arrival_time
                        pre_processes[max_key].weight_time = pre_processes[max_key].turnover_time / \
                            pre_processes[max_key].service_time
                        sum_cycling_time += pre_processes[max_key].turnover_time
                        sum_w_cycling_time += pre_processes[max_key].weight_time
                        flag += 1
                        over_processes.append(pre_processes.pop(max_key))
                    for i in range(self.x):
                        if self.p[i].arrival_time == running_time:
                            pre_processes.append(self.p[i])
            over_processes[0].start_time = over_processes[0].arrival_time
            for i in range(1, self.x):
                over_processes[i].start_time = over_processes[i - 1].finish_time

            avg_time = sum_cycling_time / self.x
            avg_w_time = sum_w_cycling_time / self.x
            return over_processes, avg_time, avg_w_time

        # 短作业优先  下一次选择所需处理时间最短的进程
        def SJF(self):
            sum_cycling_time = 0
            sum_w_cycling_time = 0

            flag = 0  # 记录已完成的进程数量
            time = 0  # 模拟时钟计数
            current_process = -1  # 记录当前正在执行的进程下标
            over_list = []

            while flag != self.x:
                if current_process != -1:  # 此时有进程在执行
                    self.p[current_process].used_time += 1
                    if self.p[current_process].used_time == self.p[current_process].service_time:
                        # 计算相关的参数
                        self.p[current_process].finish_time = time
                        self.p[current_process].turnover_time = self.p[current_process].finish_time - \
                            self.p[current_process].arrival_time
                        self.p[current_process].weight_time = self.p[current_process].turnover_time / \
                            self.p[current_process].service_time
                        sum_cycling_time += self.p[current_process].turnover_time
                        sum_w_cycling_time += self.p[current_process].weight_time
                        flag += 1
                        over_list.append(self.p[current_process])
                        self.p[current_process].over = True
                for i in range(self.x):
                    if time == self.p[i].arrival_time:
                        self.p[i].ready = True
                min_handle = 100            # 获取最小服务时间
                for i in range(self.x):
                    if self.p[i].ready == True and self.p[i].over == False:
                        if current_process == -1:
                            min_handle = self.p[0].service_time
                            current_process = 0
                        else:
                            if self.p[current_process].over == True:
                                for j in range(self.x):
                                    if self.p[j].ready == True and self.p[j].over == False:
                                        if self.p[j].service_time <= min_handle:
                                            current_process = j
                                            min_handle = self.p[j].service_time
                time += 1
            over_list[0].start_time = over_list[0].arrival_time
            for i in range(1, len(over_list)):
                over_list[i].start_time = over_list[i - 1].finish_time
            avg_time = sum_cycling_time / self.x
            avg_w_time = sum_w_cycling_time / self.x
            return over_list, avg_time, avg_w_time
