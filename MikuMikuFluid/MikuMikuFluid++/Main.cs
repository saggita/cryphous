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

        private float time = 0;

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
            get { return ""; }
        }

        public string EnglishText
        {
            get { return Text; }
        }

        public void Initialize()
        {
            screen3Ds = new List<ScreenImage_3D>();
            Random rand = new Random(0);
            Bitmap bitmap = new Bitmap(1, 1);
            Color color = Color.FromArgb(128, Color.Blue);
            bitmap.SetPixel(0, 0, color);
            for (int i = 0; i < 10000; ++i)
            {
                Vector3 vector = new Vector3(rand.Next(10000) / 100.0f - 50.0f, rand.Next(10000) / 100.0f - 50.0f, rand.Next(10000) / 100.0f - 50.0f);
                ScreenImage_3D screen3D = new ScreenImage_3D(vector, bitmap);
                screen3Ds.Add(screen3D);
                screen3D.Size = new Vector2(0.1F, 0.1F);
                Scene.ScreenObjects.Add(screen3D);
            }
        }

        public void Enabled()
        {
            Random rand = new Random(0);
            foreach (ScreenImage_3D screen3D in screen3Ds)
            {
                Vector3 vector = new Vector3(rand.Next(10000) / 100.0f - 50.0f, rand.Next(10000) / 100.0f - 50.0f, rand.Next(10000) / 100.0f - 50.0f);
                screen3D.Position = vector;
            }
        }

        public void Update(float Frame, float ElapsedTime)
        {
            foreach (ScreenImage_3D screen3D in screen3Ds)
            {
                Vector3 position = screen3D.Position;
                position.X += ElapsedTime * 0.1F;
                screen3D.Position = position;
            }
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
