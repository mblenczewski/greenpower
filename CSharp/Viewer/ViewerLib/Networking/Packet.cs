using System;

namespace ViewerLib.Networking
{
    /// <summary>
    /// Represents a data packet sent from the race car to the pits.
    /// </summary>
    public struct Packet : IPacket
    {
        private string data;

        public string Data
        {
            get { return data; }
            set { data = value; }
        }
    }
}