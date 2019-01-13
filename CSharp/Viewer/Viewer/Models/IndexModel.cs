using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using ViewerLib.Serial;

namespace Viewer.Models
{
    public class IndexModel
    {
        private SerialConfig serialConfig;

        public SerialConfig SerialConfiguration
        {
            get { return serialConfig; }
            set { serialConfig = value; }
        }

        public List<string> AvailableComPorts
        {
            get { return new List<string>(System.IO.Ports.SerialPort.GetPortNames()); }
        }

        public string SerialPort
        {
            get { return serialConfig.PortName; }
            set { serialConfig.PortName = value; }
        }

        public int BaudRate
        {
            get { return serialConfig.BaudRate; }
            set { serialConfig.BaudRate = value; }
        }

        public Parity Parity
        {
            get { return serialConfig.Parity; }
            set { serialConfig.Parity = value; }
        }

        public int DataBits
        {
            get { return serialConfig.DataBits; }
            set { serialConfig.DataBits = value; }
        }

        public StopBits StopBit
        {
            get { return serialConfig.StopBits; }
            set { serialConfig.StopBits = value; }
        }

        public Handshake HandshakeProtocol
        {
            get { return serialConfig.Handshake; }
            set { serialConfig.Handshake = value; }
        }

        public IndexModel()
        {
            serialConfig.ReadTimeout = 500;
            serialConfig.WriteTimeout = 500;
        }
    }
}