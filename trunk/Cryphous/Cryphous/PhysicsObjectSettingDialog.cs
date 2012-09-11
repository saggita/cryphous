using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;

namespace Cryphous
{
    public partial class PhysicsObjectSettingDialog : Form
    {
        private Command command;
        private Random rand = new Random();
        private List<float[]> initialPositions;
        private List<Emitter> emitters;

        public List<Emitter> Emitters
        {
            get { return emitters; }
        }
        
        public PhysicsObjectSettingDialog(Command command, List<float[]> initialPositions)
        {
            InitializeComponent();
            this.emitters = new List<Emitter>();
            this.command = command;
            this.initialPositions = initialPositions;
            dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -10.0, 0.0, 0.0, 10.0, -10.0, 0.0, "Box");

            dataGridViewEmitterSetting.Rows.Add(200000.0, 100.0, 1000.0, 5.0, 5.0, 5.0, 1.0, 1.0, 1.0);
        }

        private void PhysicsObjectSettingDialog_Load(object sender, EventArgs e)
        {
            command.displayBoundarySetting(dataGridView1);
            command.displaySimulationSetting(textBoxTimeStep, textBoxEffectLength);

            textBoxEffectLength.Text = "0.5";
            setBoundary(-20.0F, 20.0F, 0.0F, 100.0F, -20.0F, 20.0F);
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -10.0, 10.0, 0.0, 10.0, -10.0, 10.0, "Box");
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            foreach(DataGridViewRow row in dataGridViewObjectSetting.SelectedRows ) {
                dataGridViewObjectSetting.Rows.Remove( row );
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            command.saveBoundarySetting(dataGridView1);
            command.setSimulationSetting(textBoxTimeStep, textBoxEffectLength);
            command.clearConditions();
            command.refresh();

            foreach (DataGridViewRow row in dataGridViewObjectSetting.Rows)
            {
                float minX = Convert.ToSingle(row.Cells[4].Value);
                float maxX = Convert.ToSingle(row.Cells[5].Value);
                float minY = Convert.ToSingle(row.Cells[6].Value);
                float maxY = Convert.ToSingle(row.Cells[7].Value);
                float minZ = Convert.ToSingle(row.Cells[8].Value);
                float maxZ = Convert.ToSingle(row.Cells[9].Value);
                String shape = row.Cells[10].Value.ToString();
                List<float[]> positions = new List<float[]>();
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

                command.createPhysicsObject(row.Cells[0].Value.ToString(), Convert.ToSingle(row.Cells[3].Value), Convert.ToSingle(row.Cells[1].Value), Convert.ToSingle(row.Cells[2].Value), positions);
            }

            emitters.Clear();
            foreach (DataGridViewRow row in dataGridViewEmitterSetting.Rows)
            {
                uint id = command.createPhysicsObject("Fluid", Convert.ToSingle(row.Cells[2].Value), Convert.ToSingle(row.Cells[0].Value), Convert.ToSingle(row.Cells[1].Value), new List<float[]>());
                Emitter emitter = new Emitter();
                emitter.id = id;
                emitter.center[0] = Convert.ToSingle(row.Cells[3].Value);
                emitter.center[1] = Convert.ToSingle(row.Cells[4].Value);
                emitter.center[2] = Convert.ToSingle(row.Cells[5].Value);
                emitter.velocity[0] = Convert.ToSingle(row.Cells[6].Value);
                emitter.velocity[1] = Convert.ToSingle(row.Cells[7].Value);
                emitter.velocity[2] = Convert.ToSingle(row.Cells[8].Value);
                emitters.Add(emitter);
            }

            if (initialPositions != null)
            {
                command.createPhysicsObject("Obstacle", 10000.0f, 2000000.0f, 1000.0f, initialPositions);
            }

            command.refresh();
            
            Hide();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Hide();
        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }

        private List<float[]> createPositions(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, bool isSphere)
        {
            List<float[]> positions = new List<float[]>();

            float length = float.Parse(textBoxEffectLength.Text);
            float margin = 1.0e-12F;

            minX = minX + length * 0.5F - margin;
            maxX = maxX - length * 0.5F + margin;
            minY = minY + length * 0.5F - margin;
            maxY = maxY - length * 0.5F + margin;
            minZ = minZ + length * 0.5F - margin;
            maxZ = maxZ - length * 0.5F + margin;

            float centerX = (minX + maxX) * 0.5F;
            float centerY = (minY + maxY) * 0.5F;
            float centerZ = (minZ + maxZ) * 0.5F;

            float radius = Math.Min(Math.Min(centerX - minX, centerY - minY), centerZ - minZ);

            for (float x = minX; x < maxX; x += length)
            {
                for (float y = minY; y < maxY; y += length)
                {
                    for (float z = minZ; z < maxZ; z += length)
                    {
                        if( isSphere && ( Math.Pow(x - centerX, 2.0) + Math.Pow(y - centerY, 2.0) + Math.Pow(z - centerZ, 2.0) > Math.Pow( radius, 2.0) ) ) 
                        {
                            continue;
                        }
                        float[] position = new float[3];
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

        private void setBoundary(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
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
            dataGridViewEmitterSetting.Rows.Clear();
            if (comboBoxExample.Text == "DamBreak1")
            {
                setBoundary(-20.0F, 20.0F, 0.0F, 100.0F, -20.0F, 20.0F);
                dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -10.0, -2.0, 0.0, 10.0, -10.0, 10.0, "Box");
            }
            else if (comboBoxExample.Text == "DamBreak2")
            {
                setBoundary(-20.0F, 20.0F, 0.0F, 100.0F, -20.0F, 20.0F);
                dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -10.0, 0.0, 0.0, 10.0, -10.0, 0.0, "Box");
                dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, 0.0, 10.0, 0.0, 10.0, 0.0, 10.0, "Box"); 
            }
            else if (comboBoxExample.Text == "DamDrop")
            {
                setBoundary(-20.0F, 20.0F, 0.0F, 100.0F, -20.0F, 20.0F);
                dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -5.0, 5.0, 20.0, 60.0, -5.0, 5.0, "Box");
            }
            else if (comboBoxExample.Text == "Spring")
            {
                setBoundary(-11.0F, 11.0F, 0.0F, 100.0F, -11.0F, 11.0F);
                dataGridViewEmitterSetting.Rows.Add(20000.0, 200.0, 1000.0, 10.0, 1.0, 10.0, -10.0, 10.0, -10.0);
                dataGridViewEmitterSetting.Rows.Add(20000.0, 200.0, 1000.0, 10.0, 1.0, -10.0, -10.0, 10.0, 10.0);
                dataGridViewEmitterSetting.Rows.Add(20000.0, 200.0, 1000.0, -10.0, 1.0, 10.0, 10.0, 10.0, -10.0);
                dataGridViewEmitterSetting.Rows.Add(20000.0, 200.0, 1000.0, -10.0, 1.0, -10.0, 10.0, 10.0, 10.0);
            }
            else if (comboBoxExample.Text == "SphereBreak")
            {
                setBoundary(-20.0F, 20.0F, 0.0F, 100.0F, -20.0F, 20.0F);
                dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, -15.0, 0.0, 25.0, 40.0, -15.0, 0.0, "Sphere");
                dataGridViewObjectSetting.Rows.Add("Fluid", 200000.0, 100.0, 1000.0, 0.0, 15.0, 30.0, 45.0, 0.0, 15.0, "Sphere");
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
