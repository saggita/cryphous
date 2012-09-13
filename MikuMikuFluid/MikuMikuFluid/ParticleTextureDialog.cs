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
    public partial class ParticleTextureDialog : Form
    {
        private Bitmap textureImage;
        public bool updated = false;

        public ParticleTextureDialog()
        {
            InitializeComponent();
        }

        public Bitmap TextureImage
        {
            get { return textureImage; }
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
    }
}
