using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;
//using DxMath;

namespace Cryphous
{
    public partial class MainForm : Form
    {
        private SimulationCommand simulationCommand;
        private BoundarySettingCommand boundarySettingCommand;
        private FileIOCommand fileIOCommand;
        private ObjectSettingCommand objectSettingCommand;
        private ProfileInfoCommand profileInfoCommand;
        private ParticleInfoCommand particleInfoCommand;
        private SimulationSettingCommand simulationSettingCommand;
        //pictureBox1.Image = new Bitmap( pictureBox1.Width, pictureBox1.Height );
        //private MainCommand mainCommand(pictureBox1);
        //private List<Position> positions;
        //private List<Position> moved;
        private MainCommand mainCommand;
        
        public MainForm()
        {
            InitializeComponent();
        }

        /*public void setPositions(List<Position> positions)
        {
            this.positions = positions;
        }

        public List<Position> getMovedPositions()
        {
            return moved;
        }*/

        private void MainForm_Load(object sender, EventArgs e)
        {
            ApplicationSettings.get();
            simulationCommand = new SimulationCommand();
            boundarySettingCommand = new BoundarySettingCommand();
            fileIOCommand = new FileIOCommand();
            objectSettingCommand = new ObjectSettingCommand();
            profileInfoCommand = new ProfileInfoCommand();
            particleInfoCommand = new ParticleInfoCommand();
            simulationSettingCommand = new SimulationSettingCommand();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            mainCommand = new MainCommand(pictureBox1);
        }

        private void boundarySettingBToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BoundarySettingForm boundarySettingForm = new BoundarySettingForm( boundarySettingCommand);
            boundarySettingForm.Show();
        }

        private void toolStripMenuItemOpen_Click(object sender, EventArgs e)
        {
            fileIOCommand.fileOpen();
        }

        private void objectSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PhysicsObjectSettingDialog osDialog = new PhysicsObjectSettingDialog(objectSettingCommand);
            osDialog.Show();
        }

        private void toolStripMenuItemSave_Click(object sender, EventArgs e)
        {
            fileIOCommand.fileSaveOverride();
        }

        private void toolStripMenuItemSaveAs_Click(object sender, EventArgs e)
        {
            fileIOCommand.fileSave();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            //simulationCommand.proceed();
            //profileInfoCommand.display(listBoxInformation);
            timerSimulation.Enabled = !timerSimulation.Enabled;
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            mainCommand.viewReset();
            simulationCommand.refresh();
            simulationCommand.proceed();
            //simulationCommand.addParticles( positions);
        }

        private void toolStripMenuItemClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void buttonNextStep_Click(object sender, EventArgs e)
        {
            mainCommand.proceedSimulation();
        }

        private void simulationSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SimulationSettingForm form = new SimulationSettingForm(simulationSettingCommand);
            form.Show();
        }

        private void particleInfoPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ParticleObserveDialog poDialog = new ParticleObserveDialog(particleInfoCommand);
            poDialog.Show();
        }

        private void timerSimulation_Tick(object sender, EventArgs e)
        {
            mainCommand.proceedSimulation();
            mainCommand.displayInformation(listBoxInformation);
        }
    }
}
