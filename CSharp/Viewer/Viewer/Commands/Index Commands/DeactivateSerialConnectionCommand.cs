using Viewer.ViewModels;

namespace Viewer.Commands.Index_Commands
{
    public class DeactivateSerialConnectionCommand : Command<IndexViewModel>
    {
        /// <inheritdoc />
        public DeactivateSerialConnectionCommand(IndexViewModel commandViewModel) : base(commandViewModel)
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
            viewModel.DeactivateSerialConnection(parameter);
        }
    }
}