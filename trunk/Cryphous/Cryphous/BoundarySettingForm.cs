using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;

namespace Cryphous
{
    public partial class BoundarySettingForm : Form
    {
        private BoundarySettingCommand command;

        public BoundarySettingForm(BoundarySettingCommand command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void BoundarySettingForm_Load(object sender, EventArgs e)
        {
            command.displayBoundarySetting(dataGridView1);
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
    }
}
