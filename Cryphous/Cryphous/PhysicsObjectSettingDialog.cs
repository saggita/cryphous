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
            command.setView(dataGridViewObjectSetting);
            bsCommand.displayBoundarySetting(dataGridView1);
            ssCommand.setTextBox(textBoxTimeStep, textBoxEffectLength);
        }

        private void dataGridViewObjectSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            dataGridViewObjectSetting.Rows.Add( "Fluid", 10000.0, 2.0, 1000.0, -0.1, 0.1, 0.0, 0.5, -0.1, 0.1 );
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            DataGridViewRow row = dataGridViewObjectSetting.CurrentRow;
            if( row != null ) {
                dataGridViewObjectSetting.Rows.Remove(row);
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            bsCommand.saveBoundarySetting(dataGridView1);
            ssCommand.save();

            List<ManagedPosition> positions = new List<ManagedPosition>();

            double length = Crystal.Command.ApplicationSettings.get().getParticleDiameter();// 0.01;
            double margin = 1.0e-12;

            double radius = 0.25;
            
            double minX = -radius + length * 0.5 - margin;
            double maxX = radius - length * 0.5 + margin;
            double minY = 0.0 + length * 0.5 - margin;
            double maxY = radius * 2.0 - length * 0.5 + margin;
            double minZ = -radius + length * 0.5 - margin;
            double maxZ = radius - length * 0.5 + margin;

            double centerX = (minX + maxX) * 0.5;
            double centerY = (minY + maxY) * 0.5;
            double centerZ = (minZ + maxZ) * 0.5;

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

        	foreach( DataGridViewRow row in dataGridViewObjectSetting.Rows ) {
                double pressureCoe = Convert.ToDouble( row.Cells[1].Value );
                double viscosityCoe = Convert.ToDouble( row.Cells[2].Value );
                double density = Convert.ToDouble( row.Cells[3].Value );
                String str = row.Cells[0].Value.ToString();
                command.saveSettings(str, density, pressureCoe, viscosityCoe, positions);
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
    }
}
