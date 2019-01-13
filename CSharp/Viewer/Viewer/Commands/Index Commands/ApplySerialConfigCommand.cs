using Viewer.ViewModels;

namespace Viewer.Commands.Index_Commands
{
    public class ApplySerialConfigCommand : Command<IndexViewModel>
    {
        /// <inheritdoc />
        public ApplySerialConfigCommand(IndexViewModel commandViewModel) :
            base(commandViewModel)
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
            viewModel.ApplySerialConfig(parameter);
        }
    }
}