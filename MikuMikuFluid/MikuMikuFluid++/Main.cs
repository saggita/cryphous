using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using MikuMikuPlugin;
using DxMath;

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
            get { return "MikuMikuFluid++"; }
        }

        public Image Image
        {
            get { return null; }
        }

        public Image SmallImage
        {
            get { return null; }
        }

        public string Text
        {
            get { return ""; }// "MikuMikuFluid"; }
        }

        public string EnglishText
        {
            get { return Text; }
        }

        private float currentFrame;

        private MMFForm form;

        private List<List<float[]>> simulatedPositions;
        public List<List<float[]>> SimulatedPositions
        {
            set { simulatedPositions = value; }
        }

        public void Initialize()
        {
            screen3Ds = new List<ScreenImage_3D>();
            Random rand = new Random(0);
            Bitmap bitmap = new Bitmap(1, 1);
            Color color = Color.FromArgb(128, Color.Blue);
            bitmap.SetPixel(0, 0, color);
            for (int i = 0; i < 20000; ++i)
            {
                Vector3 vector = new Vector3(10000.0f, 10000.0f, 10000.0f);
                ScreenImage_3D screen3D = new ScreenImage_3D(vector, bitmap);
                screen3Ds.Add(screen3D);
                screen3D.Size = new Vector2(0.5F, 0.5F);
                Scene.ScreenObjects.Add(screen3D);
            }
        }

        public void Enabled()
        {
            Random rand = new Random(0);
            foreach (ScreenImage_3D screen3D in screen3Ds)
            {
                Vector3 vector = new Vector3(10000.0f, 10000.0f, 10000.0f);
                screen3D.Position = vector;
            }
            form = new MMFForm(this);
            form.Show();
        }

        public void Update(float Frame, float ElapsedTime)
        {
            if (currentFrame == Frame)
            {
                return;
            }
            form.proceed();
          
            int index = 0;
            for (int i = 0; i < simulatedPositions.Count; ++i)
            {
                for (int j = 0; j < simulatedPositions[i].Count; ++j)
                {
                    float x = simulatedPositions[i][j][0];
                    float y = simulatedPositions[i][j][1];
                    float z = simulatedPositions[i][j][2];
                    screen3Ds[index].Position = new Vector3(x, y, z);
                    ++index;
                }
            }
            currentFrame = Frame;
        }

        public void Disabled()
        {

        }

        public void Dispose()
        {
            foreach (ScreenImage_3D screen3D in screen3Ds)
            {
                screen3D.Dispose();
            }
        }
    }
}
