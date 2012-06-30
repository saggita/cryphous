using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using MikuMikuPlugin;
using DxMath;

using ManagedPosition = System.Collections.Generic.List<double>;

namespace MikuMikuFluid 
{
    public class Main : ICommandPlugin
    {
        public IWin32Window ApplicationForm { get; set; }

        public ICommandAPI API { get; set; }

        private FrameSettingForm frameSettingDialog;

        private long keyFrame;

        public void initKeyFrame()
        {
            keyFrame = frameSettingDialog.StartFrame;
        }

        private List<ManagedPosition> initialPositions;

        public List<ManagedPosition> InitialPositions
        {
            get { return initialPositions; }
        }

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

            initKeyFrame();

            setInitialPositions();

            MessageBox.Show(ApplicationForm, initialPositions.Count + " particles inputed."); 

            MMFForm mmfform = new MMFForm( this);
            mmfform.ShowDialog(ApplicationForm);
        }

        private void setInitialPositions()
        {
            initialPositions = new List<ManagedPosition>();

            List<Bone> bones = API.GetBones();
            for (int boneIndex = 0; boneIndex < bones.Count; boneIndex++)
            {
                Vector3 bonePosition = bones[boneIndex].Position;
                int howManylayer = API.GetMotionLayerCount(boneIndex);
                for (int layerIndex = 0; layerIndex < howManylayer; ++layerIndex)
                {
                    List<MotionFrameData> motionFrames = API.GetMotionFrameData(boneIndex, layerIndex);
                    ManagedPosition pos = new ManagedPosition();
                    pos.Add( bonePosition.X + motionFrames[0].position.X);
                    pos.Add( bonePosition.Y + motionFrames[0].position.Y);
                    pos.Add( bonePosition.Z + motionFrames[0].position.Z);
                    initialPositions.Add( pos);
                }
            }
        }

        public void BakeToTimeLine(long frameNumber, List<ManagedPosition> bakePositions)
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
                    Vector3 pos = new Vector3();
                    pos.X = (float) bakePositions[index][0] - position[0];
                    pos.Y = (float) bakePositions[index][1] - position[1];
                    pos.Z = (float) bakePositions[index][2] - position[2];

                    AddMotionFrame(motionFrames, keyFrame, pos);
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
