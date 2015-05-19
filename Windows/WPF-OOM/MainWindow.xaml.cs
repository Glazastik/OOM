using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Threading;
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

        public static ObservableCollection<Person> PersonList { get; private set; }
        public static ObservableCollection<Conversation> conversations { get; private set; }
        public static int nextPersonID { get; private set; }
        public static int nextAccountID { get; set; }
        private MessageWorker messageWorker;
        private Thread messageThread;

        public MainWindow()
        {
            ChatWrapper.Init();
            messageWorker = new MessageWorker();
            messageThread = new Thread(messageWorker.DoWork);
            messageThread.Start();
            while (!messageThread.IsAlive);

            nextPersonID = 0;
            nextAccountID = 0;
            this.Closing += this.HideWindow;
            PersonList = new ObservableCollection<Person>();
            conversations = new ObservableCollection<Conversation>();

            Person testPerson = new Person(nextPersonID, "Testelina");
            nextPersonID++;
            PersonList = new ObservableCollection<Person>();
            PersonList.Add(testPerson);

            ChatWrapper.AddPerson(testPerson);
            Account account = new Account(nextAccountID++, 0, "1qb37r9krc35d08l0pdn0m4c8m@public.talk.google.com");
            Account acc2 = new Account(nextAccountID++, 1, "testerino");
            testPerson.AddAccount(account);
            testPerson.AddAccount(acc2);

            ChatWrapper.AddAccountToPerson(testPerson.GetId(), account);
            ChatWrapper.AddAccountToPerson(testPerson.GetId(),acc2);
            ChatWrapper.ConnectService(0);
            //ChatWrapper.ConnectService(1);
            Conversation t = new Conversation(testPerson);

            

            InitializeComponent();
            ChatTabControl.ItemsSource = conversations;
            PersonListView.ItemsSource = PersonList;
            conversations.Add(t);

        }

        private void OnSelectPerson(object sender, SelectionChangedEventArgs e)
        {
            foreach (Conversation c in ChatTabControl.Items)
            {
                if (c.Person == PersonListView.SelectedItem)
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

        private void EditPerson(object sender, RoutedEventArgs e)
        {
            if (sender is MenuItem)
            {
                Person p = (Person) PersonListView.SelectedItem;
                new PersonEditWindow(p, false);
            }
        }

        private void DeletePerson(object sender, RoutedEventArgs e)
        {
            PersonList.Remove((Person) PersonListView.SelectedItem);
            PersonListView.SelectedIndex = 0;
        }

        private void NewPersonMenu(object sender, RoutedEventArgs e)
        {
            nextPersonID++;
            new PersonEditWindow(new Person(nextPersonID-1,""), true);
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            Trace.WriteLine("EXITING");
            ChatWrapper.Stop();
            Trace.WriteLine("CHATWRAPPER STOPPED");
            messageWorker.StopWorking();
            Trace.WriteLine("MESSAGEWORKER STOPPED WORKING");
            messageThread.Join();
            Trace.WriteLine("THREAD JOINED");
            Environment.Exit(0);
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            this.Exit(this, null);
        }

        private void HideWindow(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            //this.WindowState = WindowState.Minimized;
            Environment.Exit(0);
        }

        private void newService(object sender, RoutedEventArgs e)
        {
            new EditAccountWindow(PersonList.First());
        }
    }
}
