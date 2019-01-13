using System;
using System.Windows.Input;
using Viewer.ViewModels;

namespace Viewer.Commands
{
    public abstract class Command<T> : ICommand where T : ViewModel
    {
        protected T viewModel;

        protected Command(T commandViewModel)
        {
            viewModel = commandViewModel;
        }

        /// <inheritdoc />
        public virtual bool CanExecute(object parameter)
        {
            throw new NotImplementedException();
        }

        /// <inheritdoc />
        public virtual void Execute(object parameter)
        {
            throw new NotImplementedException();
        }

        /// <inheritdoc />
        public event EventHandler CanExecuteChanged;

        protected virtual void OnCanExecuteChanged(object sender, EventArgs args)
        {
            CanExecuteChanged?.Invoke(sender, args);
        }
    }
}