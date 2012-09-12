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
        private Bitmap textureImage;
        private float xSize;
        private float ySize;
        public bool updated = false;

        public ParticleSizeDialog()
        {
            InitializeComponent();
        }

        public float XSize
        {
            get { return xSize; }
        }

        public float YSize
        {
            get { return ySize; }
        }

        public Bitmap TextureImage
        {
            get { return textureImage; }
        }

        private void ParticleSizeDialog_Load(object sender, EventArgs e)
        {
            numericUpDownX.DecimalPlaces = 1;
            numericUpDownY.DecimalPlaces = 1;
        }

        private void buttonTexture_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image Files|*.bmp;*.png;*.jpg;*.gif|All Files|*.*";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                if (updated == false)
                {
                    Bitmap originalImage = new Bitmap(dialog.FileName);
                    textureImage = new Bitmap(originalImage, new Size(16, 16));
                    updated = true;
                }
            }
        }

        private void numericUpDownX_ValueChanged(object sender, EventArgs e)
        {
            if (updated == false)
            {
                xSize = (float)numericUpDownX.Value;
                updated = true;
            }
        }

        private void numericUpDownY_ValueChanged(object sender, EventArgs e)
        {
            if (updated == false)
            {
                ySize = (float)numericUpDownY.Value;
                updated = true;
            }
        }

    }
}
