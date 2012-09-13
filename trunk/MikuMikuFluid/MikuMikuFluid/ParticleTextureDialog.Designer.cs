namespace MikuMikuFluid__
{
    partial class ParticleTextureDialog
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
            this.buttonTexture = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonTexture
            // 
            this.buttonTexture.Location = new System.Drawing.Point(29, 12);
            this.buttonTexture.Name = "buttonTexture";
            this.buttonTexture.Size = new System.Drawing.Size(75, 23);
            this.buttonTexture.TabIndex = 2;
            this.buttonTexture.Text = "SetTexture";
            this.buttonTexture.UseVisualStyleBackColor = true;
            this.buttonTexture.Click += new System.EventHandler(this.buttonTexture_Click);
            // 
            // ParticleTextureDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(140, 47);
            this.Controls.Add(this.buttonTexture);
            this.Name = "ParticleTextureDialog";
            this.Text = "ParticleTexture";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonTexture;
    }
}