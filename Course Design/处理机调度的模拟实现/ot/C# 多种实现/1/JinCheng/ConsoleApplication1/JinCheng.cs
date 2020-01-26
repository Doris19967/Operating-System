using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Configuration;
using System.Collections;

namespace ConsoleApplication1
{
    class CourseInput
    {
        public string id;     //标识符
        public int prc;       //优先数
        public int cputime;   //时间片
        public int alltime;   //总时间
        public int next;      //指针
        public string state;  //当前状态
        public int InputTime; //进程输入时间
    
    }
    class JinCheng
    {

        
        public CourseInput Course1 = new CourseInput();  //创建进程1
        public CourseInput Course2 = new CourseInput();  //创建进程2
        public CourseInput Course3 = new CourseInput();  //创建进程3
        public CourseInput Course4 = new CourseInput();  //创建进程4
        public CourseInput Course5 = new CourseInput();  //创建进程5
        public ArrayList IdStaticTeam = new ArrayList(); //创建进程id数组
        public ArrayList NoReadyTeam = new ArrayList(); //创建未就绪进程id数组
        public ArrayList ReadyTeam = new ArrayList();    //创建未就绪就绪队列
        public static int i = 0;    //虚拟时钟
        public static int k = 0;
        public string Choose = "";                       //存储你选择了何种算法

        //添加测试数据函数
        public void DataPrepareFunction()
        {
            Course1.id = "a"; Course1.prc = 4; Course1.cputime = 6; Course1.alltime = 10; Course1.InputTime = 0;
            Course2.id = "b"; Course2.prc = 6; Course2.cputime = 4; Course2.alltime = 20; Course2.InputTime = 5;
            Course3.id = "c"; Course3.prc = 5; Course3.cputime = 5; Course3.alltime = 15; Course3.InputTime = 4;
            Course4.id = "d"; Course4.prc = 8; Course4.cputime = 8; Course4.alltime = 24; Course4.InputTime = 2;
            Course5.id = "e"; Course5.prc = 3; Course5.cputime = 7; Course5.alltime = 30; Course5.InputTime = 20;
            //初始化next和state
            if (i == 0)
            {
                Course1.next = 0;
                Course2.next = 0;
                Course3.next = 0;
                Course4.next = 0;
                Course5.next = 0;
            }
            NoReadyTeam.Add(Course1.id);
            NoReadyTeam.Add(Course2.id);
            NoReadyTeam.Add(Course3.id);
            NoReadyTeam.Add(Course4.id);
            NoReadyTeam.Add(Course5.id);

        }
        //显示进程的原始状态
        public void CourseNowState()
        {
            if (i == 0)
            {
                Console.WriteLine("标识符  " + "优先数  " + "时间片 " + "总时间  " + "进程进入时间  ");

                for (int j = 0; j < IdStaticTeam.Count; j++)
                {
                    Console.WriteLine("   " + Course(j, IdStaticTeam).id + "       " + Course(j, IdStaticTeam).prc + "      " + Course(j, IdStaticTeam).cputime + "      " + Course(j, IdStaticTeam).alltime + "          " + Course(j, IdStaticTeam).InputTime); ;
                }
                //Console.WriteLine("按任意键继续");
                //Console.Read();
            }
            else
            {
                Console.WriteLine("标识符  " + "优先数  " + "时间片 " + "总时间  " + "进程进入时间  " + "进程当前状态  " + "以运行的时间");

                for (int j = 0; j < IdStaticTeam.Count; j++)
                {
                    Console.WriteLine("   " + Course(j, IdStaticTeam).id + "       " + Course(j, IdStaticTeam).prc + "      " + Course(j, IdStaticTeam).cputime + "      " + Course(j, IdStaticTeam).alltime + "          " + Course(j, IdStaticTeam).InputTime + "          " + Course(j, IdStaticTeam).state + "           " + Course(j, IdStaticTeam).next); ;
                }
                //Console.WriteLine("按任意键继续");
                //Console.Read();

            }
        }
        
        //初始化IdStaticTeam和NoReadyTeam数组
        public void UpdateArray()
        {
            IdStaticTeam.Add(Course1.id);
            IdStaticTeam.Add(Course2.id);
            IdStaticTeam.Add(Course3.id);
            IdStaticTeam.Add(Course4.id);
            IdStaticTeam.Add(Course5.id);
        }

       //根据数组中的id值获取Course（进程）的名称
        public CourseInput Course(int j,ArrayList MiddleArray)
        {
            
            if (MiddleArray.Count>=1)
            {
                switch (MiddleArray[j].ToString())
                {
                    case "a":
                        return Course1;
                    case "b":
                        return Course2;
                    case "c":
                        return Course3;
                    case "d":
                        return Course4;
                    case "e":
                        return Course5;
                    default:
                        return null;

                }
            }
            else
            {
                return null;
            }
        }
        
        //判断进程是否就绪
        public void ConfirmReady()
        {
            
            for (int a = 0; a < NoReadyTeam.Count; a++)
            {
                if (Course(a,NoReadyTeam).InputTime<= i)
                {
                    Course(a, NoReadyTeam).state = "就绪";
                    ReadyTeam.Add(Course(a, NoReadyTeam).id.ToString());
                    NoReadyTeam.Remove(Course(a, NoReadyTeam).id.ToString());
                }
                else
                {
                    Course(a, NoReadyTeam).state = "未就绪";
                }

            }
            if (i == 0)
            {
                Console.WriteLine("请选择进程调度算法");
                Console.WriteLine("输入【N】表示选择不具有抢断性的优先数算法");
                //Console.WriteLine("输入【Y】表示选择具有抢断性的优先数算法");
                Console.WriteLine("输入【S】表示选择时间片轮转法");
                Choose = Console.ReadLine();
                if (Choose == "N")
                {
                    Console.WriteLine("你选择了不具有抢断性的优先数调度算法");
                    RangeByYXS();
                }
                else if (Choose == "S") 
                {
                    Console.WriteLine("你选择了时间片调度算法");
                    RangBySJP();
                }
                //else if (Choose == "Y")
                //{
                //    Console.WriteLine("你选择了具有抢断性的优先数算法");
                //    YRangByYXS();
                //}

            }

        }

        //为进程执行判断就绪函数
        public void ReadsTeam()
        {
            ConfirmReady();
            Console.WriteLine("*******************************************************************************");
            Console.Read();
        }

        //时间片轮转顺序调整
        public void PanDuanSJP()
        {
            if(ReadyTeam.Count>=1)
            {
                string a = ReadyTeam[0].ToString();
                for (int j = 0; j < ReadyTeam.Count-1; j++)
                {
                    ReadyTeam[j] = ReadyTeam[j + 1].ToString();
                }
                ReadyTeam[ReadyTeam.Count - 1] = a;
            }
        }

        //时间片轮转法
        public void RangBySJP()
        {

            if ((Course(0, IdStaticTeam).next == Course(0, IdStaticTeam).alltime) && (Course(1, IdStaticTeam).next == Course(1, IdStaticTeam).alltime) && (Course(2, IdStaticTeam).next == Course(2, IdStaticTeam).alltime) && (Course(3, IdStaticTeam).next == Course(3, IdStaticTeam).alltime) && (Course(4, IdStaticTeam).next == Course(4, IdStaticTeam).alltime))
            {
                Console.WriteLine("所有进程都已经完成");
            }
            
            else
            {
                if (ReadyTeam.Count >= 1)
                {
                     for(int j=0;j<Convert.ToInt32(Course(0,ReadyTeam).cputime);j++)
                    {
                        Course(0, ReadyTeam).next++;
                        if (Course(0, ReadyTeam).next >= Course(0, ReadyTeam).alltime)
                        {
                            Course(0, ReadyTeam).state = "任务完成";
                            ReadyTeam.Remove(Course(0, ReadyTeam).id.ToString());
                            ReadsTeam();
                            CourseNowState();
                            RangBySJP();
                        }
                        else
                        {
                            Console.WriteLine("程序执行第" + i + "S");
                            Course(0, ReadyTeam).state = "正在运行";
                            i++;
                            ReadsTeam();
                            CourseNowState();
                            Console.Read();
                        }
                    }
                    PanDuanSJP();
                    RangBySJP();
                }
            }
        }
       
        //将进程id按优先数由高到底排列
        public void PanDuanYXJ()
        {          
            for (int a = 0; a < ReadyTeam.Count; a++)
            {
                for (int b = 0;b<ReadyTeam.Count-1-a;b++)
                {
                    if (Convert.ToInt32(Course(b, ReadyTeam).prc) < Convert.ToInt32(Course(b + 1, ReadyTeam).prc))
                    {
                        string c =  ReadyTeam[b+1].ToString();
                        ReadyTeam[b] = ReadyTeam[b].ToString();
                        ReadyTeam[b+1] = c;

                    }
                }
            }
            for (int j = 0; j < ReadyTeam.Count; j++)
            {
                Console.WriteLine(ReadyTeam[j].ToString());
            }
            if (Choose == "N")
            { 
              RangeByYXS();
            }

        }
        
        //不具有抢断性的优先数算法
        public void RangeByYXS()
        {
            if (ReadyTeam.Count >= 1)
            {
                for (; Course(0, ReadyTeam).next <= Course(0, ReadyTeam).alltime; Course(0, ReadyTeam).next++)
                {
                    Console.WriteLine("程序执行第" + i + "S");
                    Course(0, ReadyTeam).state = "正在运行";
                    i++;
                    ReadsTeam();
                    CourseNowState();
                    Console.Read();
                }
                Console.WriteLine("程序执行" + i + "S");
                Course(0, ReadyTeam).state = "任务完成";
                ReadsTeam();
                CourseNowState();
                ReadyTeam.Remove(Course(0, ReadyTeam).id);
                RangeByYXS();
                if (ReadyTeam.Count >= 2)
                {
                    PanDuanYXJ();
                }
            }
            else
            {
                Console.WriteLine("所有进程都已运行完毕");
                Console.Read();
                Console.ReadLine();
            }
            
        }


        //优先数高的具有抢占性的优先数调度算法
        //public void YRangByYXS()
        //{
        //        for (int j = 0; j < Course(0, ReadyTeam).alltime - Course(0, ReadyTeam).next; j++)
        //        {
        //            i++;
        //            Course(0, ReadyTeam).next++;
                   
        //            if(Course(0,ReadyTeam).next==Course(0,ReadyTeam).alltime)
        //            {
        //               Course(0,ReadyTeam).state="任务完成";
        //            }
        //            else if (Course(0, ReadyTeam).next < Course(0, ReadyTeam).alltime)
        //            {
        //               Course(0, ReadyTeam).state = "正在运行";
        //            }
        //            ConfirmReady();
        //            CourseNowState();
        //            PanDuanYXJ();
        //            if(ReadyTeam.Count>=2)
        //            {
        //               YRangByYXS();
        //            }
        //            Console.Read();
        //        }
        //        ConfirmReady();
        //        CourseNowState();
        //        Console.Read();
           
            
        //}
        //根据时间的自动增长来执行函数
        public void Time()
        {
            if (i == 0)
            { 
                DataPrepareFunction();
                UpdateArray();
                CourseNowState();
                ConfirmReady();
            }
            
        }
    }
}
