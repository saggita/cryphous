using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Crystal.Command;

namespace Cryphous
{
    public partial class ParticleObserveDialog : Form
    {
        private Command command;
        public ParticleObserveDialog(Command command)
        {
            InitializeComponent();
            this.command = command;
        }

        private void ParticleObserveDialog_Load(object sender, EventArgs e)
        {
            command.displayParticles( this.dataGridView1);
        }
    }
}
