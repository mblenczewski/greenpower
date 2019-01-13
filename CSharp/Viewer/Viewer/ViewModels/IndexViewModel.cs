using System.Collections.Generic;
using System.IO.Ports;
using System.Windows.Input;
using Viewer.Commands.Index_Commands;
using Viewer.Models;
using ViewerLib.Serial;
using ViewerLib.Utils;

namespace Viewer.ViewModels
{
    public class IndexViewModel : ViewModel
    {
        private const string SavedSerialSettingsDir = "serialSettings.txt";

        #region Variables

        private SerialHandler serialHandler;

        private IndexModel model;

        private ApplySerialConfigCommand applySerialConfig;

        private SaveSerialConfigCommand saveSerialConfig;

        private ResetSerialConfigCommand resetSerialConfig;

        private ActivateSerialConnectionCommand activateSerialConnection;

        private DeactivateSerialConnectionCommand deactivateSerialConnection;

        #endregion Variables

        #region Properties

        #region Serial Configuration

        public List<string> AvailableSerialPorts
        {
            get { return model.AvailableComPorts; }
        }

        public string SerialPort
        {
            get { return model.SerialPort; }
            set
            {
                model.SerialPort = value;
                OnPropertyChanged(nameof(SerialPort));
            }
        }

        public int BaudRate
        {
            get { return model.BaudRate; }
            set
            {
                model.BaudRate = value;
                OnPropertyChanged(nameof(BaudRate));
            }
        }

        public Parity ParityBit
        {
            get { return model.Parity; }
            set
            {
                model.Parity = value;
                OnPropertyChanged(nameof(ParityBit));
            }
        }

        public int DataBits
        {
            get { return model.DataBits; }
            set
            {
                model.DataBits = value;
                OnPropertyChanged(nameof(DataBits));
            }
        }

        public StopBits StopBit
        {
            get { return model.StopBit; }
            set
            {
                model.StopBit = value;
                OnPropertyChanged(nameof(StopBit));
            }
        }

        public Handshake HandshakeProtocol
        {
            get { return model.HandshakeProtocol; }
            set
            {
                model.HandshakeProtocol = value;
                OnPropertyChanged(nameof(HandshakeProtocol));
            }
        }

        public ICommand ApplySerialConfigCommand
        {
            get { return applySerialConfig; }
        }

        public ICommand SaveSerialConfigCommand
        {
            get { return saveSerialConfig; }
        }

        public ICommand ResetSerialConfigCommand
        {
            get { return resetSerialConfig; }
        }

        #endregion Serial Configuration

        #region Serial Status

        public bool SerialActive
        {
            get { return serialHandler.IsActive; }
        }

        public bool SerialInactive
        {
            get { return !SerialActive; }
        }

        public ICommand ActivateSerialCommand
        {
            get { return activateSerialConnection; }
        }

        public ICommand DeactivateSerialCommand
        {
            get { return deactivateSerialConnection; }
        }

        #endregion Serial Status

        #endregion Properties

        #region Constructors

        public IndexViewModel() : this(null)
        {
        }

        public IndexViewModel(SerialHandler serialHandler)
        {
            this.serialHandler = serialHandler;

            model = new IndexModel();

            applySerialConfig = new ApplySerialConfigCommand(this);
            saveSerialConfig = new SaveSerialConfigCommand(this);
            resetSerialConfig = new ResetSerialConfigCommand(this);
            activateSerialConnection = new ActivateSerialConnectionCommand(this);
            deactivateSerialConnection = new DeactivateSerialConnectionCommand(this);

            ResetSerialConfig(null);
        }

        #endregion Constructors

        #region Methods

        public void ApplySerialConfig(object param)
        {
            SerialConfig configuration = model.SerialConfiguration;
            serialHandler.ConfigureSerialConnection(configuration);
        }

        public void SaveSerialConfig(object param)
        {
            SerialConfig configuration = model.SerialConfiguration;
            JsonFileHandler.Write(configuration, SavedSerialSettingsDir);
        }

        public void ResetSerialConfig(object param)
        {
            SerialConfig savedConfiguration =
                JsonFileHandler.Read<SerialConfig>(SavedSerialSettingsDir);

            model.SerialConfiguration = savedConfiguration;
        }

        public void ActivateSerialConnection(object param)
        {
            ApplySerialConfig(null);
            serialHandler.StartSerialReaderThread();
            OnPropertyChanged(nameof(SerialActive));
            OnPropertyChanged(nameof(SerialInactive));
        }

        public void DeactivateSerialConnection(object param)
        {
            serialHandler.StopSerialReaderThread();
            OnPropertyChanged(nameof(SerialActive));
            OnPropertyChanged(nameof(SerialInactive));
        }

        #endregion Methods
    }
}