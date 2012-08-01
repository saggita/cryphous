using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using MikuMikuPlugin;
using DxMath;

namespace MikuMikuFluid 
{
    public class Main : ICommandPlugin
    {
        public Guid GUID
        {
            get { return System.Guid.NewGuid(); }
        }

        public IWin32Window ApplicationForm { get; set; }

        public Scene Scene { get; set; }

        public string Description
        {
            get { return "MikuMikuFluid"; }
        }

        public Image Image
        {
            get { return Properties.Resources.MMF_L; }
        }

        public Image SmallImage
        {
            get { return Properties.Resources.MMF; }
        }

        public string Text
        {
            get { return ""; }// "MikuMikuFluid"; }
        }

        public string EnglishText
        {
            get { return Text; }
        }

        private FrameSettingForm frameSettingDialog;

        private long keyFrame;

        public void initKeyFrame()
        {
            keyFrame = frameSettingDialog.StartFrame;
        }

        private List<List<float[]>> initialPositions;

        public List<List<float[]>> InitialPositions
        {
            get { return initialPositions; }
        }

        public void Run(CommandArgs e)
        {
            frameSettingDialog = new FrameSettingForm();

            if (frameSettingDialog.ShowDialog(ApplicationForm) != DialogResult.OK)
            {
                return;
            }

            initKeyFrame();

            setInitialPositions();

            MessageBox.Show(ApplicationForm, initialPositions.Count + " models inputed."); 

            MMFForm mmfform = new MMFForm( this);
            mmfform.Show();
        }

        private void setInitialPositions()
        {
            initialPositions = new List<List<float[]>>();
            ModelCollection models = Scene.Models;
            for( int modelIndex = 0; modelIndex < Scene.Models.Count; ++modelIndex )
            {
                initialPositions.Add( new List<float[]>() );
                Model model = Scene.Models[modelIndex];
                BoneCollection bones = model.Bones;
                for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
                {
                    Vector3 bonePosition = bones[boneIndex].InitialPosition;
                    float[] pos = new float[3];
                    pos[0] = bonePosition.X;
                    pos[1] = bonePosition.Y;
                    pos[2] = bonePosition.Z;
                    initialPositions[modelIndex].Add(pos);
                }
            }
        }

        public void BakeToTimeLine(long frameNumber, List<List<float[]>> bakePositions)
        {
            if ( (frameNumber % frameSettingDialog.SimulationIterval) != 0)
            {
                return;
            }
            if (frameNumber > frameSettingDialog.EndFrame)
            {
                return;
            }
            ModelCollection models = Scene.Models;
            for (int modelIndex = 0; modelIndex < Scene.Models.Count; ++modelIndex)
            {
                Model model = Scene.Models[modelIndex];
                BoneCollection bones = model.Bones;
                for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
                {
                    Bone bone = bones[boneIndex];
                    Vector3 vector = new Vector3();
                    vector.X = bakePositions[modelIndex][boneIndex][0] - bone.InitialPosition[0];
                    vector.Y = bakePositions[modelIndex][boneIndex][1] - bone.InitialPosition[1];
                    vector.Z = bakePositions[modelIndex][boneIndex][2] - bone.InitialPosition[2];
                    MotionFrameData mfData = new MotionFrameData(keyFrame, vector, Quaternion.Identity);
                    bone.Layers[0].Frames.AddKeyFrame(mfData);
                }
            }
            keyFrame += frameSettingDialog.KeyFrameInterval;
        }

        public void Dispose()
        {

        }
    }
}
