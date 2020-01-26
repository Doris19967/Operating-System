using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace OSTest1
{
    public partial class Form1 : Form
    {
        private List<Process> proList = new List<Process>();
        private List<String> resultList = new List<String>();
        private  double cyclingtime = 0;//总周转时间
        private double cyclingtime_weight = 0;//总带权周转时间
        public Form1()
        {
            InitializeComponent();
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            listView1.GridLines = true;
            listView1.FullRowSelect = true;
            listView1.View = View.Details;
            listView1.Columns.Add("进程");
            listView1.Columns.Add("到达时间");
            listView1.Columns.Add("运行时间");
            listView1.Columns.Add("优先级");
            listView2.GridLines = true;
            listView2.FullRowSelect = true;
            listView2.View = View.Details;
            listView2.Columns.Add("进程");
            comboBox1.SelectedIndex = 0;
            textBox4.TabIndex = 3;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String name = textBox1.Text;
            String arrivetime = textBox2.Text;
            String runtime = textBox3.Text;
            String level = textBox4.Text;
            if (name.Equals("") || arrivetime.Equals("") || runtime.Equals("") || level.Equals(""))
            {
                MessageBox.Show("输入不能为空");
            }
            else {
                Process p = new Process(name,arrivetime,runtime,level);
                listView1.Items.Add(new ListViewItem(new string[]{name,arrivetime,runtime,level}));
                proList.Add(p);
                clear();
                textBox1.Focus();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            clear();
        }
        public void clear() {
            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
            textBox4.Clear();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            String select = comboBox1.Text;
            switch (select) {
                case "先来先到服务": {
                    refresh();
                    IEnumerable<Process> query = proList.OrderBy(process => process.Math_arrivetime);
                    foreach (Process item in query) {
                        listView2.Items.Add(new ListViewItem(item.Name));
                    }
                    double currenttime = query.First<Process>().Math_arrivetime;//当前时间&等待时间 为第一个进程到达时间
                   
                    foreach (Process p in query) {
                        double Ti ;       //每个进程的周转时间                      
                        //进程执行后-------------
                        currenttime +=p.Math_runtime;
                        Ti = currenttime - p.Math_arrivetime;
                        cyclingtime += Ti ;
                        cyclingtime_weight += Ti /(p.Math_runtime+0.0);
                    }
                    label6.Text = (cyclingtime / (proList.Count+0.0)).ToString();
                    label8.Text = (cyclingtime_weight / (proList.Count + 0.0)).ToString();
                } break;
                case "最短作业优先服务": {
                    double currenttime;                   
                    refresh();
                    List<Process> minrunList = new List<Process>();
                    IEnumerable<Process> query = proList.OrderBy(process => process.Math_arrivetime); //按照到达时间排列进程             
                    IEnumerable<Process> minruntime = proList.OrderBy(process => process.Runtime);//按照最短运行时间排列进程
                    proList = query.ToList<Process>();
                    minrunList = minruntime.ToList<Process>();                   
                    currenttime =proList[0].Math_arrivetime;    //初始时间为第一个作业的到达时间 
                    double count = proList.Count;//进程总数
                    BestTimes(proList,  currenttime, minrunList);
                    foreach (String s in resultList)
                    {
                        listView2.Items.Add(new ListViewItem(new String[]{ s}));
                    }
                    label6.Text = (cyclingtime / (count + 0.0)).ToString();
                    label8.Text = (cyclingtime_weight / (count + 0.0)).ToString();
                    GetValues();
                } break;
                case "优先级法": {
                    double currenttime;
                    refresh();
                    List<Process> minlevelList = new List<Process>();
                    IEnumerable<Process> query = proList.OrderBy(process => process.Math_arrivetime); //按照到达时间排列进程             
                    IEnumerable<Process> minlevel = proList.OrderBy(process => process.Math_level);//按照优先级排列紧进程
                    proList = query.ToList<Process>();
                    minlevelList = minlevel.ToList<Process>();
                    currenttime = proList[0].Math_arrivetime;    //初始时间为第一个作业的到达时间 
                    double count = proList.Count;//进程总数
                    BestTimes(proList, currenttime, minlevelList);
                    foreach (String s in resultList)
                    {
                        listView2.Items.Add(new ListViewItem(new String[] { s }));
                    }
                    label6.Text = (cyclingtime / (count + 0.0)).ToString();
                    label8.Text = (cyclingtime_weight / (count + 0.0)).ToString();
                    GetValues();
                } break;
                case "最高响应比优先法": {
                    double currenttime;
                    refresh();
                    IEnumerable<Process> query = proList.OrderBy(process => process.Math_arrivetime); //按照到达时间排列进程   
                    proList = query.ToList<Process>();
                    currenttime = proList[0].Math_arrivetime;    //初始时间为第一个作业的到达时间 
                    double count = proList.Count;//进程总数
                    HighestResponseratio(proList, currenttime);
                    foreach (String s in resultList)
                    {
                        listView2.Items.Add(new ListViewItem(new String[] { s }));
                    }
                    label6.Text = (cyclingtime / (count + 0.0)).ToString();
                    label8.Text = (cyclingtime_weight / (count + 0.0)).ToString();
                    GetValues();
                } break;
            }
        }
        private void HighestResponseratio(List<Process> p, double currenttime ) { 
            if (p.Count == 0) {
                return;
            }
            //运行当前进程后----------------
            currenttime = currenttime+p[0].Math_runtime;
            double Ti = currenttime -p[0].Math_arrivetime;       //每个进程的周转时间 =完成时间-提交时间
            cyclingtime += Ti;
            cyclingtime_weight += Ti / (p[0].Math_runtime + 0.0);

            String name = p[0].Name;       
            resultList.Add(name);
            p.RemoveAt(0);
             List<Process> ResponseratioList = new List<Process>(); //响应比队列，将进行响应比降序排序
            for (int j = 0; j < p.Count; j++) {               
                   if (p[j].Math_arrivetime <= currenttime)//提交时间小于该时间的进行响应比计算并且加入响应比队列
                   {
                      p[j].SetResponseratior(currenttime-p[j].Math_arrivetime);//进行响应比计算
                       ResponseratioList.Add(p[j]);
                   }
            }
          if(ResponseratioList.Count>0){
                  IEnumerable<Process> query =
                      ResponseratioList.OrderByDescending(process => process.Response_ratio); //按照响应比进行降序排列
                  ResponseratioList = query.ToList();
          }
            //按响应比由高到低执行进程
           for(int i = 0;i<ResponseratioList.Count;i++){
               //完成当前进程后
               currenttime = currenttime + ResponseratioList[i].Math_runtime;
               double Ti1 = currenttime - ResponseratioList[i].Math_arrivetime;       //每个进程的周转时间 =完成时间-提交时间
               cyclingtime += Ti1;
               cyclingtime_weight += Ti1 / (ResponseratioList[i].Math_runtime + 0.0);

               p.Remove(ResponseratioList[i]);
               String name1 = ResponseratioList[i].Name;
               resultList.Add(name1);
               ResponseratioList.RemoveAt(i);
               i = i - 1;
           }
           HighestResponseratio(p, currenttime);
        }


        private void BestTimes(List<Process> p, double currenttime, List<Process> minrunList)
        {
            if (p.Count == 0) {
                return;
            }
            //运行当前进程后----------------
            currenttime = currenttime+p[0].Math_runtime;
            double Ti = currenttime -p[0].Math_arrivetime;       //每个进程的周转时间 =完成时间-提交时间
            cyclingtime += Ti;
            cyclingtime_weight += Ti / (p[0].Math_runtime + 0.0);

            String name = p[0].Name;
            minrunList.Remove(p[0]);
            resultList.Add(name);
            p.RemoveAt(0);
            for (int j = 0; j < minrunList.Count; j++) {
                double currenttime1 = currenttime;//记录上次进程完成后的时间
                if (minrunList[j].Math_arrivetime <= currenttime1)//提交时间小于该时间的可以根据最短作业优先原则进行执行
                {
                    //完成当前进程后
                    currenttime = currenttime+minrunList[j].Math_runtime;
                    double Ti1 = currenttime - minrunList[j].Math_arrivetime;       //每个进程的周转时间 =完成时间-提交时间
                    cyclingtime += Ti1;
                    cyclingtime_weight += Ti1 / (minrunList[j].Math_runtime + 0.0);

                    p.Remove(minrunList[j]);
                    String name1 = minrunList[j].Name;
                    resultList.Add(name1);
                    minrunList.RemoveAt(j);
                    j = j-1;                     
                }              
            }
            BestTimes(p, currenttime, minrunList);
        }

        private void MinLevel(List<Process> p, double currenttime, List<Process> minlevelList)
        {
            if (p.Count == 0)
            {
                return;
            }
            //取当前最先到达的进程进入内存
            //运行当前进程后----------------
            currenttime = currenttime + p[0].Math_runtime;
            double Ti = currenttime - p[0].Math_arrivetime;       //每个进程的周转时间 =完成时间-提交时间
            cyclingtime += Ti;
            cyclingtime_weight += Ti / (p[0].Math_runtime + 0.0);

            String name = p[0].Name;
            minlevelList.Remove(p[0]);
            resultList.Add(name);
            p.RemoveAt(0);
            //查看在进程运行期间是否有进程到达，是则按优先级进行运行
            for (int j = 0; j < minlevelList.Count; j++)
            {
                double currenttime1 = currenttime;//记录上次进程完成后的时间
                if (minlevelList[j].Math_arrivetime <= currenttime1)//提交时间小于该时间的可以根据优先级原则进行执行
                {
                    //完成当前进程后
                    currenttime = currenttime + minlevelList[j].Math_runtime;
                    double Ti1 = currenttime - minlevelList[j].Math_arrivetime;       //每个进程的周转时间 =完成时间-提交时间
                    cyclingtime += Ti1;
                    cyclingtime_weight += Ti1 / (minlevelList[j].Math_runtime + 0.0);

                    p.Remove(minlevelList[j]);
                    String name1 = minlevelList[j].Name;
                    resultList.Add(name1);
                    minlevelList.RemoveAt(j);
                    j = j - 1;
                }
            }
            MinLevel(p, currenttime, minlevelList);
        }
        public void refresh() {
            label6.Text = "";
            label8.Text = "";
            listView2.Clear();
            listView2.Columns.Add("进程");
            cyclingtime = 0.0;
            cyclingtime_weight = 0.0;
        }
        /// <summary>
        /// 重新获取输入的数据
        /// </summary>
        public void GetValues() {
            int count = listView1.Items.Count;
            for (int i = 0; i < count; i++) {               
                   String name = listView1.Items[i].SubItems[0].Text;
                   String arrivetime = listView1.Items[i].SubItems[1].Text;
                   String runtime = listView1.Items[i].SubItems[2].Text;
                   String level = listView1.Items[i].SubItems[3].Text;
                   Process p = new Process(name, arrivetime, runtime,level);
                   proList.Add(p);
            }
        }

        

    
       
    }
}
