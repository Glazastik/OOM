using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

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
            InitializeComponent();
            contact = c;     
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

        private void CancelButtonClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
