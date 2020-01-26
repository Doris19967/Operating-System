using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OSTest1
{
    class Process
    {
        private String name;
        private String runtime;
        private String arrivetime;
        private String level;
        private double math_arrivetime;
        private double math_runtime;
        private int math_level;
        private double response_ratio;

        public double Response_ratio
        {
            get { return response_ratio; }
            set { response_ratio = value; }
        }
        public int Math_level
        {
            get { return math_level; }
            set { math_level = value; }
        }
    
        public String Name
        {
            get { return name; }
            set { name = value; }
        }
        public double Math_arrivetime
        {
            get { return math_arrivetime; }
            set { math_arrivetime = value; }
        }       
        public double Math_runtime
        {
            get { return math_runtime; }
            set { math_runtime = value; }
        }
        public String Arrivetime
        {
            get { return arrivetime; }
            set { arrivetime = value; }
        }
        
        public String Runtime
        {
            get { return runtime; }
            set { runtime = value; }
        }

        public Process(String name, String arrivetime, String runtime,String level) {
            this.name = name;
            this.arrivetime = arrivetime;
            this.runtime = runtime;
            this.level = level;
            initMath();
        }
        public Process() { }
       private void initMath() {
           math_level = Convert.ToInt32(level);
           math_arrivetime = Convert.ToDouble(arrivetime);
           math_runtime = Convert.ToDouble(runtime);      
        }

       public void SetResponseratior(double W) {
           this.response_ratio = (W + math_runtime) / math_runtime;
       }
    }
}
