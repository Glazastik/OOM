using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WPF_OOM
{
    /// <summary>
    /// Interaction logic for AddNewContactWindow.xaml
    /// </summary>
    public partial class AddNewContactWindow : Window
    {
        public AddNewContactWindow()
        {
            InitializeComponent();
            this.Visibility = Visibility.Visible;
        }

        private void CreateContact(object sender, RoutedEventArgs e)
        {
            Contact c = new Contact();
            c.FirstName = "New";
            c.LastName = "New";
            c.NickName = "Contact";
            MainWindow.ContactList.Add(c);
        }
    }
}
