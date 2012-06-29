﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;
//using DxMath;

//using ManagedPosition = List<double>;

namespace Cryphous
{
    public partial class MainForm : Form
    {
        //private SimulationCommand simulationCommand;
        private BoundarySettingCommand boundarySettingCommand;
        private ObjectSettingCommand objectSettingCommand;
        private ProfileInfoCommand profileInfoCommand;
        private ParticleInfoCommand particleInfoCommand;
        private SimulationSettingCommand simulationSettingCommand;
        private MainCommand mainCommand;
        private Point previousPoint;
	    private bool isLeftDown;
        private bool isRightDown;
        
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
            mainCommand = new MainCommand(pictureBox1);
        }

        private void boundarySettingBToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BoundarySettingForm boundarySettingForm = new BoundarySettingForm( boundarySettingCommand);
            boundarySettingForm.Show();
        }

        private void objectSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PhysicsObjectSettingDialog osDialog = new PhysicsObjectSettingDialog(objectSettingCommand);
            osDialog.Show();
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

        private void simulationSettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SimulationSettingForm form = new SimulationSettingForm(simulationSettingCommand);
            form.Show();
        }

        private void particleInfoPToolStripMenuItem_Click(object sender, EventArgs e)
        {

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
            		mainCommand.zoom(0.1);
		            break;
            	case Keys.Z :
	               	mainCommand.zoom(-0.1);
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
                double diffX = -(previousPoint.X - e.Location.X) / 1000.0;
                double diffY = -(previousPoint.Y - e.Location.Y) / 1000.0;
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
            double zoom = -e.Delta / 240.0;
            mainCommand.zoom(zoom);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pictureBox1.Focus();
        }

        private void graphicsSettingGToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GraphicsSettingForm form = new GraphicsSettingForm(mainCommand);
            form.Show();
        }

        private void buttonParticleInfo_Click(object sender, EventArgs e)
        {
            ParticleObserveDialog poDialog = new ParticleObserveDialog(particleInfoCommand);
            poDialog.Show();
        }

        private void MainForm_DragEnter(object sender, DragEventArgs e)
        {
        }

        private void rainRToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //RainForm form = new RainForm();
            //form.Show();
            /*ParticleMarshaler marshaler = new ParticleMarshaler();
            List<ManagedPosition> positions = new List<ManagedPosition>();
            ManagedPosition newPos = new ManagedPosition();
            newPos.Add(0.0);
            newPos.Add(0.0);
            newPos.Add(0.0);
            positions.Add(newPos);*/
        }
    }
}
