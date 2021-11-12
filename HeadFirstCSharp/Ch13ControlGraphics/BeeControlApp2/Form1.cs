using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BeeControlApp2 {

public partial class Form1 : Form {
    public Form1() {
        InitializeComponent();
    }

    BeeControl control = null;
    private void button1_Click(object sender, EventArgs e) {
        if (control == null) {
            // object initializer 初始化列表发生对象实例化之后
            control = new BeeControl() {
                Location = new Point(100, 100)
            };
            // 加入到 Controls collection 之后会立即显示
            Controls.Add(control);
        }
        else {
            // 使用 using 保证销毁 control 资源 (IDisposable)
            using (control) {
                Controls.Remove(control);
            }
            control = null;
        }
    }
}

}
