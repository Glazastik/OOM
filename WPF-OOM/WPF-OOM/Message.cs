﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace WPF_OOM
{
    class Message
    {
        public string text { get; private set; }
        public Message(String s)
        {
            text = s;
        }
    }
}
