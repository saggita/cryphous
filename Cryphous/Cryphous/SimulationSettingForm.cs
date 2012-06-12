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
    public partial class SimulationSettingForm : Form
    {
        private SimulationSettingCommand command;
        public SimulationSettingForm(SimulationSettingCommand command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            command.save();
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void SimulationSettingForm_Load(object sender, EventArgs e)
        {
            command.setTextBox(textBoxTimeStep, textBoxEffectLength);
        }
    }
}
