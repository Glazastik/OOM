using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace WPF_OOM
{
    public interface Service
    {
        string Name { get; }
        ImageSource Logo { get; }
    }
    public class Facebook : Service
    {
        public string Name { get; private set; }
        public ImageSource Logo { get; private set; }

        public Facebook()
        {
            Name = "Facebook";
            BitmapImage bmi = new BitmapImage();
            bmi.BeginInit();
            bmi.UriSource = new Uri(@"../../fb.png", UriKind.Relative);
            bmi.CacheOption = BitmapCacheOption.OnLoad;
            bmi.EndInit();
            Logo = bmi;
        }
        
    }
    public class Steam : Service
    {
        public string Name { get; private set; }
        public ImageSource Logo { get; private set; }

        public Steam()
        {
            Name = "Steam";
            BitmapImage bmi = new BitmapImage();
            bmi.BeginInit();
            bmi.UriSource = new Uri(@"../../steam.png", UriKind.Relative);
            bmi.CacheOption = BitmapCacheOption.OnLoad;
            bmi.EndInit();
            Logo = bmi;

        }
    }
}
