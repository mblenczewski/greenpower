using Viewer.ViewModels;
using Viewer.Views.Controls;

namespace Viewer.Commands.Index_Commands
{
    public class ResetSerialConfigCommand : Command<IndexViewModel>
    {
        /// <inheritdoc />
        public ResetSerialConfigCommand(IndexViewModel commandViewModel) : base(commandViewModel)
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
            viewModel.ResetSerialConfig(parameter);
        }
    }
}