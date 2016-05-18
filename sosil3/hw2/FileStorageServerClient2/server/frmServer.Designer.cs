namespace server
{
    partial class frmServer
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
            this.label1 = new System.Windows.Forms.Label();
            this.tbIp = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbPort = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tbStoragePath = new System.Windows.Forms.TextBox();
            this.btnChangeStoragePath = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.tbLog = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP : ";
            // 
            // tbIp
            // 
            this.tbIp.Location = new System.Drawing.Point(46, 6);
            this.tbIp.MaxLength = 15;
            this.tbIp.Name = "tbIp";
            this.tbIp.Size = new System.Drawing.Size(180, 21);
            this.tbIp.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(232, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "port : ";
            // 
            // tbPort
            // 
            this.tbPort.Location = new System.Drawing.Point(276, 6);
            this.tbPort.MaxLength = 5;
            this.tbPort.Name = "tbPort";
            this.tbPort.Size = new System.Drawing.Size(59, 21);
            this.tbPort.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 44);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(107, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "file storage path : ";
            // 
            // tbStoragePath
            // 
            this.tbStoragePath.BackColor = System.Drawing.Color.White;
            this.tbStoragePath.Location = new System.Drawing.Point(14, 59);
            this.tbStoragePath.Name = "tbStoragePath";
            this.tbStoragePath.ReadOnly = true;
            this.tbStoragePath.Size = new System.Drawing.Size(290, 21);
            this.tbStoragePath.TabIndex = 5;
            // 
            // btnChangeStoragePath
            // 
            this.btnChangeStoragePath.Location = new System.Drawing.Point(310, 59);
            this.btnChangeStoragePath.Name = "btnChangeStoragePath";
            this.btnChangeStoragePath.Size = new System.Drawing.Size(27, 23);
            this.btnChangeStoragePath.TabIndex = 6;
            this.btnChangeStoragePath.Text = "...";
            this.btnChangeStoragePath.UseVisualStyleBackColor = true;
            this.btnChangeStoragePath.Click += new System.EventHandler(this.btnChangeStoragePath_Click);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(80, 86);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(180, 58);
            this.btnStart.TabIndex = 7;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // tbLog
            // 
            this.tbLog.BackColor = System.Drawing.Color.Black;
            this.tbLog.ForeColor = System.Drawing.Color.Lime;
            this.tbLog.Location = new System.Drawing.Point(12, 150);
            this.tbLog.Multiline = true;
            this.tbLog.Name = "tbLog";
            this.tbLog.ReadOnly = true;
            this.tbLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbLog.Size = new System.Drawing.Size(323, 324);
            this.tbLog.TabIndex = 8;
            // 
            // frmServer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(349, 486);
            this.Controls.Add(this.tbLog);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.btnChangeStoragePath);
            this.Controls.Add(this.tbStoragePath);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbIp);
            this.Controls.Add(this.label1);
            this.Name = "frmServer";
            this.Text = "thㅓ버";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmServer_FormClosing);
            this.Load += new System.EventHandler(this.frmServer_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbIp;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbPort;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbStoragePath;
        private System.Windows.Forms.Button btnChangeStoragePath;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.TextBox tbLog;
    }
}