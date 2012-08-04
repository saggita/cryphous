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
        
        public MainForm()
        {
            InitializeComponent();
            this.pictureBox1.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseWheel);   
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
            mainCommand = new MainCommand(pictureBox1, "Cryphous 1.2");

            osDialog = new PhysicsObjectSettingDialog(objectSettingCommand, boundarySettingCommand, simulationSettingCommand);
            gsDialog = new GraphicsSettingForm(mainCommand);
        }

        private void objectSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            osDialog.ShowDialog();
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
            mainCommand.proceedSimulation();
            mainCommand.displayInformation(listBoxInformation);
        }

        private void timerSimulation_Tick(object sender, EventArgs e)
        {
            mainCommand.proceedSimulation();
            mainCommand.displayInformation(listBoxInformation);
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

        private void boneExportBToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<List<float[]>> allParticles = mainCommand.getSimulationCommand().getManagedParticles();

            if (allParticles.Count == 0)
            {
                MessageBox.Show("No particles.");
            }

            SaveFileDialog dialog = new SaveFileDialog();
            dialog.Title = "Bone Export Dialog";
            dialog.FileName = "bones.txt";
            dialog.Filter = "Text File|*.txt|All Files|*.*";

            if (dialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }
            
            int index = 1;
            using (StreamWriter w = new StreamWriter(dialog.FileName))
            {
                foreach (List<float[]> particleGroup in allParticles)
                {
                    foreach (float[] particle in particleGroup)
                    {
                    
                            w.WriteLine("ﾎﾞｰﾝ" + index);
                            w.WriteLine("bone" + index);
                            w.WriteLine("1");
                            w.WriteLine("-");
                            w.WriteLine("-");
                            w.WriteLine("-1");
                            w.WriteLine(particle[0] + "," + particle[1] + "," + particle[2]);
                            w.WriteLine("");

                            ++index;
                        }
                    }
                }
         }
    }
}
