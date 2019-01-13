using System;
using System.Collections.Generic;
using ViewerLib.Networking;

namespace Viewer.Models
{
    public class SerialModel
    {
        #region Variables

        private List<SerialPacket> serialLog;

        #endregion Variables

        #region Properties

        public List<SerialPacket> SerialLog
        {
            get { return serialLog; }
            set { serialLog = value; }
        }

        #endregion Properties

        #region Constructors

        public SerialModel()
        {
            serialLog = new List<SerialPacket>
            {
                new SerialPacket { Data = "Test Packet 1" },
                new SerialPacket { Data = "Test Packet 2" },
                new SerialPacket { Data = "Test Packet 3" }
            };
        }

        #endregion Constructors

        #region Methods

        public void AddPacket(SerialPacket packet)
        {
            serialLog.Add(packet);
        }

        #endregion Methods
    }
}