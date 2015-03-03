﻿using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;

namespace WPF_OOM
{
    /// <summary>
    /// Interaction logic for ContactEditWindow.xaml
    /// </summary>
    public partial class ContactEditWindow : Window
    {
        private Contact contact;
        private bool newContact;
        public ContactEditWindow(Contact c, bool NewContact)
        {
            newContact = NewContact;
            InitializeComponent();
            contact = c;     
            this.Visibility = Visibility.Visible;
            ContactGrid.DataContext = c;
            if (newContact)
            {
                this.Title = "New contact";
            }
            
        }

        private void AcceptButtonClick(object sender, RoutedEventArgs e)
        {
            if (!(string.IsNullOrWhiteSpace(FnameBox.Text) && string.IsNullOrWhiteSpace(LnameBox.Text) && string.IsNullOrWhiteSpace(NnameBox.Text)))
            {
                FnameBox.Text = FnameBox.Text.Trim();
                NnameBox.Text = NnameBox.Text.Trim();
                LnameBox.Text = LnameBox.Text.Trim();
                BindingExpression be1 = FnameBox.GetBindingExpression(TextBox.TextProperty);
                BindingExpression be2 = NnameBox.GetBindingExpression(TextBox.TextProperty);
                BindingExpression be3 = LnameBox.GetBindingExpression(TextBox.TextProperty);
                be1.UpdateSource();
                be2.UpdateSource();
                be3.UpdateSource();
                if (newContact)
                {
                    MainWindow.ContactList.Add(contact);
                    MainWindow.conversations.Add(new Conversation(contact));
                }

                this.Close();
            }
            else
            {
                ErrorLabel.Foreground = Brushes.Red;
                ErrorLabel.Content = "Error: Enter a name.";
            }
            
            
        }

        private void CancelButtonClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}