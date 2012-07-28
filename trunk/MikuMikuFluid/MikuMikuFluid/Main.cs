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
        public IWin32Window ApplicationForm { get; set; }

        public ICommonAPI API { get; set; }

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

        private List<float[]> initialPositions;

        public List<float[]> InitialPositions
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

            MessageBox.Show(ApplicationForm, initialPositions.Count + " particles inputed."); 

            MMFForm mmfform = new MMFForm( this);
            mmfform.Show();
        }

        private void setInitialPositions()
        {
            initialPositions = new List<float[]>();

            BoneCollection bones = Scene.ActiveModel.Bones;
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Vector3 bonePosition = bones[boneIndex].InitialPosition;
                float[] pos = new float[3];
                pos[0] = bonePosition.X;
                pos[1] = bonePosition.Y;
                pos[2] = bonePosition.Z;
                initialPositions.Add(pos);
            }
        }

        public void BakeToTimeLine(long frameNumber, List<float[]> bakePositions)
        {
            if ( (frameNumber % frameSettingDialog.SimulationIterval) != 0)
            {
                return;
            }
            if (frameNumber > frameSettingDialog.EndFrame)
            {
                return;
            }
            BoneCollection bones = Scene.ActiveModel.Bones;
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Bone bone = Scene.ActiveModel.Bones[boneIndex];
                Vector3 vector = new Vector3();
                vector.X = bakePositions[boneIndex][0] - bone.InitialPosition[0];
                vector.Y = bakePositions[boneIndex][1] - bone.InitialPosition[1];
                vector.Z = bakePositions[boneIndex][2] - bone.InitialPosition[2];
                //bone.CurrentLocalMotion.Move.X = 10.0F;// = vector;
                //AddMotionFrame();
            }
            keyFrame += frameSettingDialog.KeyFrameInterval;
        }

        //private void AddMotionFrame(List<MotionFrameData> motionFrames, long frameNumber, Vector3 position)
        //{
        //    SceneFrameCollection sf  Scene.Models[0].Bones[0].
        //    int index = motionFrames.FindIndex(delegate(MotionFrameData mdata)
        //    {
        //        return mdata.frameNumber == frameNumber;
        //    });
        //    if (index < 0){
        //        motionFrames.Add(new MotionFrameData(frameNumber, position, Quaternion.Identity ));
        //    }
        //    else{
        //        motionFrames[index].position = position;
        //    }
        //}

        public void Dispose()
        {

        }
    }
}
