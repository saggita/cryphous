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
        
        public PhysicsObjectSettingDialog(ObjectSettingCommand command, BoundarySettingCommand bsCommand, SimulationSettingCommand ssCommand, List<ManagedPosition> initialPositions = null)
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
            double pressureCoe = 100000.0;
            double viscosityCoe = 20.0;
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

            List<ManagedPosition> newPositions = (initialPositions == null) ? 
                createBox(-2.0, 2.0, 0.0, 2.0, -2.0, 2.0 ) : initialPositions;
            DataGridViewRow row = dataGridViewObjectSetting.Rows[0];
            command.saveSettings(row.Cells[0].Value.ToString(), Convert.ToDouble(row.Cells[3].Value), Convert.ToDouble(row.Cells[1].Value), Convert.ToDouble(row.Cells[2].Value), newPositions);
            
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }

        private List<ManagedPosition> createBox(double minX, double maxX, double minY, double maxY, double minZ, double maxZ )
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
    }
}
