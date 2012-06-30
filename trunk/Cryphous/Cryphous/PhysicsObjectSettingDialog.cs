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
        private List<ManagedPosition> initialPositions;
        
        public PhysicsObjectSettingDialog(ObjectSettingCommand command, BoundarySettingCommand bsCommand, SimulationSettingCommand ssCommand, bool isSingleMode = false, List<ManagedPosition> initialPositions = null)
        {
            InitializeComponent();
            this.command = command;
            this.bsCommand = bsCommand;
            this.ssCommand = ssCommand;
            this.initialPositions = initialPositions;
            if (isSingleMode)
            {
                this.buttonAdd.Hide();
                this.buttonClear.Hide();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void PhysicsObjectSettingDialog_Load(object sender, EventArgs e)
        {
            command.setView(dataGridViewObjectSetting);
            command.displaySettings();
            bsCommand.displayBoundarySetting(dataGridView1);
            ssCommand.setTextBox(textBoxTimeStep, textBoxEffectLength);
            
            if (dataGridViewObjectSetting.Rows.Count == 0)
            {
                buttonAdd_Click(sender, e);
            }
        }

        private void dataGridViewObjectSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            double pressureCoe = 10000.0;
            double viscosityCoe = 2.0;
            double density = 1000.0;
            String str = "Fluid";
            dataGridViewObjectSetting.Rows.Add(str, pressureCoe, viscosityCoe, density);
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
            Random rand = new Random();

            if (initialPositions == null)
            {
                foreach (DataGridViewRow row in dataGridViewObjectSetting.Rows)
                {
                    double centerX = (rand.NextDouble() - 0.5) * 1.5;
                    double centerY = rand.NextDouble() * 0.5 + 0.2;
                    double centerZ = (rand.NextDouble() - 0.5) * 1.5;
                    List<ManagedPosition> positions = /*(rand.Next() % 2 == 0 ) ? createBox(0.1, centerX, centerY, centerZ) :*/
                        createSphere(0.1, centerX, centerY, centerZ);
                    command.saveSettings(row.Cells[0].Value.ToString(), Convert.ToDouble(row.Cells[3].Value), Convert.ToDouble(row.Cells[1].Value), Convert.ToDouble(row.Cells[2].Value), positions);
                }
            }
            else
            {
                DataGridViewRow row = dataGridViewObjectSetting.Rows[0];
                command.saveSettings(row.Cells[0].Value.ToString(), Convert.ToDouble(row.Cells[3].Value), Convert.ToDouble(row.Cells[1].Value), Convert.ToDouble(row.Cells[2].Value), initialPositions);
            }

            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }

        private List<ManagedPosition> createSphere(double radius, double centerX, double centerY, double centerZ)
        {
            List<ManagedPosition> positions = new List<ManagedPosition>();

            double length = double.Parse( textBoxEffectLength.Text );
            double margin = 1.0e-12;

            double minX = centerX - radius + length * 0.5 - margin;
            double maxX = centerX + radius - length * 0.5 + margin;
            double minY = centerY - radius + length * 0.5 - margin;
            double maxY = centerY + radius - length * 0.5 + margin;
            double minZ = centerZ - radius + length * 0.5 - margin;
            double maxZ = centerZ + radius - length * 0.5 + margin;

            for (double x = minX; x < maxX; x += length)
            {
                for (double y = minY; y < maxY; y += length)
                {
                    for (double z = minZ; z < maxZ; z += length)
                    {
                        if (Math.Pow(centerX - x, 2.0) + Math.Pow(centerY - y, 2.0) + Math.Pow(centerZ - z, 2.0) > radius * radius)
                        {
                            continue;
                        }
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

        private List<ManagedPosition> createBox(double radius, double centerX, double centerY, double centerZ)
        {
            List<ManagedPosition> positions = new List<ManagedPosition>();

            double length = double.Parse(textBoxEffectLength.Text);
            double margin = 1.0e-12;

            double minX = centerX - radius + length * 0.5 - margin;
            double maxX = centerX + radius - length * 0.5 + margin;
            double minY = centerY - radius + length * 0.5 - margin;
            double maxY = centerY + radius - length * 0.5 + margin;
            double minZ = centerZ - radius + length * 0.5 - margin;
            double maxZ = centerZ + radius - length * 0.5 + margin;

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
    }
}
