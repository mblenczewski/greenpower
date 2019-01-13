using ViewerLib.Serial;

namespace Viewer.ViewModels
{
    public class CarViewModel : ViewModel
    {
        private SerialHandler serialHandler;

        public CarViewModel(SerialHandler serialHandler)
        {
            this.serialHandler = serialHandler;
        }
    }
}