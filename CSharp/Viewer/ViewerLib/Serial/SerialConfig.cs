using System.IO.Ports;

namespace ViewerLib.Serial
{
    /// <summary>
    /// Stores a configuration for a serial port.
    /// </summary>
    public struct SerialConfig
    {
        /// <summary>
        /// The name of the COM port to use for the serial connection.
        /// </summary>
        public string PortName { get; set; }

        /// <summary>
        /// The baud rate the connection runs at.
        /// </summary>
        public int BaudRate { get; set; }

        /// <summary>
        /// The parity bit to use for any data sent to and from the connection.
        /// </summary>
        public Parity Parity { get; set; }

        /// <summary>
        /// The amount of bits used for storing data.
        /// </summary>
        public int DataBits { get; set; }

        /// <summary>
        /// The amount of bits used as stop bits.
        /// </summary>
        public StopBits StopBits { get; set; }

        /// <summary>
        /// The handshake protocol to use.
        /// </summary>
        public Handshake Handshake { get; set; }

        /// <summary>
        /// The amount of time to wait for data to be read from the serial
        /// stream before timing out, in milliseconds.
        /// </summary>
        public int ReadTimeout { get; set; }

        /// <summary>
        /// The amount of time to wait for data to be written to the serial
        /// stream before timing out, in milliseconds.
        /// </summary>
        public int WriteTimeout { get; set; }

        /// <summary>
        /// Constructs a serial config struct with the given parameters.
        /// </summary>
        /// <param name="portName">The name of the COM port to use.</param>
        /// <param name="baudRate">The baud rate for the connection.</param>
        /// <param name="parity">The parity bit (if any).</param>
        /// <param name="dataBits">The amount of data bits in use.</param>
        /// <param name="stopBits">The stop bits.</param>
        /// <param name="handshake">The handshake protocol to use.</param>
        /// <param name="readTimeout">
        /// The amount of time to wait for data to be read from the serial
        /// stream before timing out, in milliseconds.
        /// </param>
        /// <param name="writeTimeout">
        /// The amount of time to wait for data to be written to the serial
        /// stream before timing out, in milliseconds.
        /// </param>
        public SerialConfig(
            string portName,
            int baudRate = 9600,
            Parity parity = Parity.None,
            int dataBits = 8,
            StopBits stopBits = StopBits.One,
            Handshake handshake = Handshake.None,
            int readTimeout = 500,
            int writeTimeout = 500)
        {
            PortName = portName;
            BaudRate = baudRate;
            Parity = parity;
            DataBits = dataBits;
            StopBits = stopBits;
            Handshake = handshake;
            ReadTimeout = readTimeout;
            WriteTimeout = writeTimeout;
        }
    }
}