using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;
using Cryphous;

namespace MikuMikuFluid
{
    public partial class MMFForm : Form
    {
        private BoundarySettingCommand boundarySettingCommand;
        private ObjectSettingCommand objectSettingCommand;
        private ProfileInfoCommand profileInfoCommand;
        private ParticleInfoCommand particleInfoCommand;
        private SimulationSettingCommand simulationSettingCommand;
        private MainCommand mainCommand;
        private Point previousPoint;
        private bool isLeftDown;
        private bool isRightDown;
        Main main;
        GraphicsSettingForm gsForm;
        SimulationSettingDialog osForm;
                    
        public MMFForm(Main main)
        {
            InitializeComponent();
            this.pictureBox1.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseWheel);
            this.main = main;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            ApplicationSettings.get();
            boundarySettingCommand = new BoundarySettingCommand();
            objectSettingCommand = new ObjectSettingCommand();
            profileInfoCommand = new ProfileInfoCommand();
            particleInfoCommand = new ParticleInfoCommand();
            simulationSettingCommand = new SimulationSettingCommand();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            mainCommand = new MainCommand(pictureBox1, "MikuMikuFluid 1.2");
            gsForm = new GraphicsSettingForm(mainCommand);
            osForm = new SimulationSettingDialog(objectSettingCommand, boundarySettingCommand, simulationSettingCommand, main.InitialPositions);
            objectSettingToolStripMenuItem_Click(sender, e);
        }

        private void objectSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            osForm.ShowDialog();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            timerSimulation.Enabled = !timerSimulation.Enabled;
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            main.initKeyFrame();
            mainCommand.refreshSimulation();
            mainCommand.displayInformation(listBoxInformation);
        }

        private void toolStripMenuItemClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void buttonNextStep_Click(object sender, EventArgs e)
        {
            timerSimulation_Tick(sender, e);
        }

        private void particleInfoPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ParticleObserveDialog poDialog = new ParticleObserveDialog(particleInfoCommand);
            poDialog.ShowDialog();
        }

        private void timerSimulation_Tick(object sender, EventArgs e)
        {
            mainCommand.proceedSimulation();
            mainCommand.displayInformation(listBoxInformation);
            List<List<float[]>> managed = mainCommand.getSimulationCommand().getManagedParticles();
            main.BakeToTimeLine(mainCommand.getSimulationCommand().getStep(), managed);
        }

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.D:
                    mainCommand.zoom(0.1F);
                    break;
                case Keys.Z:
                    mainCommand.zoom(-0.1F);
                    break;
            }
        }

        private void buttonViewReset_Click(object sender, EventArgs e)
        {
            mainCommand.viewReset();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                previousPoint = e.Location;
                isLeftDown = true;
            }
            if (e.Button == MouseButtons.Right)
            {
                previousPoint = e.Location;
                isRightDown = true;
            }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (isLeftDown && (e.Button == MouseButtons.Left))
            {
                float diffX = -(previousPoint.X - e.Location.X) / 100.0F;
                float diffY = -(previousPoint.Y - e.Location.Y) / 100.0F;
                mainCommand.move(diffX, diffY);
                previousPoint = e.Location;
            }
            else if (isRightDown && (e.Button == MouseButtons.Right))
            {
                int angleY = -(previousPoint.X - e.Location.X);
                int angleX = -(previousPoint.Y - e.Location.Y);
                mainCommand.rotateX(angleX);
                mainCommand.rotateY(angleY);
                previousPoint = e.Location;
            }
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            isLeftDown = false;
            isRightDown = false;
        }

        private void pictureBox1_MouseWheel(object sender, MouseEventArgs e)
        {
            float zoom = -e.Delta / 120.0F;
            mainCommand.zoom(zoom);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pictureBox1.Focus();
        }

        private void graphicsSettingGToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gsForm.Show();
        }

        private void buttonParticleInfo_Click(object sender, EventArgs e)
        {
            ParticleObserveDialog poDialog = new ParticleObserveDialog(particleInfoCommand);
            poDialog.Show();            
        }
    }
}
