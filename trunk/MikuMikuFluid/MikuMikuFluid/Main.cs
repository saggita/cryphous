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
            get { return "MikuMikuFluid"; }
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

            FrameSettingForm frameSettingDialog = new FrameSettingForm();

            if (frameSettingDialog.ShowDialog(ApplicationForm) != DialogResult.OK)
            {
                return;
            }
            
            long start = frameSettingDialog.StartFrame;
            long end = frameSettingDialog.EndFrame;

            long keyFrameInterval = frameSettingDialog.KeyFrameInterval;

            List<Vector3> positions = new List<Vector3>();
            // シミュレーション前の登録．ボーン->粒子.
            List<Bone> bones = API.GetBones();
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Vector3 position = bones[boneIndex].Position;
                int howManylayer = API.GetMotionLayerCount(boneIndex);
                for (int layerIndex = 0; layerIndex < howManylayer; ++layerIndex)
                {
                    List<MotionFrameData> motionFrames = API.GetMotionFrameData(boneIndex, layerIndex);
                    positions.Add( motionFrames[0].position );
                }
            }

            MessageBox.Show(ApplicationForm, positions.Count + " particles inputed."); 

            MMFForm mmfform = new MMFForm();
            mmfform.Positions = positions;
            mmfform.ShowDialog(ApplicationForm);
            positions = mmfform.Positions;

            int index = 0;
            // シミュレーション後の登録．粒子->ボーン.
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Vector3 position = bones[boneIndex].Position;
                int howManylayer = API.GetMotionLayerCount(boneIndex);
                for (int layerIndex = 0; layerIndex < howManylayer; ++layerIndex)
                {
                    List<MotionFrameData> motionFrames = API.GetMotionFrameData(boneIndex, layerIndex);

                    /*for (long frame = start; frame < end; ++frame)
                    {
                        AddMotionFrame(motionFrames, frame, new Vector3(0.0F, 1.0F * frame, 0.0F));
                    }*/
                    AddMotionFrame(motionFrames, end, positions[index++]);
                    API.ReplaceAllMotionFrameData(boneIndex, layerIndex, motionFrames);
                }
            }
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
