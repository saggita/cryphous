using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;

using ManagedPosition = System.Collections.Generic.List<double>;

namespace Cryphous
{
    public partial class PhysicsObjectSettingDialog : Form
    {
        private ObjectSettingCommand command;
        private BoundarySettingCommand bsCommand;
        private SimulationSettingCommand ssCommand;
        
        public PhysicsObjectSettingDialog(ObjectSettingCommand command, BoundarySettingCommand bsCommand, SimulationSettingCommand ssCommand)
        {
            InitializeComponent();
            this.command = command;
            this.bsCommand = bsCommand;
            this.ssCommand = ssCommand;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void PhysicsObjectSettingDialog_Load(object sender, EventArgs e)
        {
            bsCommand.displayBoundarySetting(dataGridView1);
            ssCommand.setTextBox(textBoxTimeStep, textBoxEffectLength);
            
            buttonAdd_Click(sender, e);
        }

        private void dataGridViewObjectSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -1.0, 1.0, 0.0, 1.0, -1.0, 1.0, "Box");
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            dataGridViewObjectSetting.Rows.Clear();
            command.refresh();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            bsCommand.saveBoundarySetting(dataGridView1);
            ssCommand.save();
            command.refresh();

            foreach (DataGridViewRow row in dataGridViewObjectSetting.Rows)
            {
                double minX = Convert.ToDouble(row.Cells[4].Value);
                double maxX = Convert.ToDouble(row.Cells[5].Value);
                double minY = Convert.ToDouble(row.Cells[6].Value);
                double maxY = Convert.ToDouble(row.Cells[7].Value);
                double minZ = Convert.ToDouble(row.Cells[8].Value);
                double maxZ = Convert.ToDouble(row.Cells[9].Value);
                String shape = row.Cells[10].Value.ToString();
                List<ManagedPosition> positions = new List<ManagedPosition>();
                if (shape == "Box")
                {
                    positions = createPositions(minX, maxX, minY, maxY, minZ, maxZ);
                }
                else if (shape == "Sphere")
                {
                    positions = createPositions(minX, maxX, minY, maxY, minZ, maxZ);
                }
                else
                {
                    System.Diagnostics.Debug.Assert(false);
                }

                command.saveSettings(row.Cells[0].Value.ToString(), Convert.ToDouble(row.Cells[3].Value), Convert.ToDouble(row.Cells[1].Value), Convert.ToDouble(row.Cells[2].Value), positions);
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

        private List<ManagedPosition> createPositions(double minX, double maxX, double minY, double maxY, double minZ, double maxZ )
        {
            List<ManagedPosition> positions = new List<ManagedPosition>();

            double length = double.Parse(textBoxEffectLength.Text);
            double margin = 1.0e-12;

            minX = minX + length * 0.5 - margin;
            maxX = maxX - length * 0.5 + margin;
            minY = minY + length * 0.5 - margin;
            maxY = maxY - length * 0.5 + margin;
            minZ = minZ + length * 0.5 - margin;
            maxZ = maxZ - length * 0.5 + margin;

            for (double x = minX; x < maxX; x += length)
            {
                for (double y = minY; y < maxY; y += length)
                {
                    for (double z = minZ; z < maxZ; z += length)
                    {
                        ManagedPosition position = new ManagedPosition();
                        position.Add(x);
                        position.Add(y);
                        position.Add(z);
                        positions.Add(position);
                    }
                }
            }
            return positions;
        }

        private void PhysicsObjectSettingDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }
    }
}
