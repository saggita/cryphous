using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;

//using ManagedPosition = System.Collections.Generic.List<double>;

namespace Cryphous
{
    public partial class PhysicsObjectSettingDialog : Form
    {
        private ObjectSettingCommand command;
        private BoundarySettingCommand bsCommand;
        private SimulationSettingCommand ssCommand;
        private Random rand = new Random();
        
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
            foreach(DataGridViewRow row in dataGridViewObjectSetting.SelectedRows ) {
                dataGridViewObjectSetting.Rows.Remove( row );
            }
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
                List<double[]> positions = new List<double[]>();
                if (shape == "Box")
                {
                    positions = createPositions(minX, maxX, minY, maxY, minZ, maxZ, false);
                }
                else if (shape == "Sphere")
                {
                    positions = createPositions(minX, maxX, minY, maxY, minZ, maxZ, true);
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

        private List<double[]> createPositions(double minX, double maxX, double minY, double maxY, double minZ, double maxZ, bool isSphere)
        {
            List<double[]> positions = new List<double[]>();

            double length = double.Parse(textBoxEffectLength.Text);
            double margin = 1.0e-12;

            minX = minX + length * 0.5 - margin;
            maxX = maxX - length * 0.5 + margin;
            minY = minY + length * 0.5 - margin;
            maxY = maxY - length * 0.5 + margin;
            minZ = minZ + length * 0.5 - margin;
            maxZ = maxZ - length * 0.5 + margin;

            double centerX = (minX + maxX) * 0.5;
            double centerY = (minY + maxY) * 0.5;
            double centerZ = (minZ + maxZ) * 0.5;

            double radius = Math.Min(Math.Min(centerX - minX, centerY - minY), centerZ - minZ);

            for (double x = minX; x < maxX; x += length)
            {
                for (double y = minY; y < maxY; y += length)
                {
                    for (double z = minZ; z < maxZ; z += length)
                    {
                        if( isSphere && ( Math.Pow(x - centerX, 2.0) + Math.Pow(y - centerY, 2.0) + Math.Pow(z - centerZ, 2.0) > Math.Pow( radius, 2.0) ) ) 
                        {
                            continue;
                        }
                        double[] position = new double[3];// ManagedPosition();
                        position[0] = x;
                        position[1] = y;
                        position[2] = z;
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

        private void setBoundary(double minX, double maxX, double minY, double maxY, double minZ, double maxZ)
        {
            dataGridView1.Rows[0].Cells[0].Value = minX;
            dataGridView1.Rows[0].Cells[1].Value = minY;
            dataGridView1.Rows[0].Cells[2].Value = minZ;
            dataGridView1.Rows[1].Cells[0].Value = maxX;
            dataGridView1.Rows[1].Cells[1].Value = maxY;
            dataGridView1.Rows[1].Cells[2].Value = maxZ;
        }

        private void comboBoxExample_SelectedIndexChanged(object sender, EventArgs e)
        {
            dataGridViewObjectSetting.Rows.Clear();
            if (comboBoxExample.Text == "DamBreak1")
            {
                setBoundary(-5.0, 5.0, 0.0, 100.0, -5.0, 5.0);
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -5.0, 0.0, 0.0, 2.0, -2.0, 2.0, "Box");
            }
            else if (comboBoxExample.Text == "DamBreak2")
            {
                setBoundary(-5.0, 5.0, 0.0, 100.0, -5.0, 5.0);
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -5.0, -1.0, 0.0, 2.0, -5.0, -1.0, "Box");
                dataGridViewObjectSetting.Rows.Add("Fluid", 20000.0, 4.0, 200.0, 1.0, 5.0, 0.0, 2.0, 1.0, 5.0, "Box"); 
            }
            else if (comboBoxExample.Text == "Rain")
            {
                setBoundary(-100.0, 100.0, 0.0, 100.0, -100.0, 100.0);
                for (int i = 0; i < 30; ++i)
                {
                    double radius = 2.0;
                    double minX = rand.NextDouble() * 20 - 10;
                    double minY = rand.NextDouble() * 10;
                    double minZ = rand.NextDouble() * 20 - 10;

                    dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 100.0, 1000.0, minX, minX + radius, minY, minY + radius, minZ, minZ + radius, "Sphere");
                }
            }
            else if (comboBoxExample.Text == "Crown")
            {
                setBoundary(-5.0, 5.0, 0.0, 100.0, -5.0, 5.0);
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -5.0, 5.0, 0.0, 1.0, -5.0, 5.0, "Box");
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -1.0, 1.0, 8.0, 10.0, -1.0, 1.0, "Sphere");
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -5.0, -3.0, 6.0, 8.0, -5.0, -3.0, "Sphere");
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, 3.0, 5.0, 6.0, 8.0, 3.0, 5.0, "Sphere");
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -5.0, -3.0, 6.0, 8.0, 3.0, 5.0, "Sphere");
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, 3.0, 5.0, 6.0, 8.0, -5.0, -3.0, "Sphere");
            }
            else if (comboBoxExample.Text == "Wall")
            {
                setBoundary(-10.0, 10.0, 0.0, 100.0, -2.0, 2.0);
                dataGridViewObjectSetting.Rows.Add("Fluid", 100000.0, 20.0, 1000.0, -5.0, 0.0, 0.0, 2.0, -2.0, 2.0, "Box");
                dataGridViewObjectSetting.Rows.Add("Rigid", 100000.0, 20.0, 1000.0, 2.0, 3.0, 0.0, 1.0, -2.0, 2.0, "Box");
                dataGridViewObjectSetting.Rows.Add("Rigid", 100000.0, 20.0, 1000.0, -8.0, -7.0, 0.0, 2.0, -2.0, 2.0, "Box");
            }
            else
            {
                System.Diagnostics.Debug.Assert(false);
            }
        }

        private void buttonCopy_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridViewObjectSetting.SelectedRows)
            {
                dataGridViewObjectSetting.Rows.Add( row.Cells[0].Value, row.Cells[1].Value, row.Cells[2].Value, row.Cells[3].Value, row.Cells[4].Value,
                    row.Cells[5].Value, row.Cells[6].Value, row.Cells[7].Value, row.Cells[8].Value, row.Cells[9].Value, row.Cells[10].Value);
            }
        }
    }
}
