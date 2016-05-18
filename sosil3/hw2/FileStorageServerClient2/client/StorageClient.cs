using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.IO;
using System.Net.Sockets;
using server;

namespace client
{
    public class StorageClient
    {
        public TcpClient tcp_client;
        Action<Packet> receive_action;

        public StorageClient(Action<Packet> receive_action)
        {
            this.receive_action = receive_action;
        }

        public void send(string ip, string port, Packet pkt)
        {
            tcp_client = new TcpClient();
            goThread(() =>
            {
                try
                {
                    tcp_client.Connect(new IPEndPoint(IPAddress.Parse(ip), int.Parse(port)));
                    if (tcp_client.Connected)
                    { 
                        send(pkt);
                    }
                }
                catch (Exception)
                {
                    ;
                }
            });
        } 

        public void disconnect()
        {
            try
            {
                tcp_client?.Close();
            }
            catch (Exception)
            {
                ;
            }
        }
         
        private void send(Packet pkt)
        {
            try
            {
                byte[] b = new byte[Packet.PACKET_SIZE];
                b = pkt.serialize();

                using (NetworkStream ns = tcp_client.GetStream())
                {
                    ns.Write(b, 0, b.Length);
                    ns.Flush();
                    b = new byte[Packet.PACKET_SIZE];
                    ns.Read(b, 0, b.Length);
                    Packet pkt2 = Packet.deserialize(b);
                    receive_action(pkt2);
                }
            }
            catch (Exception)
            {
                ;
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
