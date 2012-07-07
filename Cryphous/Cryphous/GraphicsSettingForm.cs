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
    public partial class GraphicsSettingForm : Form
    {
        private MainCommand command;
        public GraphicsSettingForm(MainCommand command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void trackBarAlphaPower_Scroll(object sender, EventArgs e)
        {
            command.getGraphicsSettingCommand().save();
            command.rendering();
        }

        private void trackBarPointSize_Scroll(object sender, EventArgs e)
        {
            command.getGraphicsSettingCommand().save();
            command.rendering();
        }

        private void checkBoxApplyPointSprite_CheckedChanged(object sender, EventArgs e)
        {
            command.getGraphicsSettingCommand().save();
            command.rendering();
        }

        private void checkBoxBoundingBox_CheckedChanged(object sender, EventArgs e)
        {
            command.getGraphicsSettingCommand().save();
            command.rendering();
        }

        private void GraphicsSettingForm_Load(object sender, EventArgs e)
        {
            command.getGraphicsSettingCommand().setTrackBar(
                    trackBarPointSize,
                    trackBarAlphaPower,
                    checkBoxApplyPointSprite,
                    checkBoxBoundingBox);
        }

        private void GraphicsSettingForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }
    }
}
