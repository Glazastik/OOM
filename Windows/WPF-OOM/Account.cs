using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace WPF_OOM
{
    public class Account
    {
        private int id;
        private int serviceType;
        private string address;
        public string ServiceName { get; private set; }
        public ImageSource Logo { get; private set; }
        public ImageSource OtherLogo { get; private set; }

        public Account(int id, int serviceType, string address)
        {
            switch (serviceType)
            {
                case 0:
                    this.ServiceName = "Google Hangouts";
                    var steamUri = new Uri(@"/WPF-OOM;component/res/steam.png", UriKind.Relative);
                    Logo = new BitmapImage(steamUri);
                    var steamDarkUri = new Uri(@"/WPF-OOM;component/res/steamdark.png", UriKind.Relative);
                    OtherLogo = new BitmapImage(steamDarkUri);
                    break;
                case 1:
                    this.ServiceName = "IRC";
                    var fbUri = new Uri(@"/WPF-OOM;component/res/fb.png", UriKind.Relative);
                    Logo = new BitmapImage(fbUri);
                    var fbDarkUri = new Uri(@"/WPF-OOM;component/res/fbdark.png", UriKind.Relative);
                    OtherLogo = new BitmapImage(fbDarkUri);
                    break;
            }
            this.id = id;
            this.serviceType = serviceType;
            this.address = address;
        }

        public int GetId()
        {
            return id;
        }

        public int GetServiceType()
        {
            return serviceType;
        }

        public string GetAddress()
        {
            return address;
        }

        public class DraftAccount
        {
            //private Account _account;
            public Account Account { get; set; }

            private bool _selected;

            public bool Selected
            {
                get { return _selected; }
                set { _selected = value; }
            }

            public DraftAccount(Account a, bool selected)
            {
                this.Account = a;
                this.Selected = selected;
            }
        }
    }
}
