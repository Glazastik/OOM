using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace WPF_OOM
{
    public interface Service
    {
        string Name { get; }
        Image Logo { get; }
    }
    public class Facebook : Service
    {
        public string Name { get; private set; }
        public Image Logo { get; private set; }

        public Facebook()
        {
            Name = "Facebook";
        }
    }
}
