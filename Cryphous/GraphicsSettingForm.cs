using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;

namespace Cryphous
{
    public partial class GraphicsSettingForm : Form
    {
        private Command command;

        public int PointSize
        {
            get { return (int)numericUpDownPointSize.Value; }
        }

        public int PointAlpha
        {
            get { return (int)numericUpDownPointAlpha.Value; }
        }

        public int LineSize
        {
            get { return (int)numericUpDownLineSize.Value; }
        }

        public int LineAlpha
        {
            get { return (int)numericUpDownLineAlpha.Value; }
        }

        public GraphicsSettingForm(Command command)
        {
            this.command = command;
            InitializeComponent();
        }

        private void numericUpDownPointSize_ValueChanged(object sender, EventArgs e)
        {
            setSetting();
        }

        private void numericUpDownPointAlpha_ValueChanged(object sender, EventArgs e)
        {
            setSetting();
        }

        private void numericUpDownLineSize_ValueChanged(object sender, EventArgs e)
        {
            setSetting();
        }

        private void numericUpDownLineAlpha_ValueChanged(object sender, EventArgs e)
        {
            setSetting();
        }

        private void setSetting()
        {
            command.setGraphicsSetting(PointSize, PointAlpha, LineSize, LineAlpha);
        }

    }
}
