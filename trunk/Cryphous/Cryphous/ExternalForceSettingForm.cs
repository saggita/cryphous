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
    public partial class ExternalForceSettingForm : Form
    {
        private Command command;

        public float X
        {
            get { return (float)numericUpDownX.Value; }
        }

        public float Y
        {
            get { return (float)numericUpDownY.Value; }
        }

        public float Z
        {
            get { return (float)numericUpDownZ.Value; }
        }


        public ExternalForceSettingForm(Command command)
        {
            this.command = command;
            InitializeComponent();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            command.setExternalForce(X, Y, Z);
        }

        private void numericUpDownY_ValueChanged(object sender, EventArgs e)
        {
            command.setExternalForce(X, Y, Z);
        }

        private void numericUpDownZ_ValueChanged(object sender, EventArgs e)
        {
            command.setExternalForce(X, Y, Z);
        }
    }
}
