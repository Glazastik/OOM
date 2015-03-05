using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms.VisualStyles;
using System.Windows.Input;

namespace WPF_OOM
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>


    public partial class MainWindow : Window
    {
        public static ObservableCollection<Contact> ContactList { get; private set; }
        public static ObservableCollection<Conversation> conversations { get; private set; }
        private Service fb;
        public Service steam { get; private set; }
        public MainWindow()
        {
            this.Closing += this.HideWindow;
            fb = new Facebook();
            steam = new Steam();

            ContactList = new ObservableCollection<Contact>();
            conversations = new ObservableCollection<Conversation>();
            Contact c = new Contact();
            Contact d = new Contact();
            c.FirstName = "Sven";
            c.LastName = "Svensson";
            d.FirstName = "Kalle";
            d.LastName = "Karlsson";
            c.addService(steam, "sven_1337");
            d.addService(fb, "Kalle_Karlsson");
            d.addService(steam, "l33thax0r");
            Conversation t = new Conversation(c);
            Conversation y = new Conversation(d);
            Message m = new Message("this has logo", c, fb);
            m.Services.Add(steam);
            t.AddMessage(m);
            t.AddMessage(new Message("hej", c, fb));
            t.AddMessage(new Message("hejhej", Contact.Me, fb));
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
                Conversation c = (Conversation)ChatTabControl.SelectedItem;
                c.SendMessage();

            }
        }

        private void SendMessageButtonClick(object sender, RoutedEventArgs e)
        {
            //TabItem ti = (TabItem) ChatTabControl.SelectedContent;
            //ListView lv = (ListView)((TabItem) ChatTabControl.SelectedContent).FindName("ServiceListView");
            //Debug.WriteLine(ti.ToString());
            Conversation c = (Conversation)ChatTabControl.SelectedItem;
            c.SendMessage();

        }

        private void EditContact(object sender, RoutedEventArgs e)
        {
            if (sender is MenuItem)
            {
                Contact c = (Contact)ContactListView.SelectedItem;
                new ContactEditWindow(c, false);
            }
        }

        private void DeleteContact(object sender, RoutedEventArgs e)
        {
            ContactList.Remove((Contact) ContactListView.SelectedItem);
            ContactListView.SelectedIndex = 0;
        }

        private void NewContactMenu(object sender, RoutedEventArgs e)
        {
            new ContactEditWindow(new Contact(), true);
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            Environment.Exit(0);
        }

        private void HideWindow(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            //this.WindowState = WindowState.Minimized;
            Environment.Exit(0);
        }
    }
}
