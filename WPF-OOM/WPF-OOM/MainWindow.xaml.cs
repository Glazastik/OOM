using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPF_OOM
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    public partial class MainWindow : Window
    {
        ObservableCollection<Contact> contactList;
        ObservableCollection<Conversation> conversations; 
        public MainWindow()
        {
            InitializeComponent();
            contactList = new ObservableCollection<Contact>();
            conversations = new ObservableCollection<Conversation>();
            Contact c = new Contact();
            Contact d = new Contact();
            c.FirstName = "Sven";
            c.LastName = "Svensson";
            d.FirstName = "Kalle";
            d.LastName = "Karlsson";
            Conversation t = new Conversation(c);
            Conversation y = new Conversation(d);
            t.addMessage(new Message("hej"));
            y.addMessage(new Message("asdasdas"));

            conversations.Add(t);
            conversations.Add(y);

            contactList.Add(c);
            contactList.Add(d);
            ContactListView.ItemsSource = contactList;
            ChatTabControl.ItemsSource = conversations;
        }
    }
}
