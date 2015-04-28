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
    /// Interaction logic for EditAccountWindow.xaml
    /// </summary>
    public partial class EditAccountWindow : Window
    {
        private Person person;
        public EditAccountWindow(Person p)
        {
            person = p;
            InitializeComponent();
            this.Visibility = Visibility.Visible;
        }

        private void AcceptClick(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(IdBox.Text))
            {
                Account account;
                switch (ServiceBox.SelectedIndex)
                {
                    
                    case -1: //Unselected
                        break;
                    //Google Hangouts
                    case 0:
                        account = new Account(MainWindow.nextAccountID, 0, IdBox.Text);
                        MainWindow.nextAccountID++;
                        ChatWrapper.AddAccountToPerson(person.GetId(), account);
                        person.Accounts.Add(account);
                        this.Close();

                        break;
                    //IRC
                    case 1: this.Close();
                        account = new Account(MainWindow.nextAccountID, 1, IdBox.Text);
                        MainWindow.nextAccountID++;
                        ChatWrapper.AddAccountToPerson(person.GetId(), account);
                        person.Accounts.Add(account);
                        this.Close();
                        break;
                }
            }
            else
            {
                //ErrorLabel.Foreground = Brushes.Red;
                //ErrorLabel.Content = "Error: Enter an ID";
            }
        }
    }
}
