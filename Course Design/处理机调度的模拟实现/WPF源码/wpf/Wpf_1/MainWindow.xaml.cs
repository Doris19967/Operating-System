using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Text.RegularExpressions;
using System.Drawing;
using System.Collections;
using System.IO;
namespace Wpf_1
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public int t = 50;
        public int t1 = 20;
        int t2 = 35;//line 单位长度
        string[] a = { "A", "B", "C", "D", "E" };//进程
        int[] b = { 0, 2, 4, 5, 10 };//到达时间
        int[] c = { 6, 2, 5, 4, 3 };//服务时间
        int[] d = { 2, 1, 4, 5, 3 };//优先级数，数字大的优先        
        int time1 = 3;//时间片
        public MainWindow()
        {
            InitializeComponent();    

        }
        public void fcfs_f()
        {
            FCFS_c.Children.Clear();
            addName(FCFS_c);//FCFS_c画板
            int end = b[0];//记录终止位置
            int len1 = a.Length;//作业个数
            double[] s1 = new double[len1];//j记录周转时间
            double[] s2 = new double[len1];//记录带权周转时间
            double[] s3 = new double[1];//记录平均周转时间
            double[] s4 = new double[1];//记录平均带权周转时间
            for (int i = 0; i < len1; i++)//按照进入顺依次画出
            {
                drawLine1(i+ 1,c[i] ,b[i], FCFS_c);
            }
            for (int i = 0; i < len1; i++)
            {
                drawLine(i+1, c[i], end, FCFS_c);
		        s1[i] =  end - b[i]+c[i];
                s2[i] = Convert.ToDouble(end - b[i]+c[i]) / c[i];   
                end += c[i];                
            }
            double sum = 0;
            double sum1 = 0;
            for (int i = 0; i < len1; i++)
            {
                sum += s1[i];
                sum1 += s2[i];
            }
            s3[0] = sum / len1;
            s4[0] = sum1 / len1;
            drawLabel(s1,340,FCFS_c);
            drawLabel(s2, 370, FCFS_c);
            drawLabel(s3, 400, FCFS_c);
            drawLabel(s4, 430, FCFS_c); 
        }
        public void sjf_s()//短作业优先
        {
            SJF_c.Children.Clear();
            addName(SJF_c);//画板SJF_c
            int len1 = b.Length;//作业个数
            double[] s1 = new double[len1];//j记录周转时间
            double[] s2 = new double[len1];//记录带权周转时间
            double[] s3 = new double[1];//记录平均周转时间
            double[] s4 = new double[1];//记录平均带权周转时间
            int end=b[0];
            int[] state=new int[len1];//是否进入的状态值，0未进入，1进入
            for (int i = 0; i < len1; i++)
            {
                state[i] = 0;
                drawLine1(i+ 1,c[i] ,b[i], SJF_c);
            }
            drawLine(1, c[0], end, SJF_c);
            s1[0] = end - b[0] + c[0];
            s2[0] = Convert.ToDouble(end - b[0] + c[0]) / c[0];  
            end =+ c[0];
            state[0] = 1;
            int min;//最短作业长度
            int minid;//最短作业id           
            for (int i = 1; i < len1; i++)
            {
                int[] temp = SJF_findshort(state, end);//封装的方法找出最短作业
                min=temp[0];
                minid = temp[1];
                drawLine(minid+1, min, end, SJF_c);
                s1[minid] = end - b[minid] + c[minid];
                s2[minid] = Convert.ToDouble(end - b[minid] + c[minid]) / c[minid];  
                end += min;
            }
            double sum = 0;
            double sum1 = 0;
            for (int i = 0; i < len1; i++)
            {
                sum += s1[i];
                sum1 += s2[i];
            }
            s3[0] = sum / len1;
            s4[0] = sum1 / len1;
            drawLabel(s1, 340, SJF_c);
            drawLabel(s2, 370, SJF_c);
            drawLabel(s3, 400, SJF_c);
            drawLabel(s4, 430, SJF_c);
        }
        public void rr_r()//轮转调度 时间片time1=3
        {
            RR_c.Children.Clear();
            addName(RR_c);//画板RR_c
            int end = b[0];//b是到达时间，end记录进程开始位置
            int len1 = b.Length;//作业个数
            double[] s1 = new double[len1];//j记录周转时间
            double[] s2 = new double[len1];//记录带权周转时间
            double[] s3 = new double[1];//记录平均周转时间
            double[] s4 = new double[1];//记录平均带权周转时间
            int[] state = new int[len1];//进入队列的状态 0未进入，1进入
            int[] least = new int[len1];
            for (int i = 0; i < len1; i++)
            {
                least[i] = c[i];
            }
            for (int i = 0; i < len1; i++)
            {
                state[i] = 0;
                drawLine1(i + 1, c[i], b[i], RR_c);
            }
            Queue q = new Queue();//队列
            q.Enqueue(1);//作业1入队
            state[0] = 1;
            while (q.Count > 0)//队列空则不循环
            {
                int first = Convert.ToInt32(q.Dequeue());
                int m = 0;//判断该作业是否有剩余
                if (least[first - 1] > time1)
                {
                    drawLine(first, time1, end, RR_c);
                    least[first - 1] -= time1;
                    m = 1;                    
                    end += time1;
                }
                else
                {
                    //当前作业无剩余，出队
                    drawLine(first, least[first - 1], end, RR_c);
                    s1[first - 1] = end - b[first - 1] + least[first - 1];
                    s2[first - 1] = Convert.ToDouble(end - b[first - 1] + least[first - 1]) / c[first - 1];                  
                    end += least[first - 1];
                    least[first - 1] = 0; 
                }
                for (int i = 0; i < len1; i++)
                {
                    if (b[i] <= end && state[i]==0)//有新的作业进入，入队
                    {
                        q.Enqueue(i + 1);
                        state[i] = 1;
                    }
                }
                if (m == 1)//当前作业还有剩余，入队
                {
                    q.Enqueue(first);
                }
            }
            double sum = 0;
            double sum1 = 0;
            for (int i = 0; i < len1; i++)
            {
                sum += s1[i];
                sum1 += s2[i];
            }
            s3[0] = sum / len1;
            s4[0] = sum1 / len1;
            drawLabel(s1, 340, RR_c);
            drawLabel(s2, 370, RR_c);
            drawLabel(s3, 400, RR_c);
            drawLabel(s4, 430, RR_c);
        }
        public void psa_p()//静态优先级调度
        {
            PSA_c.Children.Clear();
            addName(PSA_c);
            
            int end = b[0];
            int len1 = b.Length;//作业个数
            double[] s1 = new double[len1];//j记录周转时间
            double[] s2 = new double[len1];//记录带权周转时间
            double[] s3 = new double[1];//记录平均周转时间
            double[] s4 = new double[1];//记录平均带权周转时间
            int[] state = new int[len1];//是否进入的状态值，0未进入，1进入
            int[] least = new int[len1];//记录每个作业的剩余量
            for (int i = 0; i < len1; i++)
            {
                least[i] = c[i];
            }
            for (int i = 1; i < len1; i++)
            {
                state[i] = 0;
                drawLine1(i + 1, c[i], b[i], PSA_c);
            }
            int zz = 0;//记录作业执行完的个数            
            while (zz<len1)
            {
                int max = 0;//记录最大的优先级
                int id = 0;//记录最大的优先级作业id
                for (int i = 0; i < len1; i++)//找出优先级最大的作业
                {
                    if (state[i]==0 && d[i]>max && b[i]<=end )
                    {
                        max = d[i];
                        id = i;
                    }
                }
                drawLine(id + 1, 1, end++, PSA_c);
                least[id] -= 1;
                if (least[id]<1)
                {
                    state[id] = 1;
                    zz++;
                    s1[id] = end - b[id];
                    s2[id] = Convert.ToDouble(end - b[id]) / c[id];  
                }
            }            
            double sum = 0;
            double sum1 = 0;
            for (int i = 0; i < len1; i++)
            {
                sum += s1[i];
                sum1 += s2[i];
            }
            s3[0] = sum / len1;
            s4[0] = sum1 / len1;
            drawLabel(s1, 340, PSA_c);
            drawLabel(s2, 370, PSA_c);
            drawLabel(s3, 400, PSA_c);
            drawLabel(s4, 430, PSA_c);
        }
        public void hrrn_h()
        {
            HRRN_c.Children.Clear();
            addName(HRRN_c);
            int end = b[0];
            int len1 = b.Length;//作业个数
            double[] s1 = new double[len1];//j记录周转时间
            double[] s2 = new double[len1];//记录带权周转时间
            double[] s3 = new double[1];//记录平均周转时间
            double[] s4 = new double[1];//记录平均带权周转时间
            int[] state = new int[len1];
            drawLine(1, c[0], end, HRRN_c);
            s1[0] = end - b[0] + c[0];
            s2[0] = Convert.ToDouble(end - b[0] + c[0]) / c[0]; 
            state[0] = 1;
            end += c[0];
            for (int i = 1; i < len1; i++)
            {
                state[i] = 0;
                drawLine1(i + 1, c[i], b[i], HRRN_c);
            }
            int ii = 1;
            int[] rp = new int[len1];
            while (ii<len1)
            {
                for (int i = 1; i < len1; i++)
                {
                    if (b[i]<=end && state[i]==0)
                    {
                        rp[i] = (end - b[i] + c[i]) / c[i];//计算最高响应比的值（进程开始服务时间-到达时间+服务时间）/服务时间
                    }
                }
                int max = 0;//记录最大的最高响应比的值
                int maxid = 0;//记录最大的最高响应比的值的作业id
                for (int i = 1; i < len1; i++)
                {
                    if (rp[i]>max && state[i]==0)
                    {
                        max = rp[i];
                        maxid = i;
                    }
                }
                drawLine(maxid+1, c[maxid], end, HRRN_c);
                s1[maxid] = end - b[maxid] + c[maxid];
                s2[maxid] = Convert.ToDouble(end - b[maxid] + c[maxid]) / c[maxid]; 
                end += c[maxid];
                state[maxid] = 1;
                ii++;
            }
            double sum = 0;
            double sum1 = 0;
            for (int i = 0; i < len1; i++)
            {
                sum += s1[i];
                sum1 += s2[i];
            }
            s3[0] = sum / len1;
            s4[0] = sum1 / len1;
            drawLabel(s1, 340, HRRN_c);
            drawLabel(s2, 370, HRRN_c);
            drawLabel(s3, 400, HRRN_c);
            drawLabel(s4, 430, HRRN_c);
        }
        public void drawLine(int n,int len,int start,Canvas wp)//n第几排 len长度 star起点
        {
            Line l1 = new Line();
            int n1 = n * t+12 ;
            l1.X1 = t+start*t2; l1.X2 = t+t2*(start+len); l1.Y1 = n1; l1.Y2 =n1 ;
            l1.Fill = new SolidColorBrush(Colors.Blue);
            l1.Stroke = new SolidColorBrush(Colors.Blue);
            wp.Children.Add(l1);
            
        }
        public void drawLine1(int n, int len, int start, Canvas wp)//n第几排 len长度 star起点
        {
            Line l1 = new Line();
            int n1 = n * t + 12;
            l1.X1 = t + start * t2; l1.X2 = t + start * t2+2; l1.Y1 = n1; l1.Y2 = n1;
            l1.Fill = new SolidColorBrush(Colors.Blue);
            l1.Stroke = new SolidColorBrush(Colors.Blue);
            wp.Children.Add(l1);

        }
        public void addName(Canvas ca)
        {      
            for (int i = 1; i <= a.Length; i++)
            {
                Label lb = new Label();
                lb.Content =a[i-1];
                ca.Children.Add(lb);
                Canvas.SetLeft(lb, 10);
                Canvas.SetTop(lb, i*t);
            }
        }
        private void FCFS_Click(object sender, RoutedEventArgs e)
        {
            FCFS_w.Visibility = Visibility.Visible;
            SJF_w.Visibility = Visibility.Hidden;
            RR_w.Visibility = Visibility.Hidden;
            HRRN_w.Visibility = Visibility.Hidden;
            PSA_w.Visibility = Visibility.Hidden;            
            if (isHaveData(isread.Content.ToString()))
            {
                fcfs_f();
            }
        }

        private void SJF_Click(object sender, RoutedEventArgs e)
        {
            FCFS_w.Visibility = Visibility.Hidden;
            SJF_w.Visibility = Visibility.Visible;
            RR_w.Visibility = Visibility.Hidden;
            HRRN_w.Visibility = Visibility.Hidden;
            PSA_w.Visibility = Visibility.Hidden;
            if (isHaveData(isread.Content.ToString()))
            {
                sjf_s();
            }
        }

        private void RR_Click(object sender, RoutedEventArgs e)
        {
            FCFS_w.Visibility = Visibility.Hidden;
            SJF_w.Visibility = Visibility.Hidden;
            RR_w.Visibility = Visibility.Visible;
            HRRN_w.Visibility = Visibility.Hidden;
            PSA_w.Visibility = Visibility.Hidden;
            if (isHaveData(isread.Content.ToString()))
            {
                rr_r();
            }

        }

        private void PSA_Click(object sender, RoutedEventArgs e)
        {
            FCFS_w.Visibility = Visibility.Hidden;
            SJF_w.Visibility = Visibility.Hidden;
            RR_w.Visibility = Visibility.Hidden;
            HRRN_w.Visibility = Visibility.Hidden;
            PSA_w.Visibility = Visibility.Visible;
            if (isHaveData(isread.Content.ToString()))
            {
                psa_p();
            }
        }

        private void HRRN_Click(object sender, RoutedEventArgs e)
        {
            FCFS_w.Visibility = Visibility.Hidden;
            SJF_w.Visibility = Visibility.Hidden;
            RR_w.Visibility = Visibility.Hidden;
            HRRN_w.Visibility = Visibility.Visible;
            PSA_w.Visibility = Visibility.Hidden;
            if (isHaveData(isread.Content.ToString()))
            {
                hrrn_h();
            }
        }

        private void btn_back1_Click(object sender, RoutedEventArgs e)
        {
            FCFS_w.Visibility = Visibility.Hidden;
            SJF_w.Visibility = Visibility.Hidden;
            RR_w.Visibility = Visibility.Hidden;
            HRRN_w.Visibility = Visibility.Hidden;
            PSA_w.Visibility = Visibility.Hidden;
        }
        public int[] SJF_findshort(int[] state,int end)
        {
            int[] s1=new int[2];
            int min = 100000;
            int minid=0;
            for (int i = 1; i < c.Length; i++)
            {
                if (c[i]<=min && state[i]==0 && b[i]<=end )
                {
                    min = c[i];
                    minid = i;                    
                }                
            }
            state[minid] = 1;
            s1[0] = min;
            s1[1] = minid;
            return s1;
        }
        public void drawLabel(double[] s,int top,Canvas ca)
        {
            drawLabel_bottom(ca);
            for (int i = 0; i < s.Length; i++)
            {
                Label lb = new Label();
                lb.Content = s[i].ToString("0.00");
                ca.Children.Add(lb);
                Canvas.SetLeft(lb, 120+t*i);
                Canvas.SetTop(lb, top);
            }
        }

        private void Label_MouseLeftButtonDown_1(object sender, MouseButtonEventArgs e)
        {
            this.Close();
        }


        private void Grid_MouseLeftButtonDown_1(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.DefaultExt = ".txt";
            Nullable<bool> result=dlg.ShowDialog();
            if (result==true)
            {
                string name=dlg.FileName;
                isread.Content = name;
                StreamReader sr = new StreamReader(name,Encoding.Default);
                string[] ss = new string[10];
                int i = 0;
                string st;
                while ((st=sr.ReadLine())!=null)
                {
                    ss[i] = st;
                    i++;
                }
                a = ss[0].Split(' ');
                b = Array.ConvertAll(ss[1].Split(' '), int.Parse);
                c = Array.ConvertAll(ss[2].Split(' '), int.Parse);
                d = Array.ConvertAll(ss[3].Split(' '), int.Parse);
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            grid1.Visibility = Visibility.Visible;
            
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            grid1.Visibility = Visibility.Hidden;
            a = txt_1.Text.Split(' ');
            b = Array.ConvertAll(txt_2.Text.Split(' '), int.Parse);
            c = Array.ConvertAll(txt_3.Text.Split(' '), int.Parse);
            d = Array.ConvertAll(txt_4.Text.Split(' '), int.Parse);
            isread.Content = "已经手动输入数据";
        }
        public bool isHaveData(string ss)
        {
            if (ss=="无数据")
            {
                return false;
            }
            else
            {
                return true;
            }
                    
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            grid1.Visibility = Visibility.Hidden;
        }
        public void drawLabel_bottom(Canvas ca)
        {
               Label lb = new Label();
               lb.Content = "周转时间";
               ca.Children.Add(lb);
               Canvas.SetLeft(lb, 48);
               Canvas.SetTop(lb, 341);
               lb = new Label();
               lb.Content = "带权周转时间";
               ca.Children.Add(lb);
               Canvas.SetLeft(lb, 24);
               Canvas.SetTop(lb, 371);
               lb = new Label();
               lb.Content = "平均周转时间";
               ca.Children.Add(lb);
               Canvas.SetLeft(lb, 24);
               Canvas.SetTop(lb, 400);
               lb = new Label();
               lb.Content = "平均带权周转时间";
               ca.Children.Add(lb);
               Canvas.SetTop(lb, 427);
        }
    }
}
