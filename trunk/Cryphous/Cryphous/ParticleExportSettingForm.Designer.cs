namespace Cryphous
{
    partial class ParticleExportSettingForm
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
            this.buttonFileReset = new System.Windows.Forms.Button();
            this.buttonFileSet = new System.Windows.Forms.Button();
            this.textBoxOutputFile = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.textBoxOutputInterval = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonFileReset
            // 
            this.buttonFileReset.Location = new System.Drawing.Point(194, 66);
            this.buttonFileReset.Name = "buttonFileReset";
            this.buttonFileReset.Size = new System.Drawing.Size(54, 23);
            this.buttonFileReset.TabIndex = 15;
            this.buttonFileReset.Text = "Reset";
            this.buttonFileReset.UseVisualStyleBackColor = true;
            this.buttonFileReset.Click += new System.EventHandler(this.buttonFileReset_Click);
            // 
            // buttonFileSet
            // 
            this.buttonFileSet.Location = new System.Drawing.Point(134, 66);
            this.buttonFileSet.Name = "buttonFileSet";
            this.buttonFileSet.Size = new System.Drawing.Size(54, 23);
            this.buttonFileSet.TabIndex = 14;
            this.buttonFileSet.Text = "Set";
            this.buttonFileSet.UseVisualStyleBackColor = true;
            this.buttonFileSet.Click += new System.EventHandler(this.buttonFileSet_Click);
            // 
            // textBoxOutputFile
            // 
            this.textBoxOutputFile.Location = new System.Drawing.Point(134, 41);
            this.textBoxOutputFile.Name = "textBoxOutputFile";
            this.textBoxOutputFile.Size = new System.Drawing.Size(100, 19);
            this.textBoxOutputFile.TabIndex = 13;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 12);
            this.label2.TabIndex = 12;
            this.label2.Text = "OutputFile";
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(136, 95);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 11;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(53, 95);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 10;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // textBoxOutputInterval
            // 
            this.textBoxOutputInterval.Location = new System.Drawing.Point(134, 12);
            this.textBoxOutputInterval.Name = "textBoxOutputInterval";
            this.textBoxOutputInterval.Size = new System.Drawing.Size(100, 19);
            this.textBoxOutputInterval.TabIndex = 9;
            this.textBoxOutputInterval.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "OutputInterval";
            // 
            // ParticleExportSettingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(277, 126);
            this.Controls.Add(this.buttonFileReset);
            this.Controls.Add(this.buttonFileSet);
            this.Controls.Add(this.textBoxOutputFile);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.textBoxOutputInterval);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ParticleExportSettingForm";
            this.Text = "ParticleExportSettingForm";
            this.Load += new System.EventHandler(this.ParticleExportSettingForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonFileReset;
        private System.Windows.Forms.Button buttonFileSet;
        private System.Windows.Forms.TextBox textBoxOutputFile;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.TextBox textBoxOutputInterval;
        private System.Windows.Forms.Label label1;
    }
}