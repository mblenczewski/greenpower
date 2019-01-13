using Viewer.ViewModels;

namespace Viewer.Commands.Serial_Commands
{
    public class RefreshSerialLogCommand : Command<SerialViewModel>
    {
        /// <inheritdoc />
        public RefreshSerialLogCommand(SerialViewModel commandViewModel) : base(commandViewModel)
        {
        }

        /// <inheritdoc />
        public override bool CanExecute(object parameter)
        {
            return true;
        }

        /// <inheritdoc />
        public override void Execute(object parameter)
        {
            viewModel.RefreshLog(parameter);
        }
    }
}