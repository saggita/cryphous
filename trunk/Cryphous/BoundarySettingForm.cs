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
    public partial class BoundarySettingForm : Form
    {
        private Command command;

        public BoundarySettingForm(Command command)
        {
            this.command = command;
            InitializeComponent();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            command.saveBoundarySetting(dataGridView1);
            Hide();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Hide();
        }

        private void BoundarySettingForm_Load(object sender, EventArgs e)
        {
            command.displayBoundarySetting(dataGridView1);
        }

        private void BoundarySettingForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }
    }
}
