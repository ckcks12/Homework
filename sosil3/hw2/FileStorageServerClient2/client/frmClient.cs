using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using server;
using System.IO;
using System.Threading;

namespace client
{
    public partial class frmClient : Form
    {
        public StorageClient client;

        public frmClient()
        {
            InitializeComponent();
        }

        private void frmClient_Load(object sender, EventArgs e)
        {
            string ip = StorageClient.getIp().Trim();
            if (ip == null || ip == string.Empty)
            {
                ip = "127.0.0.1";
            }
            ip = "127.0.0.1";
            tbIp.Text = ip;
            tbPort.Text = "1444";

            client = new StorageClient(receive);
        }

        public void receive(Packet pkt)
        {
            Packet pkt2 = new Packet();

            switch (pkt.packet_type)
            {
                case Packet.PACKET_TYPE.TYPE_CONNECTION_OK:
                    pkt2.packet_type = Packet.PACKET_TYPE.TYPE_GET_FILE_LIST;
                    client.send(tbIp.Text, tbPort.Text, pkt2);
                    break;
                case Packet.PACKET_TYPE.TYPE_FILE_LIST:
                    List<string> file_list = (List<string>)pkt.data;
                    Invoke(new MethodInvoker(() => { updateFileList(file_list); }));
                    break;
                default:
                    break;
            }

        }

        private void updateFileList(List<string> file_list)
        {
            lvStorage.Items.Clear();
            foreach (string str in file_list)
            {
                string name = str.Split('|')[0];
                string size = str.Split('|')[1];
                lvStorage.Items.Add(new ListViewItem(new string[] { name, size }));
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (btnConnect.Text.Equals("Disconnect"))
            {
                btnConnect.Text = "Connect";
                client.disconnect();
                tbIp.Enabled = true;
                tbPort.Enabled = true;
                btnUpload.Enabled = false;
            }
            else
            {
                Packet pkt = new Packet();
                pkt.packet_type = Packet.PACKET_TYPE.TYPE_CONNECTION_OK;
                btnConnect.Text = "Disconnect";
                client.send(tbIp.Text, tbPort.Text, pkt);
                tbIp.Enabled = false;
                tbPort.Enabled = false;
                btnUpload.Enabled = true;
            }
        }

        private void btnStoragePath_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog dialog = new FolderBrowserDialog())
            {
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    tbStoragePath.Text = dialog.SelectedPath;
                }
            }
        }

        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    tbFilePath.Text = dlg.FileName;
                }
            }
        }

        private void btnUpload_Click(object sender, EventArgs e)
        {
            Packet file_name_pkt = new Packet();
            Packet pkt_cnt_pkt = new Packet();
            List<Packet> pkt_list = new List<Packet>();
            string name, path;

            if (tbFilePath.Text == "")
            {
                MessageBox.Show("어이어이~ 전송할파일은 좀 선.택.해주라구-_-?");
                return;
            }

            path = tbFilePath.Text;
            name = Path.GetFileName(path);

            file_name_pkt.packet_type = Packet.PACKET_TYPE.TYPE_FILE_NAME;
            file_name_pkt.data = name;

            byte[] b = File.ReadAllBytes(path);
            int pos = 0;
            while (pos < b.Length)
            {
                byte[] bb = new byte[Packet.PACKET_DATA_SIZE];
                Packet pkt = new Packet();

                for (int j = 0; j < Packet.PACKET_DATA_SIZE; pos++, j++)
                {
                    if (pos >= b.Length)
                    {
                        break;
                    }
                    bb[j] = b[pos];
                }

                pkt.packet_type = Packet.PACKET_TYPE.TYPE_FILE_DATA;
                pkt.data = bb;
                pkt_list.Add(pkt);
            }

            pkt_cnt_pkt.packet_type = Packet.PACKET_TYPE.TYPE_FILE_PKT_CNT;
            pkt_cnt_pkt.data = pkt_list.Count;

            // progress bar
            progressBar.Maximum = pkt_list.Count;
            progressBar.Value = 0;

            client.send(tbIp.Text, tbPort.Text, file_name_pkt);
            Thread.Sleep(1000);
            client.send(tbIp.Text, tbPort.Text, pkt_cnt_pkt);
            Thread.Sleep(1000);
            foreach (Packet p in pkt_list)
            {
                client.send(tbIp.Text, tbPort.Text, p);
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(10);
                    Application.DoEvents();
                }
                progressBar.Value++;
            }
        }

        private void lvStorage_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void lvStorage_MouseDoubleClick(object sender, MouseEventArgs e)
        {

        }
    }
}
