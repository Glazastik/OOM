

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace WebBrowserApp
{
 
    public partial class MainWindow : Window
    {
        private String token;
        public MainWindow()
        {
            InitializeComponent();
            webBrowser1.Navigate("https://www.facebook.com/dialog/oauth?client_id=355530074619140&display=popup&response_type=token&&redirect_uri=https://www.facebook.com/connect/login_success.html");
            
        }

         private void wbSample_Navigating(object sender, System.Windows.Navigation.NavigatingCancelEventArgs e)
                {
                        token = e.Uri.OriginalString;
                        webSiteAdr.Text = e.Uri.OriginalString;
                }

         private String sortToken(String url)
         {
             /*TODO: Sort url such that only token is left! find access_token=xxxxxx&expiresin... and cut out xxxxxxxx*/
             String s = url;
             

             return s;
         }
    
        private void downloadButtonClick(object sender, RoutedEventArgs e)
        {

        }

      

        private void helpButtonClick(object sender, RoutedEventArgs e)
        {
           
            webBrowser1.Navigate("https://www.facebook.com/dialog/oauth?client_id=355530074619140&display=popup&response_type=token&&redirect_uri=https://www.facebook.com/connect/login_success.html");
        }

        private void mouseEnterEvent(object sender, MouseEventArgs e)
        {
            Button b = (Button)sender;
            if (b.Width == 75)
            {
                b.Margin = new Thickness(b.Margin.Left - 4, b.Margin.Top - 1, b.Margin.Right, b.Margin.Bottom);
                b.Height += 3;
                b.Width += 8;
                b.FontSize += 2;
            }
        }

        private void mouseLeaveEvent(object sender, MouseEventArgs e)
        {
            Button b = (Button)sender;
            if (b.Width == 83)
            {
                b.Margin = new Thickness(b.Margin.Left + 4, b.Margin.Top + 1, b.Margin.Right, b.Margin.Bottom);
                b.Height -= 3;
                b.Width -= 8;
                b.FontSize -= 2;
            }
        }

        private void webBrowser1_Navigated_1(object sender, NavigationEventArgs e)
        {

        }
    }
}
