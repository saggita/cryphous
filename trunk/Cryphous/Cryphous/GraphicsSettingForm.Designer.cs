namespace Cryphous
{
    partial class GraphicsSettingForm
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
            this.checkBoxBoundingBox = new System.Windows.Forms.CheckBox();
            this.checkBoxApplyPointSprite = new System.Windows.Forms.CheckBox();
            this.trackBarAlphaPower = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.trackBarPointSize = new System.Windows.Forms.TrackBar();
            this.labelPointSize = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarAlphaPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarPointSize)).BeginInit();
            this.SuspendLayout();
            // 
            // checkBoxBoundingBox
            // 
            this.checkBoxBoundingBox.AutoSize = true;
            this.checkBoxBoundingBox.Location = new System.Drawing.Point(214, 58);
            this.checkBoxBoundingBox.Name = "checkBoxBoundingBox";
            this.checkBoxBoundingBox.Size = new System.Drawing.Size(91, 16);
            this.checkBoxBoundingBox.TabIndex = 69;
            this.checkBoxBoundingBox.Text = "BoundingBox";
            this.checkBoxBoundingBox.UseVisualStyleBackColor = true;
            this.checkBoxBoundingBox.CheckedChanged += new System.EventHandler(this.checkBoxBoundingBox_CheckedChanged);
            // 
            // checkBoxApplyPointSprite
            // 
            this.checkBoxApplyPointSprite.AutoSize = true;
            this.checkBoxApplyPointSprite.Location = new System.Drawing.Point(214, 18);
            this.checkBoxApplyPointSprite.Name = "checkBoxApplyPointSprite";
            this.checkBoxApplyPointSprite.Size = new System.Drawing.Size(80, 16);
            this.checkBoxApplyPointSprite.TabIndex = 68;
            this.checkBoxApplyPointSprite.Text = "PointSprite";
            this.checkBoxApplyPointSprite.UseVisualStyleBackColor = true;
            this.checkBoxApplyPointSprite.CheckedChanged += new System.EventHandler(this.checkBoxApplyPointSprite_CheckedChanged);
            // 
            // trackBarAlphaPower
            // 
            this.trackBarAlphaPower.Location = new System.Drawing.Point(72, 12);
            this.trackBarAlphaPower.Maximum = 100;
            this.trackBarAlphaPower.Name = "trackBarAlphaPower";
            this.trackBarAlphaPower.Size = new System.Drawing.Size(104, 45);
            this.trackBarAlphaPower.TabIndex = 67;
            this.trackBarAlphaPower.Value = 1;
            this.trackBarAlphaPower.Scroll += new System.EventHandler(this.trackBarAlphaPower_Scroll);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(60, 12);
            this.label4.TabIndex = 66;
            this.label4.Text = "PointAlpha";
            // 
            // trackBarPointSize
            // 
            this.trackBarPointSize.Location = new System.Drawing.Point(72, 53);
            this.trackBarPointSize.Maximum = 100;
            this.trackBarPointSize.Minimum = 1;
            this.trackBarPointSize.Name = "trackBarPointSize";
            this.trackBarPointSize.Size = new System.Drawing.Size(104, 45);
            this.trackBarPointSize.TabIndex = 65;
            this.trackBarPointSize.Value = 1;
            this.trackBarPointSize.Scroll += new System.EventHandler(this.trackBarPointSize_Scroll);
            // 
            // labelPointSize
            // 
            this.labelPointSize.AutoSize = true;
            this.labelPointSize.Location = new System.Drawing.Point(7, 58);
            this.labelPointSize.Name = "labelPointSize";
            this.labelPointSize.Size = new System.Drawing.Size(52, 12);
            this.labelPointSize.TabIndex = 64;
            this.labelPointSize.Text = "PointSize";
            // 
            // GraphicsSettingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(317, 98);
            this.Controls.Add(this.checkBoxBoundingBox);
            this.Controls.Add(this.checkBoxApplyPointSprite);
            this.Controls.Add(this.trackBarAlphaPower);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.trackBarPointSize);
            this.Controls.Add(this.labelPointSize);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "GraphicsSettingForm";
            this.Text = "GraphicsSettingForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.GraphicsSettingForm_FormClosing);
            this.Load += new System.EventHandler(this.GraphicsSettingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.trackBarAlphaPower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarPointSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxBoundingBox;
        private System.Windows.Forms.CheckBox checkBoxApplyPointSprite;
        private System.Windows.Forms.TrackBar trackBarAlphaPower;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar trackBarPointSize;
        private System.Windows.Forms.Label labelPointSize;
    }
}