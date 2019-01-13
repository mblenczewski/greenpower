using ViewerLib.Serial;

namespace Viewer.ViewModels
{
    public class RacetrackViewModel : ViewModel
    {
        private SerialHandler serialHandler;

        public RacetrackViewModel(SerialHandler serialHandler)
        {
            this.serialHandler = serialHandler;
        }
    }
}