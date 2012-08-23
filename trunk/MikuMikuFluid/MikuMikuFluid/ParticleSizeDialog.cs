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

        public Bitmap TextureImage
        {
            get { return textureImage; }
        }

        private void ParticleSizeDialog_Load(object sender, EventArgs e)
        {
            numericUpDownX.DecimalPlaces = 1;
            numericUpDownY.DecimalPlaces = 1;
            numericUpDownAlphaScale.DecimalPlaces = 1;
        }

        private void buttonTexture_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image Files|*.bmp;*.png;*.jpg;*.gif|All Files|*.*";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                textureImage = new Bitmap(dialog.FileName);
                for (int x = 0; x < textureImage.Width; ++x)
                {
                    for (int y = 0; y < textureImage.Height; ++y)
                    {
                        Color color = textureImage.GetPixel(x, y);
                        textureImage.SetPixel(x, y, getColorWithAlpha(color));
                    }
                }
            }
        }

        private Color getColorWithAlpha(Color color)
        {
            double alpha = 0.299 * color.R + 0.587 * color.G + 0.114 * color.B;
            alpha *= (double)numericUpDownAlphaScale.Value;
            return Color.FromArgb((int)alpha, color.R, color.G, color.B);
        }
    }
}
