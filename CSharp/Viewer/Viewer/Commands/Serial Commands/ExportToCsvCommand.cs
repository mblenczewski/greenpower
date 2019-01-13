using Viewer.ViewModels;

namespace Viewer.Commands.Serial_Commands
{
    public class ExportToCsvCommand : Command<SerialViewModel>
    {
        /// <inheritdoc />
        public ExportToCsvCommand(SerialViewModel commandViewModel) : base(commandViewModel)
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
            viewModel.ExportToCsv(parameter);
        }
    }
}