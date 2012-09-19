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
        public RenderingForm()
        {
            InitializeComponent();
        }

        private void RenderingForm_Load(object sender, EventArgs e)
        {
            RenderingCommand command = new RenderingCommand();
            pictureBox1.Image = command.getImage(pictureBox1.Width, pictureBox1.Height);
        }

        private void pictureBox1_SizeChanged(object sender, EventArgs e)
        {
            RenderingCommand command = new RenderingCommand();
            pictureBox1.Image = command.getImage(pictureBox1.Width, pictureBox1.Height);
        }
    }
}
