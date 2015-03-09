using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace WPF_OOM
{
    public interface Service
    {
        string Name { get; }
        ImageSource Logo { get; }
        ImageSource OtherLogo { get; }
    }
    public class Facebook : Service
    {
        public string Name { get; private set; }
        public ImageSource Logo { get; private set; }
        public ImageSource OtherLogo { get; private set; }

        public Facebook()
        {
            Name = "Facebook";

            var fbUri = new Uri(@"/WPF-OOM;component/res/fb.png", UriKind.Relative);
            Logo = new BitmapImage(fbUri);

            var fbDarkUri = new Uri(@"/WPF-OOM;component/res/fbdark.png", UriKind.Relative);
            OtherLogo = new BitmapImage(fbDarkUri);
        }
        
    }
    public class Steam : Service
    {
        public string Name { get; private set; }
        public ImageSource Logo { get; private set; }
        public ImageSource OtherLogo { get; private set; }

        public Steam()
        {
            Name = "Steam";

            var steamUri = new Uri(@"/WPF-OOM;component/res/steam.png", UriKind.Relative);
            Logo = new BitmapImage(steamUri);

            var steamDarkUri = new Uri(@"/WPF-OOM;component/res/steamdark.png", UriKind.Relative);
            OtherLogo = new BitmapImage(steamDarkUri);
        }
    }

    public class DraftService
    {
        private Service _service;
        public Service Service
        {
            get { return _service; }
            private set { _service = value; }
        }

        public bool Selected { get; set; }

        public DraftService(Service s, bool selected)
        {
            this.Service = s;
            this.Selected = selected;
        }
    }

}
