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
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void BoundarySettingForm_Load(object sender, EventArgs e)
        {
            command.displayBoundarySetting(dataGridView1);
        }
    }
}
