namespace WindowsFormsApplication2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.butLoad = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.butTimer = new System.Windows.Forms.Button();
            this.butMakeXML = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.cmbZoom = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.butReset = new System.Windows.Forms.Button();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.butReadData = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.butStop = new System.Windows.Forms.Button();
            this.txtMsg = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.text_adc0 = new System.Windows.Forms.TextBox();
            this.text_adc1 = new System.Windows.Forms.TextBox();
            this.text_adc2 = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // chart1
            // 
            this.chart1.BackColor = System.Drawing.Color.Transparent;
            this.chart1.BackImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.chart1.BackSecondaryColor = System.Drawing.Color.Silver;
            this.chart1.BorderSkin.BackColor = System.Drawing.Color.MediumAquamarine;
            chartArea3.AxisX.Interval = 6D;
            chartArea3.AxisX.MajorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            chartArea3.AxisX.ScaleView.MinSizeType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Minutes;
            chartArea3.AxisX.ScrollBar.BackColor = System.Drawing.Color.Transparent;
            chartArea3.AxisX.ScrollBar.ButtonColor = System.Drawing.Color.Gray;
            chartArea3.AxisY.MajorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            chartArea3.AxisY.ScrollBar.BackColor = System.Drawing.Color.Transparent;
            chartArea3.AxisY.ScrollBar.ButtonColor = System.Drawing.Color.Gray;
            chartArea3.BackColor = System.Drawing.Color.Black;
            chartArea3.BackSecondaryColor = System.Drawing.Color.Green;
            chartArea3.CursorX.IsUserEnabled = true;
            chartArea3.CursorX.IsUserSelectionEnabled = true;
            chartArea3.CursorY.IsUserEnabled = true;
            chartArea3.CursorY.IsUserSelectionEnabled = true;
            chartArea3.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea3);
            legend3.AutoFitMinFontSize = 10;
            legend3.BackColor = System.Drawing.Color.Black;
            legend3.ForeColor = System.Drawing.Color.White;
            legend3.ItemColumnSpacing = 20;
            legend3.Name = "Legend1";
            legend3.Position.Auto = false;
            legend3.Position.Height = 10F;
            legend3.Position.Width = 20F;
            legend3.Position.X = 76F;
            legend3.Position.Y = 6F;
            this.chart1.Legends.Add(legend3);
            this.chart1.Location = new System.Drawing.Point(3, 102);
            this.chart1.Name = "chart1";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series3.Legend = "Legend1";
            series3.MarkerColor = System.Drawing.Color.Red;
            series3.Name = "Watts";
            this.chart1.Series.Add(series3);
            this.chart1.Size = new System.Drawing.Size(436, 461);
            this.chart1.TabIndex = 0;
            this.chart1.Text = "chart1";
            // 
            // butLoad
            // 
            this.butLoad.Location = new System.Drawing.Point(13, 31);
            this.butLoad.Name = "butLoad";
            this.butLoad.Size = new System.Drawing.Size(75, 23);
            this.butLoad.TabIndex = 1;
            this.butLoad.Text = "Load";
            this.butLoad.UseVisualStyleBackColor = true;
            this.butLoad.Click += new System.EventHandler(this.butLoad_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(103, 31);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(62, 21);
            this.comboBox1.TabIndex = 2;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // butTimer
            // 
            this.butTimer.Location = new System.Drawing.Point(891, 15);
            this.butTimer.Name = "butTimer";
            this.butTimer.Size = new System.Drawing.Size(75, 23);
            this.butTimer.TabIndex = 4;
            this.butTimer.Text = "Timer";
            this.butTimer.UseVisualStyleBackColor = true;
            this.butTimer.Click += new System.EventHandler(this.butTimer_Click);
            // 
            // butMakeXML
            // 
            this.butMakeXML.Location = new System.Drawing.Point(891, 43);
            this.butMakeXML.Name = "butMakeXML";
            this.butMakeXML.Size = new System.Drawing.Size(128, 21);
            this.butMakeXML.TabIndex = 6;
            this.butMakeXML.Text = "MakeXML";
            this.butMakeXML.UseVisualStyleBackColor = true;
            this.butMakeXML.Click += new System.EventHandler(this.butMakeXML_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(103, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Hour";
            // 
            // cmbZoom
            // 
            this.cmbZoom.FormattingEnabled = true;
            this.cmbZoom.Location = new System.Drawing.Point(185, 31);
            this.cmbZoom.Name = "cmbZoom";
            this.cmbZoom.Size = new System.Drawing.Size(86, 21);
            this.cmbZoom.TabIndex = 8;
            this.cmbZoom.SelectedIndexChanged += new System.EventHandler(this.cmbZoom_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(186, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Zoom in Minutes";
            // 
            // butReset
            // 
            this.butReset.Location = new System.Drawing.Point(277, 29);
            this.butReset.Name = "butReset";
            this.butReset.Size = new System.Drawing.Size(75, 23);
            this.butReset.TabIndex = 5;
            this.butReset.Text = "Reset";
            this.butReset.UseVisualStyleBackColor = true;
            this.butReset.Click += new System.EventHandler(this.butReset_Click);
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(414, 31);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(51, 20);
            this.txtPort.TabIndex = 10;
            this.txtPort.Text = "COM1";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(382, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(26, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Port";
            // 
            // butReadData
            // 
            this.butReadData.Location = new System.Drawing.Point(471, 31);
            this.butReadData.Name = "butReadData";
            this.butReadData.Size = new System.Drawing.Size(75, 23);
            this.butReadData.TabIndex = 12;
            this.butReadData.Text = "ReadData";
            this.butReadData.UseVisualStyleBackColor = true;
            this.butReadData.Click += new System.EventHandler(this.butReadData_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // butStop
            // 
            this.butStop.Location = new System.Drawing.Point(551, 31);
            this.butStop.Name = "butStop";
            this.butStop.Size = new System.Drawing.Size(75, 23);
            this.butStop.TabIndex = 13;
            this.butStop.Text = "Stop";
            this.butStop.UseVisualStyleBackColor = true;
            this.butStop.Click += new System.EventHandler(this.butStop_Click);
            // 
            // txtMsg
            // 
            this.txtMsg.BackColor = System.Drawing.Color.Black;
            this.txtMsg.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtMsg.ForeColor = System.Drawing.Color.Lime;
            this.txtMsg.Location = new System.Drawing.Point(647, 18);
            this.txtMsg.Name = "txtMsg";
            this.txtMsg.Size = new System.Drawing.Size(244, 38);
            this.txtMsg.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(101, 70);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(0, 29);
            this.label4.TabIndex = 15;
            // 
            // text_adc0
            // 
            this.text_adc0.BackColor = System.Drawing.Color.Black;
            this.text_adc0.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text_adc0.ForeColor = System.Drawing.Color.Lime;
            this.text_adc0.Location = new System.Drawing.Point(302, 635);
            this.text_adc0.Name = "text_adc0";
            this.text_adc0.Size = new System.Drawing.Size(244, 38);
            this.text_adc0.TabIndex = 16;
            // 
            // text_adc1
            // 
            this.text_adc1.BackColor = System.Drawing.Color.Black;
            this.text_adc1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text_adc1.ForeColor = System.Drawing.Color.Lime;
            this.text_adc1.Location = new System.Drawing.Point(621, 635);
            this.text_adc1.Name = "text_adc1";
            this.text_adc1.Size = new System.Drawing.Size(244, 38);
            this.text_adc1.TabIndex = 17;
            // 
            // text_adc2
            // 
            this.text_adc2.BackColor = System.Drawing.Color.Black;
            this.text_adc2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text_adc2.ForeColor = System.Drawing.Color.Lime;
            this.text_adc2.Location = new System.Drawing.Point(453, 564);
            this.text_adc2.Name = "text_adc2";
            this.text_adc2.Size = new System.Drawing.Size(244, 38);
            this.text_adc2.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1004, 685);
            this.Controls.Add(this.text_adc2);
            this.Controls.Add(this.text_adc1);
            this.Controls.Add(this.text_adc0);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtMsg);
            this.Controls.Add(this.butStop);
            this.Controls.Add(this.butReadData);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cmbZoom);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.butMakeXML);
            this.Controls.Add(this.butReset);
            this.Controls.Add(this.butTimer);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.butLoad);
            this.Controls.Add(this.chart1);
            this.ForeColor = System.Drawing.Color.Black;
            this.Name = "Form1";
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Button butLoad;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button butTimer;
        private System.Windows.Forms.Button butMakeXML;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cmbZoom;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button butReset;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button butReadData;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button butStop;
        private System.Windows.Forms.TextBox txtMsg;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox text_adc0;
        private System.Windows.Forms.TextBox text_adc1;
        private System.Windows.Forms.TextBox text_adc2;
    }
}

