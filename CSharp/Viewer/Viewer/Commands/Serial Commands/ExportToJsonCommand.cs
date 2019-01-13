using Viewer.ViewModels;

namespace Viewer.Commands.Serial_Commands
{
    public class ExportToJsonCommand : Command<SerialViewModel>
    {
        /// <inheritdoc />
        public ExportToJsonCommand(SerialViewModel commandViewModel) : base(commandViewModel)
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
            viewModel.ExportToJson(parameter);
        }
    }
}