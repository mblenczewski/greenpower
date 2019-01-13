using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows.Input;
using Viewer.Commands.Serial_Commands;
using Viewer.Models;
using ViewerLib.Networking;
using ViewerLib.Serial;
using ViewerLib.Utils;

namespace Viewer.ViewModels
{
    public class SerialViewModel : ViewModel
    {
        #region Variables

        private SerialHandler serialHandler;

        private SerialModel model;

        private RefreshSerialLogCommand refreshLog;

        private ExportToCsvCommand exportToCsv;
        private const string CsvDir = "csvLogs\\packetLog";

        private ExportToJsonCommand exportToJson;
        private const string JsonDir = "jsonLogs\\packetLog";

        #endregion Variables

        #region Properties

        public ObservableCollection<SerialPacket> SerialLog
        {
            get { return new ObservableCollection<SerialPacket>(model.SerialLog); }
        }

        public ICommand RefreshLogCommand
        {
            get { return refreshLog; }
        }

        public ICommand ExportToCsvCommand
        {
            get { return exportToCsv; }
        }

        public ICommand ExportToJsonCommand
        {
            get { return exportToJson; }
        }

        #endregion Properties

        #region Constructors

        public SerialViewModel() : this(null)
        {
        }

        public SerialViewModel(SerialHandler serialHandler)
        {
            model = new SerialModel();

            this.serialHandler = serialHandler;
            this.serialHandler.ReceivedPacket += packet =>
            {
                model.AddPacket(packet);
                OnPropertyChanged(nameof(SerialLog));
            };

            model.SerialLog = new List<SerialPacket>();

            refreshLog = new RefreshSerialLogCommand(this);
            exportToCsv = new ExportToCsvCommand(this);
            exportToJson = new ExportToJsonCommand(this);
        }

        #endregion Constructors

        #region Methods

        private string GetDate()
        {
            DateTime date = DateTime.Today;
            return $"{date.Day}-{date.Month}-{date.Year}";
        }

        public void RefreshLog(object param)
        {
            OnPropertyChanged(nameof(SerialLog));
        }

        public void ExportToCsv(object param)
        {
            string fullFileName =
                CsvDir + GetDate() + ".csv";

            CsvFileHandler.Write(model.SerialLog.ToArray(), fullFileName);
        }

        public void ExportToJson(object param)
        {
            string fullFileName =
                JsonDir + GetDate() + ".json";

            JsonFileHandler.Write(model.SerialLog, fullFileName);
        }

        #endregion Methods
    }
}