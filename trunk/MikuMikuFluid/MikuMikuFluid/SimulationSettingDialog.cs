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
    public partial class SimulationSettingDialog : Form
    {
        private ObjectSettingCommand command;
        private BoundarySettingCommand bsCommand;
        private SimulationSettingCommand ssCommand;
        List<double[]> initialPositions;
        
        public SimulationSettingDialog(ObjectSettingCommand command, BoundarySettingCommand bsCommand, SimulationSettingCommand ssCommand, List<double[]> initialPositions)
        {
            InitializeComponent();
            this.command = command;
            this.bsCommand = bsCommand;
            this.ssCommand = ssCommand;
            this.initialPositions = initialPositions;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void PhysicsObjectSettingDialog_Load(object sender, EventArgs e)
        {
            bsCommand.displayBoundarySetting(dataGridView1);
            ssCommand.setTextBox(textBoxTimeStep, textBoxEffectLength);

            textBoxEffectLength.Text = (0.5).ToString();   
            buttonAdd_Click(sender, e);
        }

        private void dataGridViewObjectSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -1.0, 1.0, 0.0, 1.0, -1.0, 1.0, "Box");
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            foreach(DataGridViewRow row in dataGridViewObjectSetting.SelectedRows ) {
                dataGridViewObjectSetting.Rows.Remove( row );
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            bsCommand.saveBoundarySetting(dataGridView1);
            ssCommand.save();
            command.refresh();

            System.Diagnostics.Debug.Assert( dataGridViewObjectSetting.Rows.Count == 1);
            foreach (DataGridViewRow row in dataGridViewObjectSetting.Rows)
            {
                command.saveSettings(row.Cells[0].Value.ToString(), Convert.ToDouble(row.Cells[3].Value), Convert.ToDouble(row.Cells[1].Value), Convert.ToDouble(row.Cells[2].Value), initialPositions);
            }
            
            Hide();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Hide();
        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void PhysicsObjectSettingDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        private void setBoundary(double minX, double maxX, double minY, double maxY, double minZ, double maxZ)
        {
            dataGridView1.Rows[0].Cells[0].Value = minX;
            dataGridView1.Rows[0].Cells[1].Value = minY;
            dataGridView1.Rows[0].Cells[2].Value = minZ;
            dataGridView1.Rows[1].Cells[0].Value = maxX;
            dataGridView1.Rows[1].Cells[1].Value = maxY;
            dataGridView1.Rows[1].Cells[2].Value = maxZ;
        }
    }
}
