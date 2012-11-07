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
    public partial class LightSourceSettingForm : Form
    {
        private Command command;

        public LightSourceSettingForm(Command command)
        {
            this.command = command;
            InitializeComponent();
        }

        private void LightSourceSettingForm_Load(object sender, EventArgs e)
        {
            dataGridViewLightSourceSetting.Rows.Add(-20, 5, -20, 200000, 100);
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridViewLightSourceSetting.Rows)
            {
                float posX = Convert.ToSingle(row.Cells[0].Value);
                float posY = Convert.ToSingle(row.Cells[1].Value);
                float posZ = Convert.ToSingle(row.Cells[2].Value);
                uint photons = Convert.ToUInt32(row.Cells[3].Value);
                float velocity = Convert.ToSingle(row.Cells[4].Value);

                command.setLightSourceSetting(posX, posY, posZ, photons, velocity);
            }
            Hide();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Hide();
        }

        private void LightSourceSettingForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        private void dataGridViewLightSourceSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
