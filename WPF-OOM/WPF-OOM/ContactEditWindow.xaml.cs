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
    /// Interaction logic for ContactEditWindow.xaml
    /// </summary>
    public partial class ContactEditWindow : Window
    {
        private Contact contact;
        public ContactEditWindow(Contact c)
        {
            
            contact = c;
            InitializeComponent();
            this.Visibility = Visibility.Visible;
            ContactGrid.DataContext = c;
            
        }

        private void AcceptButtonClick(object sender, RoutedEventArgs e)
        {
            BindingExpression be1 = FnameBox.GetBindingExpression(TextBox.TextProperty);
            BindingExpression be2 = NnameBox.GetBindingExpression(TextBox.TextProperty);
            BindingExpression be3 = LnameBox.GetBindingExpression(TextBox.TextProperty);
            be1.UpdateSource();
            be2.UpdateSource();
            be3.UpdateSource();
            this.Close();

        }
    }
}
