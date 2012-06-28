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

        public ICommandAPI API { get; set; }

        private FrameSettingForm frameSettingDialog;

        private long keyFrame;

        private List<Vector3> initialPositions;

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
            get { return "";}// "MikuMikuFluid"; }
        }

        public string EnglishText
        {
            get { return  Text; }
        }

        public void Run()
        {
            if (API.GetActivateObjectType() != ObjectType.Model)
            {
                MessageBox.Show(ApplicationForm, "Please select a model.", "Note", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            frameSettingDialog = new FrameSettingForm();

            if (frameSettingDialog.ShowDialog(ApplicationForm) != DialogResult.OK)
            {
                return;
            }
            
            keyFrame = frameSettingDialog.StartFrame;

            setInitialPositions();

            MessageBox.Show(ApplicationForm, initialPositions.Count + " particles inputed."); 

            MMFForm mmfform = new MMFForm( this);
            mmfform.ShowDialog(ApplicationForm);
        }

        private void setInitialPositions()
        {
            initialPositions = new List<Vector3>();

            List<Bone> bones = API.GetBones();
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Vector3 position = bones[boneIndex].Position;
                int howManylayer = API.GetMotionLayerCount(boneIndex);
                for (int layerIndex = 0; layerIndex < howManylayer; ++layerIndex)
                {
                    List<MotionFrameData> motionFrames = API.GetMotionFrameData(boneIndex, layerIndex);
                    initialPositions.Add(motionFrames[0].position);
                }
            }
        }

        public void BakeToTimeLine(long frameNumber, List<Vector3> positions)
        {
            if ( (frameNumber % frameSettingDialog.SimulationIterval) != 0)
            {
                return;
            }
            if (frameNumber > frameSettingDialog.EndFrame)
            {
                return;
            }
            int index = 0;
            List<Bone> bones = API.GetBones();
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Vector3 position = bones[boneIndex].Position;
                int howManylayer = API.GetMotionLayerCount(boneIndex);
                for (int layerIndex = 0; layerIndex < howManylayer; ++layerIndex)
                {
                    List<MotionFrameData> motionFrames = API.GetMotionFrameData(boneIndex, layerIndex);
                    AddMotionFrame(motionFrames, keyFrame, new Vector3(0.0F, index * 1.0F, 0.0F));
                    API.ReplaceAllMotionFrameData(boneIndex, layerIndex, motionFrames);
                    index++;
                }
            }
            keyFrame += frameSettingDialog.KeyFrameInterval;
        }

        private void AddMotionFrame(List<MotionFrameData> motionFrames, long frameNumber, Vector3 position)
        {
            int index = motionFrames.FindIndex(delegate(MotionFrameData mdata)
            {
                return mdata.frameNumber == frameNumber;
            });
            if (index < 0){
                motionFrames.Add(new MotionFrameData(frameNumber, position, Quaternion.Identity ));
            }
            else{
                motionFrames[index].position = position;
            }
        }

        public void Dispose()
        {

        }
    }
}
