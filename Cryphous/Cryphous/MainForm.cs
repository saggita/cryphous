using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;
using System.IO;

namespace Cryphous
{
    public partial class MainForm : Form
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

        private PhysicsObjectSettingDialog osDialog;
        private GraphicsSettingForm gsDialog;

        private bool isStandAlone;
        List<List<float[]>> simulatedPositions;
        List<List<float[]>> simulatedNormals;

        private int maxParticles;

        public List<List<float[]>> SimulatedPositions
        {
            get{ return simulatedPositions; }
        }

        public List<List<float[]>> SimulatedNormals
        {
            get { return simulatedNormals; }
        }
        
        public MainForm(bool isStandAlone, int maxParticles)
        {
            InitializeComponent();
            this.pictureBox1.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseWheel);
            this.isStandAlone = isStandAlone;
            this.maxParticles = maxParticles;
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
            mainCommand = new MainCommand(pictureBox1, "Cryphous 1.3");

            osDialog = new PhysicsObjectSettingDialog(objectSettingCommand, boundarySettingCommand, simulationSettingCommand, maxParticles);
            gsDialog = new GraphicsSettingForm(mainCommand);
            objectSettingToolStripMenuItem_Click(sender, e);
        }

        private void objectSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            osDialog.ShowDialog();
            if (!isStandAlone)
            {
                simulatedPositions = mainCommand.getSimulationCommand().getManagedPositions();
                simulatedNormals = mainCommand.getSimulationCommand().getManagedNormals();
            }
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            timerSimulation.Enabled = !timerSimulation.Enabled;
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            mainCommand.refreshSimulation();
            mainCommand.displayInformation(listBoxInformation);
        }

        private void toolStripMenuItemClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void buttonNextStep_Click(object sender, EventArgs e)
        {
            proceed();
        }

        private void timerSimulation_Tick(object sender, EventArgs e)
        {
            proceed();
        }

        public void proceed()
        {
            mainCommand.proceedSimulation();
            mainCommand.displayInformation(listBoxInformation);
            if (!isStandAlone)
            {
                simulatedPositions = mainCommand.getSimulationCommand().getManagedPositions();
                simulatedNormals = mainCommand.getSimulationCommand().getManagedNormals();
            }
        }

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            switch( e.KeyCode ) {
	            case Keys.D :
            		mainCommand.zoom(1.0F);
		            break;
            	case Keys.Z :
	               	mainCommand.zoom(-1.0F);
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
                float diffX = -(previousPoint.X - e.Location.X) / 1000.0F;
                float diffY = -(previousPoint.Y - e.Location.Y) / 1000.0F;
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
            float zoom = -e.Delta / 24.0F;
            mainCommand.zoom(zoom);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pictureBox1.Focus();
        }

        private void graphicsSettingGToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gsDialog.Show();
        }

        private void buttonParticleInfo_Click(object sender, EventArgs e)
        {
            ParticleObserveDialog poDialog = new ParticleObserveDialog(particleInfoCommand);
            poDialog.ShowDialog();
        }
    }
}
