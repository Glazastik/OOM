using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
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
        public ObservableCollection<Contact> contactList;
        ObservableCollection<Conversation> conversations; 
        public MainWindow()
        {
           
            contactList = new ObservableCollection<Contact>();
            conversations = new ObservableCollection<Conversation>();
            Contact c = new Contact();
            Contact d = new Contact();
            Contact me = new Contact();
            me.FirstName = "Me";
            c.FirstName = "Sven";
            c.LastName = "Svensson";
            d.FirstName = "Kalle";
            d.LastName = "Karlsson";
            Conversation t = new Conversation(c);
            Conversation y = new Conversation(d);
            t.addMessage(new Message("hej",c));
            t.addMessage(new Message("hejhej",me));
            y.addMessage(new Message("asdasdas",d));
            t.addMessage(new Message("asdhsadg",c));

            conversations.Add(t);
            conversations.Add(y);

            contactList.Add(c);
            contactList.Add(d);
            InitializeComponent();
            ContactListView.ItemsSource = contactList;
            ChatTabControl.ItemsSource = conversations;
            
        }

        private void OnSelectContact(object sender, SelectionChangedEventArgs e)
        {
            foreach (Conversation c in ChatTabControl.Items)
            {
                if(c.contact == ContactListView.SelectedItem)
                {
                    ChatTabControl.SelectedItem = c;
                    break;
                }
            }
        }

        private void ChatBox_OnKeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                TextBox box = (TextBox) sender;
                box.Text = ((Contact) box.DataContext).FirstName;
                Debug.WriteLine(box.GetHashCode());
            }
        }
    }
}
