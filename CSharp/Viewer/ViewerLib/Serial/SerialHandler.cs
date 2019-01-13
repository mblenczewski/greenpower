using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Threading;
using ViewerLib.Networking;
using ViewerLib.Utils;

namespace ViewerLib.Serial
{
    /// <summary>
    /// A class for interacting with a serial stream.
    /// </summary>
    public class SerialHandler
    {
        #region Variables

        private bool readSerialConnection;
        private Thread readThread;

        private readonly object serialPacketLock;

        private readonly SerialPort serialPort;

        #endregion Variables

        #region Properties

        public bool IsActive
        {
            get { return readThread != null; }
        }

        #endregion Properties

        #region Constructors

        public SerialHandler()
        {
            serialPort = new SerialPort();
            serialPacketLock = new object();
        }

        #endregion Constructors

        #region Methods

        /// <summary>
        /// Configures the serial connection with the given parameters.
        /// </summary>
        /// <param name="configuration">
        /// The serial configuration to use. See <see cref="SerialConfig"/>.
        /// </param>
        public void ConfigureSerialConnection(SerialConfig configuration)
        {
            serialPort.PortName = configuration.PortName;
            serialPort.BaudRate = configuration.BaudRate;
            serialPort.Parity = configuration.Parity;
            serialPort.DataBits = configuration.DataBits;
            serialPort.StopBits = configuration.StopBits;
            serialPort.Handshake = configuration.Handshake;
            serialPort.ReadTimeout = configuration.ReadTimeout;
            serialPort.WriteTimeout = configuration.WriteTimeout;
        }

        public void StartSerialReaderThread()
        {
            if (readThread == null) // if thread hasn't been started
            {
                serialPort.Open();
                readSerialConnection = true;
                readThread = new Thread(Read);
                readThread.Start();
            }
        }

        public void StopSerialReaderThread()
        {
            if (readThread != null) // if the thread has been started
            {
                readSerialConnection = false;
                readThread.Join();
                readThread = null;
                serialPort.Close();
            }
        }

        private void Read()
        {
            while (readSerialConnection)
            {
                try
                {
                    bool hasValidPacket = true;
                    string packet = serialPort.ReadLine();
                    SerialPacket serialPacket = new SerialPacket { Data = packet };
                    /*
                    try
                    {
                        serialPacket =
                            JsonFileHandler.Deserialise<SerialPacket>(packet);
                        hasValidPacket = true;
                    }
                    catch (JsonReaderException)
                    {
                    }
                    */
                    if (hasValidPacket)
                    {
                        lock (serialPacketLock)
                        {
                            OnReceivedPacket(serialPacket);
                        }
                    }
                }
                catch (TimeoutException)
                {
                }
            }
        }

        #endregion Methods

        #region Events

        public event Action<SerialPacket> ReceivedPacket;

        private void OnReceivedPacket(SerialPacket packet)
        {
            ReceivedPacket?.Invoke(packet);
        }

        #endregion Events
    }
}