namespace MikuMikuFluid
{
    partial class FrameSettingForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.startUpDown = new System.Windows.Forms.NumericUpDown();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.endUpDown = new System.Windows.Forms.NumericUpDown();
            this.hyphonLabel = new System.Windows.Forms.Label();
            this.startLabel = new System.Windows.Forms.Label();
            this.endLabel = new System.Windows.Forms.Label();
            this.keyFrameIntervalUpDown = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.simulationIntervalUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.startUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.endUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.keyFrameIntervalUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.simulationIntervalUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // startUpDown
            // 
            this.startUpDown.Location = new System.Drawing.Point(12, 32);
            this.startUpDown.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.startUpDown.Name = "startUpDown";
            this.startUpDown.Size = new System.Drawing.Size(81, 19);
            this.startUpDown.TabIndex = 0;
            this.startUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // okButton
            // 
            this.okButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.okButton.Location = new System.Drawing.Point(84, 115);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 23);
            this.okButton.TabIndex = 1;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.Location = new System.Drawing.Point(165, 115);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // endUpDown
            // 
            this.endUpDown.Location = new System.Drawing.Point(127, 32);
            this.endUpDown.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.endUpDown.Name = "endUpDown";
            this.endUpDown.Size = new System.Drawing.Size(81, 19);
            this.endUpDown.TabIndex = 3;
            this.endUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.endUpDown.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // hyphonLabel
            // 
            this.hyphonLabel.AutoSize = true;
            this.hyphonLabel.Location = new System.Drawing.Point(101, 34);
            this.hyphonLabel.Name = "hyphonLabel";
            this.hyphonLabel.Size = new System.Drawing.Size(11, 12);
            this.hyphonLabel.TabIndex = 4;
            this.hyphonLabel.Text = "-";
            // 
            // startLabel
            // 
            this.startLabel.AutoSize = true;
            this.startLabel.Location = new System.Drawing.Point(13, 14);
            this.startLabel.Name = "startLabel";
            this.startLabel.Size = new System.Drawing.Size(66, 12);
            this.startLabel.TabIndex = 5;
            this.startLabel.Text = "Start Frame";
            // 
            // endLabel
            // 
            this.endLabel.AutoSize = true;
            this.endLabel.Location = new System.Drawing.Point(125, 14);
            this.endLabel.Name = "endLabel";
            this.endLabel.Size = new System.Drawing.Size(60, 12);
            this.endLabel.TabIndex = 6;
            this.endLabel.Text = "End Frame";
            // 
            // keyFrameIntervalUpDown
            // 
            this.keyFrameIntervalUpDown.Location = new System.Drawing.Point(12, 81);
            this.keyFrameIntervalUpDown.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.keyFrameIntervalUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.keyFrameIntervalUpDown.Name = "keyFrameIntervalUpDown";
            this.keyFrameIntervalUpDown.Size = new System.Drawing.Size(81, 19);
            this.keyFrameIntervalUpDown.TabIndex = 7;
            this.keyFrameIntervalUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.keyFrameIntervalUpDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 66);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(106, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "Interval (KeyFrame)";
            // 
            // simulationIntervalUpDown
            // 
            this.simulationIntervalUpDown.Location = new System.Drawing.Point(127, 83);
            this.simulationIntervalUpDown.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.simulationIntervalUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.simulationIntervalUpDown.Name = "simulationIntervalUpDown";
            this.simulationIntervalUpDown.Size = new System.Drawing.Size(81, 19);
            this.simulationIntervalUpDown.TabIndex = 9;
            this.simulationIntervalUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.simulationIntervalUpDown.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(125, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(108, 12);
            this.label2.TabIndex = 10;
            this.label2.Tag = "";
            this.label2.Text = "Interval (Simulation)";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(101, 83);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(11, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "-";
            // 
            // FrameSettingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(252, 150);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.simulationIntervalUpDown);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.keyFrameIntervalUpDown);
            this.Controls.Add(this.endLabel);
            this.Controls.Add(this.startLabel);
            this.Controls.Add(this.hyphonLabel);
            this.Controls.Add(this.endUpDown);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.startUpDown);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrameSettingForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "FrameSetting";
            ((System.ComponentModel.ISupportInitialize)(this.startUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.endUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.keyFrameIntervalUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.simulationIntervalUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown startUpDown;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.NumericUpDown endUpDown;
        private System.Windows.Forms.Label hyphonLabel;
        private System.Windows.Forms.Label startLabel;
        private System.Windows.Forms.Label endLabel;
        private System.Windows.Forms.NumericUpDown keyFrameIntervalUpDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown simulationIntervalUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}