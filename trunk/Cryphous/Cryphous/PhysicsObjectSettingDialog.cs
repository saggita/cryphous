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
    public partial class PhysicsObjectSettingDialog : Form
    {
        private ObjectSettingCommand command;
        public PhysicsObjectSettingDialog(ObjectSettingCommand command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void PhysicsObjectSettingDialog_Load(object sender, EventArgs e)
        {
            command.setView(dataGridViewObjectSetting);
            command.displaySettings();
        }

        private void dataGridViewObjectSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            command.addObject();
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            command.deleteObject();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            command.saveSettings();
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
