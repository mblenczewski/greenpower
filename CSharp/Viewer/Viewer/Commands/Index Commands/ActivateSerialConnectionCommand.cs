using Viewer.ViewModels;

namespace Viewer.Commands.Index_Commands
{
    public class ActivateSerialConnectionCommand : Command<IndexViewModel>
    {
        /// <inheritdoc />
        public ActivateSerialConnectionCommand(IndexViewModel commandViewModel) : base(commandViewModel)
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
            viewModel.ActivateSerialConnection(parameter);
        }
    }
}