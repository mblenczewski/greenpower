using System;

namespace ViewerLib.Networking
{
    public struct SerialPacket : IPacket
    {
        private DateTime timestamp;

        public string Timestamp
        {
            get { return timestamp.ToString(); }
        }

        private string data;

        public string Data
        {
            get { return data; }
            set { data = value; }
        }
    }
}