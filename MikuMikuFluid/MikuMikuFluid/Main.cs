﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
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

        private float currentFrame;

        private MainForm mainForm;

        private const int maxParticles = 25500;

        public void Initialize()
        {
            screen3Ds = new List<ScreenImage_3D>();
            Random rand = new Random(0);
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
            for (int i = 0; i < maxParticles; ++i)
            {
                Vector3 vector = new Vector3(10000.0f, 10000.0f, 10000.0f);
                ScreenImage_3D screen3D = new ScreenImage_3D(vector, bitmap);
                screen3Ds.Add(screen3D);
                screen3D.Size = new Vector2(1.0F, 1.0F);
                Scene.ScreenObjects.Add(screen3D);
            }
        }

        public void Enabled()
        {
            foreach (ScreenImage_3D screen3D in screen3Ds)
            {
                Vector3 vector = new Vector3(10000.0f, 10000.0f, 10000.0f);
                screen3D.Position = vector;
            }
            mainForm = new MainForm(false, maxParticles);
            mainForm.Show();
        }

        public void Update(float Frame, float ElapsedTime)
        {
            Vector3 angle = Scene.Cameras[0].CurrentMotion.Angle;
            Quaternion quaternion = Quaternion.RotationYawPitchRoll(-angle.Y, -angle.X, -angle.Z);

            mainForm.proceed();
            List<List<float[]>> simulatedPositions = mainForm.SimulatedParticles;
            if (simulatedPositions == null)
            {
                return;
            }
          
            int index = 0;
            for (int i = 0; i < simulatedPositions.Count; ++i)
            {
                for (int j = 0; j < simulatedPositions[i].Count; ++j)
                {
                    float x = simulatedPositions[i][j][0];
                    float y = simulatedPositions[i][j][1];
                    float z = simulatedPositions[i][j][2];
                    screen3Ds[index].Position = new Vector3(x, y, z);
                    screen3Ds[index].Rotation = quaternion;
                    ++index;
                }
            }
            currentFrame = Frame;
        }

        public void Disabled()
        {
            mainForm.Close();
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