using ViewerLib.Serial;

namespace Viewer.ViewModels
{
    public class BatteryViewModel : ViewModel
    {
        private SerialHandler serialHandler;

        public BatteryViewModel(SerialHandler serialHandler)
        {
            this.serialHandler = serialHandler;
        }
    }
}