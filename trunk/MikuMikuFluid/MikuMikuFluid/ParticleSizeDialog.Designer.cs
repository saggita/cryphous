namespace MikuMikuFluid__
{
    partial class ParticleSizeDialog
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
            this.numericUpDownX = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownY = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownY)).BeginInit();
            this.SuspendLayout();
            // 
            // numericUpDownX
            // 
            this.numericUpDownX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownX.Location = new System.Drawing.Point(43, 12);
            this.numericUpDownX.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownX.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownX.Name = "numericUpDownX";
            this.numericUpDownX.Size = new System.Drawing.Size(63, 19);
            this.numericUpDownX.TabIndex = 0;
            this.numericUpDownX.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numericUpDownY
            // 
            this.numericUpDownY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownY.Location = new System.Drawing.Point(154, 12);
            this.numericUpDownY.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownY.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownY.Name = "numericUpDownY";
            this.numericUpDownY.Size = new System.Drawing.Size(63, 19);
            this.numericUpDownY.TabIndex = 1;
            this.numericUpDownY.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // ParticleSizeDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 49);
            this.Controls.Add(this.numericUpDownY);
            this.Controls.Add(this.numericUpDownX);
            this.Name = "ParticleSizeDialog";
            this.Text = "ParticleSizeDialog";
            this.Load += new System.EventHandler(this.ParticleSizeDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownY)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown numericUpDownX;
        private System.Windows.Forms.NumericUpDown numericUpDownY;
    }
}