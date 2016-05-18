namespace client
{
    partial class frmClient
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.tbIp = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbPort = new System.Windows.Forms.TextBox();
            this.btnStoragePath = new System.Windows.Forms.Button();
            this.btnSelectFile = new System.Windows.Forms.Button();
            this.btnUpload = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.tbStoragePath = new System.Windows.Forms.TextBox();
            this.tbFilePath = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.lvStorage = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(16, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP";
            // 
            // tbIp
            // 
            this.tbIp.Location = new System.Drawing.Point(34, 6);
            this.tbIp.Name = "tbIp";
            this.tbIp.Size = new System.Drawing.Size(154, 21);
            this.tbIp.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(194, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(27, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Port";
            // 
            // tbPort
            // 
            this.tbPort.Location = new System.Drawing.Point(227, 6);
            this.tbPort.Name = "tbPort";
            this.tbPort.Size = new System.Drawing.Size(60, 21);
            this.tbPort.TabIndex = 3;
            // 
            // btnStoragePath
            // 
            this.btnStoragePath.Location = new System.Drawing.Point(14, 33);
            this.btnStoragePath.Name = "btnStoragePath";
            this.btnStoragePath.Size = new System.Drawing.Size(83, 36);
            this.btnStoragePath.TabIndex = 4;
            this.btnStoragePath.Text = "File path";
            this.btnStoragePath.UseVisualStyleBackColor = true;
            this.btnStoragePath.Click += new System.EventHandler(this.btnStoragePath_Click);
            // 
            // btnSelectFile
            // 
            this.btnSelectFile.Location = new System.Drawing.Point(103, 33);
            this.btnSelectFile.Name = "btnSelectFile";
            this.btnSelectFile.Size = new System.Drawing.Size(83, 36);
            this.btnSelectFile.TabIndex = 5;
            this.btnSelectFile.Text = "Select File";
            this.btnSelectFile.UseVisualStyleBackColor = true;
            this.btnSelectFile.Click += new System.EventHandler(this.btnSelectFile_Click);
            // 
            // btnUpload
            // 
            this.btnUpload.Enabled = false;
            this.btnUpload.Location = new System.Drawing.Point(192, 33);
            this.btnUpload.Name = "btnUpload";
            this.btnUpload.Size = new System.Drawing.Size(83, 36);
            this.btnUpload.TabIndex = 6;
            this.btnUpload.Text = "Upload";
            this.btnUpload.UseVisualStyleBackColor = true;
            this.btnUpload.Click += new System.EventHandler(this.btnUpload_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(14, 75);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(261, 36);
            this.btnConnect.TabIndex = 7;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 141);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(42, 12);
            this.label3.TabIndex = 8;
            this.label3.Text = "Path : ";
            // 
            // tbStoragePath
            // 
            this.tbStoragePath.Location = new System.Drawing.Point(60, 138);
            this.tbStoragePath.Name = "tbStoragePath";
            this.tbStoragePath.ReadOnly = true;
            this.tbStoragePath.Size = new System.Drawing.Size(215, 21);
            this.tbStoragePath.TabIndex = 9;
            // 
            // tbFilePath
            // 
            this.tbFilePath.Location = new System.Drawing.Point(60, 165);
            this.tbFilePath.Name = "tbFilePath";
            this.tbFilePath.ReadOnly = true;
            this.tbFilePath.Size = new System.Drawing.Size(215, 21);
            this.tbFilePath.TabIndex = 11;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 168);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(37, 12);
            this.label4.TabIndex = 10;
            this.label4.Text = "File : ";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(12, 192);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(263, 21);
            this.progressBar.TabIndex = 12;
            // 
            // lvStorage
            // 
            this.lvStorage.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.lvStorage.GridLines = true;
            this.lvStorage.Location = new System.Drawing.Point(14, 219);
            this.lvStorage.Name = "lvStorage";
            this.lvStorage.Size = new System.Drawing.Size(261, 143);
            this.lvStorage.TabIndex = 13;
            this.lvStorage.UseCompatibleStateImageBehavior = false;
            this.lvStorage.View = System.Windows.Forms.View.Details;
            this.lvStorage.SelectedIndexChanged += new System.EventHandler(this.lvStorage_SelectedIndexChanged);
            this.lvStorage.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lvStorage_MouseDoubleClick);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Name";
            this.columnHeader1.Width = 160;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Size";
            this.columnHeader2.Width = 89;
            // 
            // frmClient
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(306, 374);
            this.Controls.Add(this.lvStorage);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.tbFilePath);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.tbStoragePath);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnUpload);
            this.Controls.Add(this.btnSelectFile);
            this.Controls.Add(this.btnStoragePath);
            this.Controls.Add(this.tbPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbIp);
            this.Controls.Add(this.label1);
            this.Name = "frmClient";
            this.Text = "클ㄹrㅇ1언트";
            this.Load += new System.EventHandler(this.frmClient_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbIp;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbPort;
        private System.Windows.Forms.Button btnStoragePath;
        private System.Windows.Forms.Button btnSelectFile;
        private System.Windows.Forms.Button btnUpload;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbStoragePath;
        private System.Windows.Forms.TextBox tbFilePath;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.ListView lvStorage;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
    }
}

