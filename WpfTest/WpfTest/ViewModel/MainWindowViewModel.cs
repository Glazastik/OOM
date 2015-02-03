using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using WpfTest.Model;

namespace WpfTest.ViewModel
{
    class MainWindowViewModel : BaseViewModel
    {
        private string text;
        //private TestModel obj = new TestModel();

        public string GiveText
        {
            get
            {
                return text;
            }
            set
            {
                text = value;
                RaisePropertyChangedEvent("GiveText");
            }
        }

        public void ChangeText()
        {
            GiveText = Wrapper.GetMessage(512);
        }

        public ICommand ChangeTextCommand
        {
            get { return new DelegateCommand(ChangeText); }
        }
    }
}
