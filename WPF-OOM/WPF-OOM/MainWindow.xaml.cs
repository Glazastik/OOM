using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace WPF_OOM
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>


    public partial class MainWindow : Window
    {
        public ObservableCollection<Contact> ContactList;
        ObservableCollection<Conversation> conversations;
        private Contact me;
        private Service fb;
        private Service steam;
        public MainWindow()
        {
            fb = new Facebook();
            steam = new Steam();
            ContactList = new ObservableCollection<Contact>();
            conversations = new ObservableCollection<Conversation>();
            Contact c = new Contact();
            Contact d = new Contact();
            me = new Contact();
            me.FirstName = "Me";
            c.FirstName = "Sven";
            c.LastName = "Svensson";
            d.FirstName = "Kalle";
            d.LastName = "Karlsson";
            Conversation t = new Conversation(c);
            Conversation y = new Conversation(d);
            Message m = new Message("this has logo", c, fb);
            m.Services.Add(steam);
            t.AddMessage(m);
            t.AddMessage(new Message("hej", c, fb));
            t.AddMessage(new Message("hejhej", me, fb));
            y.AddMessage(new Message("asdasdas", d, fb));
            t.AddMessage(new Message("asdhsadg", c, fb));

            conversations.Add(t);
            conversations.Add(y);

            ContactList.Add(c);
            ContactList.Add(d);
            InitializeComponent();
            ContactListView.ItemsSource = ContactList;
            ChatTabControl.ItemsSource = conversations;

        }

        private void OnSelectContact(object sender, SelectionChangedEventArgs e)
        {
            foreach (Conversation c in ChatTabControl.Items)
            {
                if (c.Contact == ContactListView.SelectedItem)
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
                TextBox box = (TextBox)sender;
                string text = box.Text;
                if (text.Length > 0)
                {
                    Conversation conv = (Conversation)ChatTabControl.SelectedItem;
                    conv.AddMessage(new Message(text, me, fb));
                    conv.DraftMessage = "";
                }

            }
        }

        private void SendMessageButtonClick(object sender, RoutedEventArgs e)
        {
            Conversation c = (Conversation)ChatTabControl.SelectedItem;
            if (!string.IsNullOrEmpty(c.DraftMessage))
            {
                c.AddMessage(new Message(c.DraftMessage, me, fb));
                c.DraftMessage = "";
            }

        }

        private void EditContact(object sender, RoutedEventArgs e)
        {
            if (sender is MenuItem)
            {
                Contact c = (Contact)ContactListView.SelectedItem;
                new ContactEditWindow(c);
            }
        }

        private void DeleteContact(object sender, RoutedEventArgs e)
        {
            ContactList.Remove((Contact) ContactListView.SelectedItem);
            ContactListView.SelectedIndex = 0;
        }

        private void NewContactMenu(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}
