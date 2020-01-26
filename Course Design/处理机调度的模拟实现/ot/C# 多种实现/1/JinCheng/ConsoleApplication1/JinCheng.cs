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
        public string id;     //��ʶ��
        public int prc;       //������
        public int cputime;   //ʱ��Ƭ
        public int alltime;   //��ʱ��
        public int next;      //ָ��
        public string state;  //��ǰ״̬
        public int InputTime; //��������ʱ��
    
    }
    class JinCheng
    {

        
        public CourseInput Course1 = new CourseInput();  //��������1
        public CourseInput Course2 = new CourseInput();  //��������2
        public CourseInput Course3 = new CourseInput();  //��������3
        public CourseInput Course4 = new CourseInput();  //��������4
        public CourseInput Course5 = new CourseInput();  //��������5
        public ArrayList IdStaticTeam = new ArrayList(); //��������id����
        public ArrayList NoReadyTeam = new ArrayList(); //����δ��������id����
        public ArrayList ReadyTeam = new ArrayList();    //����δ������������
        public static int i = 0;    //����ʱ��
        public static int k = 0;
        public string Choose = "";                       //�洢��ѡ���˺����㷨

        //��Ӳ������ݺ���
        public void DataPrepareFunction()
        {
            Course1.id = "a"; Course1.prc = 4; Course1.cputime = 6; Course1.alltime = 10; Course1.InputTime = 0;
            Course2.id = "b"; Course2.prc = 6; Course2.cputime = 4; Course2.alltime = 20; Course2.InputTime = 5;
            Course3.id = "c"; Course3.prc = 5; Course3.cputime = 5; Course3.alltime = 15; Course3.InputTime = 4;
            Course4.id = "d"; Course4.prc = 8; Course4.cputime = 8; Course4.alltime = 24; Course4.InputTime = 2;
            Course5.id = "e"; Course5.prc = 3; Course5.cputime = 7; Course5.alltime = 30; Course5.InputTime = 20;
            //��ʼ��next��state
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
        //��ʾ���̵�ԭʼ״̬
        public void CourseNowState()
        {
            if (i == 0)
            {
                Console.WriteLine("��ʶ��  " + "������  " + "ʱ��Ƭ " + "��ʱ��  " + "���̽���ʱ��  ");

                for (int j = 0; j < IdStaticTeam.Count; j++)
                {
                    Console.WriteLine("   " + Course(j, IdStaticTeam).id + "       " + Course(j, IdStaticTeam).prc + "      " + Course(j, IdStaticTeam).cputime + "      " + Course(j, IdStaticTeam).alltime + "          " + Course(j, IdStaticTeam).InputTime); ;
                }
                //Console.WriteLine("�����������");
                //Console.Read();
            }
            else
            {
                Console.WriteLine("��ʶ��  " + "������  " + "ʱ��Ƭ " + "��ʱ��  " + "���̽���ʱ��  " + "���̵�ǰ״̬  " + "�����е�ʱ��");

                for (int j = 0; j < IdStaticTeam.Count; j++)
                {
                    Console.WriteLine("   " + Course(j, IdStaticTeam).id + "       " + Course(j, IdStaticTeam).prc + "      " + Course(j, IdStaticTeam).cputime + "      " + Course(j, IdStaticTeam).alltime + "          " + Course(j, IdStaticTeam).InputTime + "          " + Course(j, IdStaticTeam).state + "           " + Course(j, IdStaticTeam).next); ;
                }
                //Console.WriteLine("�����������");
                //Console.Read();

            }
        }
        
        //��ʼ��IdStaticTeam��NoReadyTeam����
        public void UpdateArray()
        {
            IdStaticTeam.Add(Course1.id);
            IdStaticTeam.Add(Course2.id);
            IdStaticTeam.Add(Course3.id);
            IdStaticTeam.Add(Course4.id);
            IdStaticTeam.Add(Course5.id);
        }

       //���������е�idֵ��ȡCourse�����̣�������
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
        
        //�жϽ����Ƿ����
        public void ConfirmReady()
        {
            
            for (int a = 0; a < NoReadyTeam.Count; a++)
            {
                if (Course(a,NoReadyTeam).InputTime<= i)
                {
                    Course(a, NoReadyTeam).state = "����";
                    ReadyTeam.Add(Course(a, NoReadyTeam).id.ToString());
                    NoReadyTeam.Remove(Course(a, NoReadyTeam).id.ToString());
                }
                else
                {
                    Course(a, NoReadyTeam).state = "δ����";
                }

            }
            if (i == 0)
            {
                Console.WriteLine("��ѡ����̵����㷨");
                Console.WriteLine("���롾N����ʾѡ�񲻾��������Ե��������㷨");
                //Console.WriteLine("���롾Y����ʾѡ����������Ե��������㷨");
                Console.WriteLine("���롾S����ʾѡ��ʱ��Ƭ��ת��");
                Choose = Console.ReadLine();
                if (Choose == "N")
                {
                    Console.WriteLine("��ѡ���˲����������Ե������������㷨");
                    RangeByYXS();
                }
                else if (Choose == "S") 
                {
                    Console.WriteLine("��ѡ����ʱ��Ƭ�����㷨");
                    RangBySJP();
                }
                //else if (Choose == "Y")
                //{
                //    Console.WriteLine("��ѡ���˾��������Ե��������㷨");
                //    YRangByYXS();
                //}

            }

        }

        //Ϊ����ִ���жϾ�������
        public void ReadsTeam()
        {
            ConfirmReady();
            Console.WriteLine("*******************************************************************************");
            Console.Read();
        }

        //ʱ��Ƭ��ת˳�����
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

        //ʱ��Ƭ��ת��
        public void RangBySJP()
        {

            if ((Course(0, IdStaticTeam).next == Course(0, IdStaticTeam).alltime) && (Course(1, IdStaticTeam).next == Course(1, IdStaticTeam).alltime) && (Course(2, IdStaticTeam).next == Course(2, IdStaticTeam).alltime) && (Course(3, IdStaticTeam).next == Course(3, IdStaticTeam).alltime) && (Course(4, IdStaticTeam).next == Course(4, IdStaticTeam).alltime))
            {
                Console.WriteLine("���н��̶��Ѿ����");
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
                            Course(0, ReadyTeam).state = "�������";
                            ReadyTeam.Remove(Course(0, ReadyTeam).id.ToString());
                            ReadsTeam();
                            CourseNowState();
                            RangBySJP();
                        }
                        else
                        {
                            Console.WriteLine("����ִ�е�" + i + "S");
                            Course(0, ReadyTeam).state = "��������";
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
       
        //������id���������ɸߵ�������
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
        
        //�����������Ե��������㷨
        public void RangeByYXS()
        {
            if (ReadyTeam.Count >= 1)
            {
                for (; Course(0, ReadyTeam).next <= Course(0, ReadyTeam).alltime; Course(0, ReadyTeam).next++)
                {
                    Console.WriteLine("����ִ�е�" + i + "S");
                    Course(0, ReadyTeam).state = "��������";
                    i++;
                    ReadsTeam();
                    CourseNowState();
                    Console.Read();
                }
                Console.WriteLine("����ִ��" + i + "S");
                Course(0, ReadyTeam).state = "�������";
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
                Console.WriteLine("���н��̶����������");
                Console.Read();
                Console.ReadLine();
            }
            
        }


        //�������ߵľ�����ռ�Ե������������㷨
        //public void YRangByYXS()
        //{
        //        for (int j = 0; j < Course(0, ReadyTeam).alltime - Course(0, ReadyTeam).next; j++)
        //        {
        //            i++;
        //            Course(0, ReadyTeam).next++;
                   
        //            if(Course(0,ReadyTeam).next==Course(0,ReadyTeam).alltime)
        //            {
        //               Course(0,ReadyTeam).state="�������";
        //            }
        //            else if (Course(0, ReadyTeam).next < Course(0, ReadyTeam).alltime)
        //            {
        //               Course(0, ReadyTeam).state = "��������";
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
        //����ʱ����Զ�������ִ�к���
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
