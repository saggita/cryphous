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
            dataGridViewLightSourceSetting.Rows.Add(0, 5, 0, 0, -1, 0);
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridViewLightSourceSetting.Rows)
            {
                float posX = Convert.ToSingle(row.Cells[0].Value);
                float posY = Convert.ToSingle(row.Cells[1].Value);
                float posZ = Convert.ToSingle(row.Cells[2].Value);
                float dirX = Convert.ToSingle(row.Cells[3].Value);
                float dirY = Convert.ToSingle(row.Cells[4].Value);
                float dirZ = Convert.ToSingle(row.Cells[5].Value);
                command.setLightSourceSetting(posX, posY, posZ, dirX, dirY, dirZ);
            }
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
