using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.IO;
using System.Net.Sockets;

namespace server
{
    public class StorageServer
    {
        public TcpListener listener;
        public Socket sock;
        Action<Packet> receive_action;
        public bool enable;

        public StorageServer(Action<Packet> receive_action)
        {
            this.receive_action = receive_action;
        }

        public void init(string ip, string port)
        {
            if (listener != null)
            {
                listener.Stop();
            }
            listener = new TcpListener(new IPEndPoint(IPAddress.Parse(ip), int.Parse(port)));
            listener.Start();
            enable = true;

            goThread(() =>
            {
                while (enable)
                {
                    try
                    {
                        sock = listener.AcceptSocket();
                        receive();
                    }
                    catch (Exception)
                    {
                        ;
                    }
                }
            });
        }

        public void serverDisable()
        {
            enable = false;
            listener?.Stop();
        }

        public void receive()
        {
            try
            {

                if (!sock.Connected)
                {
                    return;
                }

                byte[] b = new byte[Packet.PACKET_SIZE];

                using (NetworkStream ns = new NetworkStream(sock))
                {
                    ns.Read(b, 0, b.Length);
                    ns.Flush();
                }

                Packet pkt = Packet.deserialize(b);

                receive_action(pkt);
            }
            catch (Exception)
            {
                ;
            }
        }

        public void send(Packet pkt)
        {
            try
            {

                byte[] b = new byte[Packet.PACKET_SIZE];
                b = pkt.serialize();

                if (!sock.Connected)
                { 
                    return;
                }
                using (NetworkStream ns = new NetworkStream(sock))
                {
                    ns.Write(b, 0, b.Length);
                    ns.Flush();
                }
            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.ToString());
            }
        }

        public void goThread(Action act)
        {
            new Thread(new ThreadStart(act)).Start();
        }

        /// <summary>
        /// return this machine's public ip
        /// </summary>
        public static string getIp()
        {
            HttpWebRequest req;
            HttpWebResponse resp;
            string ip;

            req = (HttpWebRequest)WebRequest.CreateHttp("http://api.ipify.org");
            resp = (HttpWebResponse)req.GetResponse();

            using (StreamReader sr = new StreamReader(resp.GetResponseStream()))
            {
                ip = sr.ReadToEnd();
            }

            return ip;
        }
    }
}
