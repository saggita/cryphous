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
        private Command mainCommand;
        private Point previousPoint;
	    private bool isLeftDown;
        private bool isRightDown;

        private PhysicsObjectSettingDialog osDialog;

        private bool isStandAlone;
        List<float[]> simulatedPositions;
        List<float[]> initialPositions;

        public List<float[]> SimulatedPositions
        {
            get{ return simulatedPositions; }
        }

        
        public MainForm(bool isStandAlone, List<float[]> initialPositions = null)
        {
            InitializeComponent();
            this.pictureBox1.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseWheel);
            this.isStandAlone = isStandAlone;
            this.initialPositions = initialPositions;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            mainCommand = new Command( pictureBox1 );

            osDialog = new PhysicsObjectSettingDialog(mainCommand, initialPositions);
        }

        private void objectSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            osDialog.ShowDialog();
            if (!isStandAlone)
            {
                simulatedPositions = mainCommand.getManagedPositions();
            }
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            timerSimulation.Enabled = !timerSimulation.Enabled;
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            foreach (Emitter emitter in osDialog.Emitters)
            {
                emitter.emittedParticles = 0;
            }
            mainCommand.refresh();
            mainCommand.rendering();
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
            if( mainCommand.getStep() % 4 == 0 ) {
                List<Emitter> emitters = osDialog.Emitters;
                foreach (Emitter emitter in emitters)
                {
                    if (emitter.emittedParticles >= emitter.maxParticles)
                    {
                        continue;
                    }
                    emitter.emittedParticles++;
                    List<float[]> positions = new List<float[]>();
                    positions.Add(emitter.center);

                    List<float[]> velocities = new List<float[]>();
                    velocities.Add(emitter.velocity);
                    mainCommand.addParticles(emitter.id, positions, velocities);
                }
            }
            mainCommand.proceed();
            mainCommand.displayProfile( listBoxInformation);
            if (!isStandAlone)
            {
                simulatedPositions = mainCommand.getManagedPositions();
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

        private void buttonRenderingTest_Click(object sender, EventArgs e)
        {
            RenderingForm form = new RenderingForm();
            form.ShowDialog(this);
        }
    }
}
