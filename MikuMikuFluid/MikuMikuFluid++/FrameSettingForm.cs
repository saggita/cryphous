using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MikuMikuFluid
{
    public partial class FrameSettingForm : Form
    {
        public FrameSettingForm()
        {
            InitializeComponent();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            if (StartFrame >= EndFrame)
            {
                MessageBox.Show("Invalid Input: StartFrame > EndFrame");
                return;
            }
            DialogResult = System.Windows.Forms.DialogResult.OK;
            Hide();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
            Hide();
        }

        public long StartFrame
        {
            get { return (long)startUpDown.Value; }
        }

        public long EndFrame
        {
            get { return (long)endUpDown.Value; }
        }

        public long KeyFrameInterval
        {
            get { return (long)keyFrameIntervalUpDown.Value; }
        }

        public long SimulationIterval
        {
            get { return (long)simulationIntervalUpDown.Value; }
        }
    }
}
