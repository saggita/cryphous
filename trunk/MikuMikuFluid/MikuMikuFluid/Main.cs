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
        private List<List<ScreenImage_3D>> screen3Ds;

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

        private const int maxParticles = 26000;

        public void Initialize()
        {
            screen3Ds = new List<List<ScreenImage_3D>>();
            /*Bitmap bitmap = new Bitmap(1, 1);
            Color color = Color.FromArgb(128, Color.Blue);
            bitmap.SetPixel(0, 0, color);*/
            Bitmap bitmap = new Bitmap(MikuMikuFluid__.Properties.Resources.sprite);
            for (int x = 0; x < bitmap.Width; ++x)
            {
                for (int y = 0; y < bitmap.Height; ++y)
                {
                    Color color = bitmap.GetPixel( x, y);
                    color = Color.FromArgb( (byte.MaxValue - color.B) / 4, 0, 0, color.B );
                    bitmap.SetPixel(x, y, color);
                }
            }
            for( int i = 0; i < 2; ++i ) {
                screen3Ds.Add(new List<ScreenImage_3D>());
                for (int j = 0; j < 13000; ++j)
                {
                    Vector3 vector = new Vector3(10000.0f, 10000.0f, 10000.0f);
                    ScreenImage_3D screen3D = new ScreenImage_3D(vector, bitmap);
                    screen3D.Size = new Vector2(1.0F, 1.0F);
                    Scene.ScreenObjects.Add(screen3D);
                    screen3Ds[i].Add(screen3D);
                }
            }
        }

        public void Enabled()
        {
            foreach (List<ScreenImage_3D> screens in screen3Ds)
            {
                foreach (ScreenImage_3D screen in screens)
                {
                    screen.Position = new Vector3(10000.0f, 10000.0f, 10000.0f);
                }
            }
            mainForm = new MainForm(false, maxParticles);
            mainForm.Show();
        }

        public void Update(float Frame, float ElapsedTime)
        {
            // for billboard rendering
            Vector3 angle = Scene.Cameras[0].CurrentMotion.Angle;
            Quaternion quaternion = Quaternion.RotationYawPitchRoll(-angle.Y, -angle.X, -angle.Z);
            // for normal vector rendering
            //Vector3 upper = new Vector3(0.0f, 0.0f, 1.0f);
            
            mainForm.proceed();
            List<List<float[]>> simulatedPositions = mainForm.SimulatedPositions;
            List<List<float[]>> simulatedNormals = mainForm.SimulatedNormals;
            if (simulatedPositions == null)
            {
                return;
            }
            System.Diagnostics.Debug.Assert(simulatedPositions.Count == simulatedNormals.Count);

            for (int i = 0; i < simulatedPositions.Count; ++i)
            {
                //Parallel.For(0, simulatedPositions[i].Count, j =>
                for (int j = 0; j < simulatedPositions[i].Count; ++j)
                {
                    /*float normalx = simulatedNormals[i][j][0];
                    float normaly = simulatedNormals[i][j][1];
                    float normalz = simulatedNormals[i][j][2];
                    Vector3 normal = new Vector3(normalx, normaly, normalz);*/
                    
                    float posx = simulatedPositions[i][j][0];
                    float posy = simulatedPositions[i][j][1];
                    float posz = simulatedPositions[i][j][2];
                    screen3Ds[i][j].Position = new Vector3(posx, posy, posz);

                    //// TODO: ゼロベクトルを除外
                    //normal.Normalize();
                    //Vector3 axis = Vector3.Cross(upper, normal);
                    //float angle = (float)Math.Acos( Vector3.Dot(upper, normal) / ( upper.Length() * normal.Length() )); 
                    //Quaternion quaternion = Quaternion.RotationAxis(axis, angle);
                    screen3Ds[i][j].Rotation = quaternion;
                }//);
            }
            GC.Collect();
        }

        public void Disabled()
        {
            mainForm.Close();
        }

        public void Dispose()
        {
            foreach (List<ScreenImage_3D> screens in screen3Ds)
            {
                foreach (ScreenImage_3D screen in screens)
                {
                    screen.Dispose();
                }
            }
        }
    }
}
