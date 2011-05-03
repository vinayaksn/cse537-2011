using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using System.Xml.Linq;


namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        string[] te;
        float[] tm;
        int[] wt;
        int count;


        StreamReader timer_data;

        public Form1()
        {
            InitializeComponent();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cmbZoom.Items.Add(5);
            cmbZoom.Items.Add(10);
            cmbZoom.Items.Add(15);
            cmbZoom.Items.Add(30);
            cmbZoom.Items.Add(45);
            cmbZoom.Items.Add(60);
            
            butStop.Enabled = false;
            txtMsg.ReadOnly = true;
            
            chart1.Width = this.Size.Width;
            //chart1.BackColor = Form1.DefaultBackColor;
            //chart1.BackSecondaryColor = chart1.BackColor;
            //chart1.ChartAreas[0].BackColor = chart1.BackColor;

            // Enable range selection and zooming end user interface
            chart1.ChartAreas[0].CursorX.IsUserEnabled = true;
            chart1.ChartAreas[0].CursorY.IsUserEnabled = true;
            chart1.ChartAreas[0].CursorX.IsUserSelectionEnabled = true;
            chart1.ChartAreas[0].AxisX.ScaleView.Zoomable = true;
            chart1.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = false;
            chart1.ChartAreas[0].AxisY.ScrollBar.IsPositionedInside = false;

            //chart1.ChartAreas[0].AxisY.Interval = 2;
            //MessageBox.Show(chart1.ChartAreas[0].AxisY.Interval + "");
        }

        // works for only one sensor
        private bool loadCSVData(string filename)
        {
            List<string> time = new List<string>();
            List<float> temparature = new List<float>();
            List<int> watts = new List<int>();
            string prvhr = "";
            String line;

            StreamReader sr = new StreamReader(filename);
            line = sr.ReadLine();
            comboBox1.Items.Clear();

            while ((line = sr.ReadLine()) != null)
            {
                string[] s = line.Split(',');

                if (s[0].Length < 8)
                    s[0] = "0" + s[0];

                time.Add(s[0]);
                temparature.Add(float.Parse(s[1]));
                watts.Add(int.Parse(s[2]));

                string[] hh = s[0].Split(':');
                
                if (!hh[0].Equals(prvhr))
                {
                    comboBox1.Items.Add(hh[0]);
                    prvhr = hh[0];
                }
            }

            te = time.ToArray();
            tm = temparature.ToArray();
            wt = watts.ToArray();
            count = te.Length;

            chart1.Series[0].Points.DataBindXY(te, wt);
            //chart1.Series[1].Points.DataBindXY(te, tm);

            return true;
        }

        // works for only one sensor
        private bool loadXMLData(string filename)
        {
            List<string> time = new List<string>();
            List<float> temparature = new List<float>();
            List<int> watts = new List<int>();
            string prvhr = "";
            String line;

            StreamReader sr = new StreamReader(filename);
            line = sr.ReadLine();
            comboBox1.Items.Clear();

            XElement xmldata = XElement.Load(filename);
            XElement data = xmldata.Element(XName.Get("watts"));

            XmlTextReader xr = new XmlTextReader(filename);
            while (xr.Read())
            {
                if (xr.NodeType == XmlNodeType.Element)
                {
                    if (xr.Name.Equals("time"))
                    {
                        xr.Read();
                        //t = t + " " + xr.Value.ToString();
                        time.Add(xr.Value.ToString());

                        string[] hh = xr.Value.ToString().Split(':');
                        
                        if (!hh[0].Equals(prvhr))
                        {
                            comboBox1.Items.Add(hh[0]);
                            prvhr = hh[0];
                        }

                    }
                    else if (xr.Name.Equals("tmpr"))
                    {
                        xr.Read();
                        //tt = tt + " " + xr.Value.ToString();
                        temparature.Add(float.Parse(xr.Value.ToString()));
                    }
                    else if (xr.Name.Equals("watts"))
                    {
                        xr.Read();
                        //w = w + " " + xr.Value.ToString();
                        watts.Add(int.Parse(xr.Value.ToString()));
                    }
                }

            }
            
            //MessageBox.Show(t);
            //MessageBox.Show(tt);
            //MessageBox.Show(w);

            te = time.ToArray();
            tm = temparature.ToArray();
            wt = watts.ToArray();
            count = te.Length;

            chart1.Series[0].Points.DataBindXY(te, wt);
            //chart1.Series[1].Points.DataBindXY(te, tm);
            
            return true;
        }


        private void butLoad_Click(object sender, System.EventArgs e)
        {
            //String filename = "D:\\muc\\ENVI\\data\\PC 2010-12-17.csv";
            //String filename = "D:\\muc\\ENVI\\data\\PC 2010-12-17 1.xml";

            openFileDialog1.Filter = "XML files (*.xml)|*.xml|CSV files (*.csv)|*.csv";
            if (openFileDialog1.ShowDialog() != DialogResult.OK)
                return;

            
            string filename = openFileDialog1.FileName;
            string ext = Path.GetExtension(filename);
            label4.Text = Path.GetFileName(filename);

            if (ext.Equals(".xml"))
                loadXMLData(filename);
            else if (ext.Equals(".csv"))
                loadCSVData(filename);

        }

        private void comboBox1_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            
            string hh = comboBox1.SelectedItem+"";

            //int hh = int.Parse(comboBox1.SelectedItem+"");
            //MessageBox.Show("" + hh + "  " + count);

            
            List<string> time = new List<string>();
            List<float> temparature = new List<float>();
            List<int> watts = new List<int>();
            
            
            for (int i = 0; i < count; ++i)
            {
                if( te[i].StartsWith(hh) )
                {
                    time.Add(te[i]);
                    temparature.Add(tm[i]);
                    watts.Add(wt[i]);
                }
            }
            
            string[] fte = time.ToArray();
            float[]  ftm = temparature.ToArray();
            int[]    fwt = watts.ToArray();


            chart1.ChartAreas[0].AxisX.Interval = 6;
            //MessageBox.Show("" + hh + "  " + count + "   " + fte.Length);

            chart1.Series[0].Points.DataBindXY(fte, fwt);
            //chart1.Series[1].Points.DataBindXY(fte, ftm);

            //chart1.Update();
            //chart1.Show();

        }

        int reccount;
        List<string> t1 = new List<string>();
        List<float> t2 = new List<float>();
        List<int> t3 = new List<int>();
        string prvhr = "";
        string readline = "";

        private void timer1_Tick(object sender, System.EventArgs e)
        {
            string line;
            if ((line = timer_data.ReadLine()) != null)
            {
                string[] s = line.Split(',');

                t1.Add(s[0]);
                t2.Add(float.Parse(s[1]));
                t3.Add(int.Parse(s[2]));

                string[] te = t1.ToArray();
                float[]  tm = t2.ToArray();
                int[]    wt = t3.ToArray();

                if ( te.Length > 60 )
                    chart1.ChartAreas[0].Axes[0].Interval = 6;

                chart1.Series[0].Points.DataBindXY(te, wt);
               // chart1.Series[1].Points.DataBindXY(te, tm);
            }
        }

        private void butTimer_Click(object sender, System.EventArgs e)
        {

            timer1.Stop();

            String filename = "D:\\muc\\ENVI\\Book1.csv";
            timer_data = new StreamReader(filename);
            MessageBox.Show(timer_data.ReadLine());

            timer1.Enabled = true;
            timer1.Interval = 100;
            timer1.Start();

            t1.Clear();
            t2.Clear();
            t3.Clear();
        }


        private void butZoomOut_Click(object sender, EventArgs e)
        {
            chart1.ChartAreas[0].AxisX.ScaleView.ZoomReset();
        }

        private void butMakeXML_Click(object sender, System.EventArgs e)
        {
            
            openFileDialog1.Filter = "Text files (*.txt)|*.txt";

            if (openFileDialog1.ShowDialog() != DialogResult.OK)
                return;
            
            
            string txtfname = openFileDialog1.FileName;
            string xmlfname = txtfname.Replace(".txt", ".xml");
            string filename = Path.GetFileNameWithoutExtension(txtfname);

            string line;
            
            MessageBox.Show(filename, xmlfname);

            StreamReader sr = new StreamReader(txtfname);
            StreamWriter sw = new StreamWriter(xmlfname);

            sw.WriteLine("<" + filename + "_data>");
            while ((line = sr.ReadLine()) != null)
            {
                //blind assumption
                if (line.StartsWith("<msg>") && line.EndsWith("</msg>") && !line.Contains("<hist>"))
                    sw.WriteLine(line);
            }
            sw.WriteLine("</" + filename + "_data>");
            sr.Close();
            sw.Close();
            MessageBox.Show(xmlfname, "File created");
        }

        private void cmbZoom_SelectedIndexChanged(object sender, EventArgs e)
        {
            int limit = int.Parse(cmbZoom.SelectedItem+"");
            chart1.ChartAreas[0].AxisX.ScaleView.Zoom(1, limit*10);
            chart1.ChartAreas[0].AxisX.Interval = limit / 5;
        }

        private void butReset_Click(object sender, EventArgs e)
        {
            chart1.ChartAreas[0].AxisX.ScaleView.ZoomReset();
            
            if( te != null )
                chart1.Series[0].Points.DataBindXY(te, wt);

        }

        private void butReadData_Click(object sender, EventArgs e)
        {
            if (!txtPort.Text.Trim().StartsWith("COM"))
            {
                MessageBox.Show("Invalid port name " + txtPort.Text);
                return;
            }

            serialPort1.PortName = txtPort.Text.Trim();
            serialPort1.BaudRate = 9600;
            serialPort1.DataBits = 8;
            serialPort1.StopBits = System.IO.Ports.StopBits.One;

            try
            {
                serialPort1.Open();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.ToString());
                return;
            }

            t1.Clear();
            t2.Clear();
            t3.Clear();
            comboBox1.Items.Clear();

            butReadData.Enabled = false;
            butStop.Enabled = true;

        }


        private void updateData(object sender, EventArgs e )
        {

            //MessageBox.Show(readline);

            string timestamp;
            DateTime t = DateTime.Now;
            timestamp = t.Hour + ":" + t.Minute + ":" + t.Second + "." + t.Millisecond;
            // update variable readline
            txtMsg.Text = ADC[0].ToString();
            text_adc0.Text = ADC[0].ToString();
            text_adc1.Text = ADC[1].ToString();
            text_adc2.Text = addr.ToString();
            //text_adc3.Text = ADC[3].ToString();
            //text_adc4.Text = ADC[4].ToString();
            if (addr == 3)
            {
                t1.Add(timestamp);
                //            t3.Add(int.Parse(readline));
                t3.Add(ADC[0]);

                string[] te = t1.ToArray();
                float[] tm = t2.ToArray();
                int[] wt = t3.ToArray();

                chart1.Series[0].Points.DataBindXY(te, wt);
            }
        }

                
        int[] ADC= new int[2];
        int addr=new int();



private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
 {
            //readline = serialPort1.ReadLine();
            byte StartByte = (byte)serialPort1.ReadByte();

    if (StartByte == 0x7E){
            
        byte ignore;

        for(int i =0; i<3;i++){
            ignore = (byte)serialPort1.ReadByte();
        }

        byte firstaddr = (byte)serialPort1.ReadByte();
        byte secondaddr = (byte)serialPort1.ReadByte();
        addr = (int)firstaddr;
        addr = addr << 8;
        addr = addr + (int)secondaddr;

        for (int i = 5; i < 10; i++)
        {
            ignore = (byte)serialPort1.ReadByte();
        }

        for (int i = 0; i < 5; i++)
        {

            byte firstByte = (byte)serialPort1.ReadByte();
            byte secondByte = (byte)serialPort1.ReadByte();
            ADC[0] = (int)firstByte;
            ADC[0] = ADC[0] << 8;
            ADC[0] = ADC[0] + (int)secondByte;

            //adc chanel 0 from node 3, is temprature sensor
            ADC[0] = (int)((double)(ADC[0]) * 0.32258064516129);

            firstByte = (byte)serialPort1.ReadByte();
            secondByte = (byte)serialPort1.ReadByte();
            ADC[1] = (int)firstByte;
            ADC[1] = ADC[1] << 8;
            ADC[1] = ADC[1] + (int)secondByte;
           /* firstByte = (byte)serialPort1.ReadByte();
            secondByte = (byte)serialPort1.ReadByte();
            ADC[2] = (int)firstByte;
            ADC[2] = ADC[2] << 8;
            ADC[2] = ADC[2] + (int)secondByte;
            firstByte = (byte)serialPort1.ReadByte();
            secondByte = (byte)serialPort1.ReadByte();
            ADC[3] = (int)firstByte;
            ADC[3] = ADC[3] << 8;
            ADC[3] = ADC[3] + (int)secondByte;
            firstByte = (byte)serialPort1.ReadByte();
            secondByte = (byte)serialPort1.ReadByte();
            ADC[4] = (int)firstByte;
            ADC[4] = ADC[4] << 8;
            ADC[4] = ADC[4] + (int)secondByte;
            */

            
               this.Invoke(new EventHandler(updateData));
        }

        ignore = (byte)serialPort1.ReadByte();

    }//if

}




        private void butStop_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                butStop.Enabled = false;
                butReadData.Enabled = true;
            }
        }

    }
}
