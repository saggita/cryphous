using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MikuMikuFluid__
{
    public partial class ParticleSizeDialog : Form
    {
        public ParticleSizeDialog()
        {
            InitializeComponent();
        }

        public float X
        {
            get { return (float)numericUpDownX.Value; }
        }

        public float Y
        {
            get { return (float)numericUpDownY.Value; }
        }

        private void ParticleSizeDialog_Load(object sender, EventArgs e)
        {
            numericUpDownX.DecimalPlaces = 1;
            numericUpDownY.DecimalPlaces = 1;
        }
    }
}
