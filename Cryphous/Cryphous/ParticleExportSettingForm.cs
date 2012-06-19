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
    public partial class ParticleExportSettingForm : Form
    {
        private ExportSettingCommand command;

        public ParticleExportSettingForm(ExportSettingCommand command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void buttonFileSet_Click(object sender, EventArgs e)
        {
            command.setFileName();
            command.display();
        }

        private void buttonFileReset_Click(object sender, EventArgs e)
        {
            command.resetFileName();
            command.display();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            command.save();
            this.Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ParticleExportSettingForm_Load(object sender, EventArgs e)
        {
            command.setTextBox(this.textBoxOutputInterval, this.textBoxOutputFile);
            command.display();
        }
    }
}
