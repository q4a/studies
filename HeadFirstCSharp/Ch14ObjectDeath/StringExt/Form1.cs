using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MyExtensions;

namespace StringExt
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string message = "Clones are wreaking havoc at the factory. Help!";
            if (message.IsDistressCall())
                MessageBox.Show("Is Distress Call");
            else
                MessageBox.Show("Is Not Distress Call");
        }
    }
}
