using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Crystal.Command;

namespace Cryphous
{
    public partial class RenderingForm : Form
    {
        private RenderingCommand command;

        public RenderingForm(Command mainCommand)
        {
            InitializeComponent();
            command = new RenderingCommand( mainCommand);
        }

        private void RenderingForm_Load(object sender, EventArgs e)
        {
            pictureBox1_SizeChanged(sender, e);
            pictureBox1.Image = command.getThicknessImage();
        }

        private void buttonSurface_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = command.getSurfaceImage();
        }

        private void buttonThickness_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = command.getThicknessImage();
        }

        private void buttonNormal_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = command.getNormalImage();
        }

        private void buttonDepth_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = command.getDepthImage();
        }

        private void pictureBox1_SizeChanged(object sender, EventArgs e)
        {
            command.setHeight(pictureBox1.Height);
            command.setWidth(pictureBox1.Width);
        }
    }
}
