using System.ComponentModel;
using ViewerLib.Serial;

namespace Viewer.ViewModels
{
    public sealed class MainViewModel : ViewModel
    {
        #region Variables

        private SerialHandler serialHandler;

        #endregion Variables

        #region Properties

        /// <summary>
        /// The view model that binds an index model to an index view.
        /// See <see cref="IndexViewModel"/> for more.
        /// </summary>
        public IndexViewModel IndexView { get; set; }

        /// <summary>
        /// The view model that binds a serial model to a serial view.
        /// See <see cref="SerialViewModel"/> for more.
        /// </summary>
        public SerialViewModel SerialView { get; set; }

        /// <summary>
        /// The view model that binds a car model to a car view.
        /// See <see cref="CarViewModel"/> for more.
        /// </summary>
        public CarViewModel CarView { get; set; }

        /// <summary>
        /// The view model that binds a battery model to a battery view.
        /// See <see cref="BatteryViewModel"/> for more.
        /// </summary>
        public BatteryViewModel BatteryView { get; set; }

        /// <summary>
        /// The view model that binds a racetrack model to a racetrack view.
        /// See <see cref="RacetrackViewModel"/> for more.
        /// </summary>
        public RacetrackViewModel RacetrackView { get; set; }

        #endregion Properties

        #region Constructor

        public MainViewModel()
        {
            serialHandler = new SerialHandler();

            IndexView = new IndexViewModel(serialHandler);

            SerialView = new SerialViewModel(serialHandler);

            CarView = new CarViewModel(serialHandler);

            BatteryView = new BatteryViewModel(serialHandler);

            RacetrackView = new RacetrackViewModel(serialHandler);
        }

        #endregion Constructor

        #region Methods

        /// <summary>
        /// Performs a clean shutdown, closing any used resources.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        public void CleanShutdown(object sender, CancelEventArgs args)
        {
            if (serialHandler.IsActive)
            {
                serialHandler.StopSerialReaderThread();
            }
        }

        #endregion Methods
    }
}