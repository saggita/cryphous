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
        public PhysicsObjectSettingDialog(ObjectSettingCommand command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void PhysicsObjectSettingDialog_Load(object sender, EventArgs e)
        {
            command.setView(dataGridViewObjectSetting);
            command.displaySettings();
        }

        private void dataGridViewObjectSetting_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            command.addObject();
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            command.deleteObject();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            List<ManagedPosition> positions = new List<ManagedPosition>();

            const double length = 0.01;
            const double margin = 1.0e-12;

            const double radius = 0.25;
            
            const double minX = -radius + length * 0.5 - margin;
            const double maxX = radius - length * 0.5 + margin;
            const double minY = 0.0 + length * 0.5 - margin;
            const double maxY = radius * 2.0 - length * 0.5 + margin;
            const double minZ = -radius + length * 0.5 - margin;
            const double maxZ = radius - length * 0.5 + margin;

            const double centerX = (minX + maxX) * 0.5;
            const double centerY = (minY + maxY) * 0.5;
            const double centerZ = (minZ + maxZ) * 0.5;

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

            double pressureCoe = 0.0;
            double viscosityCoe = 0.0;
            double density = 0.0;
        	foreach( DataGridViewRow row in dataGridViewObjectSetting.Rows ) {
                pressureCoe = Convert.ToDouble( row.Cells[1].Value );
                viscosityCoe = Convert.ToDouble( row.Cells[2].Value );
                density = Convert.ToDouble( row.Cells[3].Value );
            }
            command.saveSettings(density, pressureCoe, viscosityCoe, positions);
            
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
