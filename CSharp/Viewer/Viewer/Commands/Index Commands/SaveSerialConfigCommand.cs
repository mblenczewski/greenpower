using Viewer.ViewModels;

namespace Viewer.Commands.Index_Commands
{
    public class SaveSerialConfigCommand : Command<IndexViewModel>
    {
        /// <inheritdoc />
        public SaveSerialConfigCommand(IndexViewModel commandViewModel) : base(commandViewModel)
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
            viewModel.SaveSerialConfig(parameter);
        }
    }
}