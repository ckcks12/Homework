using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace server
{
    public partial class frmServer : Form
    {
        public StorageServer server;
        public string path;

        public frmServer()
        {
            InitializeComponent();
        }

        private void frmServer_Load(object sender, EventArgs e)
        {
            //retrieve ip
            string ip = StorageServer.getIp();
            if (ip != null)
            {
                tbIp.Text = ip.Trim();
                tbIp.Text = "127.0.0.1";
            }
            //cannot retireve ip
            else
            {
                tbIp.Text = "ERROR";
            }

            // init port
            tbPort.Text = "1444";

            // init receiver
            server = new StorageServer(receive);
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            if (btnStart.Text.Equals("Stop"))
            {
                btnStart.Text = "Start";
                server.serverDisable();
                tbIp.Enabled = true;
                tbPort.Enabled = true;
                tbStoragePath.Enabled = true;
                btnChangeStoragePath.Enabled = true;
                log("서버가 중지되었습니다..." + tbPort.Text);
            }
            else
            {
                btnStart.Text = "Stop";
                server.init(tbIp.Text, tbPort.Text);
                tbIp.Enabled = false;
                tbPort.Enabled = false;
                tbStoragePath.Enabled = false;
                btnChangeStoragePath.Enabled = false;
                log("서버가 시작되었습니다..." + tbPort.Text);
            }
        }

        public void receive(Packet pkt)
        {
            Packet pkt2 = new Packet();

            switch (pkt.packet_type)
            {
                case Packet.PACKET_TYPE.TYPE_CONNECTION_OK:
                    pkt2.packet_type = Packet.PACKET_TYPE.TYPE_CONNECTION_OK;
                    server.send(pkt2);
                    break;
                case Packet.PACKET_TYPE.TYPE_GET_FILE_LIST:
                    Invoke(new MethodInvoker(() => { log("파일정보요청"); }));
                    List<string> file_list = new List<string>(Directory.GetFiles(tbStoragePath.Text));
                    for (int i = 0; i < file_list.Count; i++)
                    {
                        FileInfo f = new FileInfo(file_list[i]);
                        file_list[i] = Path.GetFileName(file_list[i]) + "|" + f.Length;
                    }
                    pkt2.packet_type = Packet.PACKET_TYPE.TYPE_FILE_LIST;
                    pkt2.data = file_list;
                    server.send(pkt2);
                    Invoke(new MethodInvoker(() => { log("파일정보보냄"); }));
                    break;
                case Packet.PACKET_TYPE.TYPE_FILE_NAME: 
                    string name = (string)pkt.data;
                    string path = tbStoragePath.Text + "\\" + name;
                    Invoke(new MethodInvoker(() => log("파일 전송 준비 : " + name)));
                    if (File.Exists(path))
                    {
                        File.Delete(path);
                    }
                    File.Create(tbStoragePath.Text + "\\" + name);
                    this.path = path;
                    server.send(pkt2);
                    break;
                case Packet.PACKET_TYPE.TYPE_FILE_PKT_CNT:
                    int cnt = (int)pkt.data;
                    Invoke(new MethodInvoker(() => log("파일 패킷 갯수 : " + cnt)));
                    server.send(pkt2);
                    break;
                case Packet.PACKET_TYPE.TYPE_FILE_DATA:
                    byte[] b = (byte[])pkt.data;
                    Invoke(new MethodInvoker(() => log("전송 받음 : " + b.Length)));
                    using (BinaryWriter writer = new BinaryWriter(new FileStream(this.path, FileMode.Append)))
                    {
                        writer.Write(b);
                        writer.Flush();
                    }
                    server.send(pkt2);
                    break;
                default:
                    break;
            }
        }

        private void log(object obj)
        {
            DateTime now = DateTime.Now;
            string time = $"{now.Hour}:{now.Minute}:{now.Second}";
            tbLog.Text += time + " > " + obj.ToString() + Environment.NewLine;
        }

        private void frmServer_FormClosing(object sender, FormClosingEventArgs e)
        {
            server?.listener?.Stop();
            server?.serverDisable();
        }

        private void btnChangeStoragePath_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog dialog = new FolderBrowserDialog())
            {
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    tbStoragePath.Text = dialog.SelectedPath;
                }
            }
        }

        private void folderBrowserDialog1_HelpRequest(object sender, EventArgs e)
        {

        }
    }
}
