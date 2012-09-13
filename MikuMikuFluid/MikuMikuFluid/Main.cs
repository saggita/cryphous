using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Threading.Tasks;
using System.Threading;
using MikuMikuPlugin;
using DxMath;
using Cryphous;

namespace MikuMikuFluid
{
    public class Main : IResidentPlugin
    {
        private List<ScreenImage_3D> screen3Ds;

        public Guid GUID
        {
            get { return new Guid(); }
        }

        public IWin32Window ApplicationForm { get; set; }

        public Scene Scene { get; set; }

        public string Description
        {
            get { return "MikuMikuFluid"; }
        }

        public Image Image
        {
            get { return MikuMikuFluid__.Properties.Resources.MMF_L; }
        }

        public Image SmallImage
        {
            get { return MikuMikuFluid__.Properties.Resources.MMF; }
        }

        public string Text
        {
            get { return ""; }// "MikuMikuFluid"; }
        }

        public string EnglishText
        {
            get { return Text; }
        }
        
        private MainForm mainForm;

        private MikuMikuFluid__.ParticleTextureDialog dialog;

        private const int maxParticles = 30000;

        public void Initialize()
        {
            screen3Ds = new List<ScreenImage_3D>();
            Bitmap bitmap = new Bitmap(MikuMikuFluid__.Properties.Resources.sprite);
            for (int x = 0; x < bitmap.Width; ++x)
            {
                for (int y = 0; y < bitmap.Height; ++y)
                {
                    Color color = bitmap.GetPixel( x, y);
                    color = Color.FromArgb((byte.MaxValue - color.B) / 4, 0, 0, color.B );
                    bitmap.SetPixel(x, y, color);
                }
            }
            for( int i = 0; i < maxParticles; ++i ) {
                Vector3 vector = new Vector3(10000.0f, 10000.0f, 10000.0f);
                ScreenImage_3D screen3D = new ScreenImage_3D(vector, bitmap);
                screen3D.Size = new Vector2(1.0F, 1.0F);
                Scene.ScreenObjects.Add(screen3D);
                screen3Ds.Add(screen3D);
            }
            dialog = new MikuMikuFluid__.ParticleTextureDialog();
        }

        public void Enabled()
        {
            dialog.Show();
        
            List<float[]> bonePositions = new List<float[]>();
            foreach( Model model in Scene.Models ) {
                foreach (Bone bone in model.Bones)
                {
                    float[] pos = new float[3];
                    pos[0] = bone.InitialPosition.X;
                    pos[1] = bone.InitialPosition.Y;
                    pos[2] = bone.InitialPosition.Z;
                    bonePositions.Add(pos);
                }
            }
            foreach (ScreenImage_3D screen in screen3Ds)
            {
                screen.Position = new Vector3(10000.0f, 10000.0f, 10000.0f);
            }
            mainForm = new MainForm(false, bonePositions);
            mainForm.Show();
        }

        public void Update(float Frame, float ElapsedTime)
        {
            if (dialog.updated)
            {
                foreach (ScreenImage_3D screen in screen3Ds)
                {
                    if (dialog.TextureImage != null)
                    {
                        screen.Image.Dispose();
                        screen.Image = dialog.TextureImage;
                    }
                }
                dialog.updated = false;
            }
            
            Vector3 angle = Scene.Cameras[0].CurrentMotion.Angle;
            Quaternion quaternion = Quaternion.RotationYawPitchRoll(-angle.Y, -angle.X, -angle.Z);
            
            mainForm.proceed();
            List<float[]> simulatedPositions = mainForm.SimulatedPositions;
            if (simulatedPositions == null)
            {
                return;
            }
            
            int screenIndex = 0;
            for (int i = 0; (i < simulatedPositions.Count) && (screenIndex < screen3Ds.Count); ++i)
            {
                float posx = simulatedPositions[i][0];
                float posy = simulatedPositions[i][1];
                float posz = simulatedPositions[i][2];
                screen3Ds[screenIndex].Position = new Vector3(posx, posy, posz);
                screen3Ds[screenIndex].Rotation = quaternion;
                ++screenIndex;
            }
        }

        public void Disabled()
        {
            dialog.Hide();
            mainForm.Close();
        }

        public void Dispose()
        {
            foreach (ScreenImage_3D screen in screen3Ds)
            {
                screen.Dispose();
            }
        }
    }
}
