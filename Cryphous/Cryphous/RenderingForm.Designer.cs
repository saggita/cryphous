namespace Cryphous
{
    partial class RenderingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.buttonSurface = new System.Windows.Forms.Button();
            this.buttonThickness = new System.Windows.Forms.Button();
            this.buttonNormal = new System.Windows.Forms.Button();
            this.buttonDepth = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(550, 413);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.SizeChanged += new System.EventHandler(this.pictureBox1_SizeChanged);
            // 
            // buttonSurface
            // 
            this.buttonSurface.Location = new System.Drawing.Point(475, 390);
            this.buttonSurface.Name = "buttonSurface";
            this.buttonSurface.Size = new System.Drawing.Size(75, 23);
            this.buttonSurface.TabIndex = 1;
            this.buttonSurface.Text = "Surface";
            this.buttonSurface.UseVisualStyleBackColor = true;
            this.buttonSurface.Click += new System.EventHandler(this.buttonSurface_Click);
            // 
            // buttonThickness
            // 
            this.buttonThickness.Location = new System.Drawing.Point(0, 390);
            this.buttonThickness.Name = "buttonThickness";
            this.buttonThickness.Size = new System.Drawing.Size(75, 23);
            this.buttonThickness.TabIndex = 2;
            this.buttonThickness.Text = "Thickness";
            this.buttonThickness.UseVisualStyleBackColor = true;
            this.buttonThickness.Click += new System.EventHandler(this.buttonThickness_Click);
            // 
            // buttonNormal
            // 
            this.buttonNormal.Location = new System.Drawing.Point(122, 390);
            this.buttonNormal.Name = "buttonNormal";
            this.buttonNormal.Size = new System.Drawing.Size(75, 23);
            this.buttonNormal.TabIndex = 3;
            this.buttonNormal.Text = "Normal";
            this.buttonNormal.UseVisualStyleBackColor = true;
            this.buttonNormal.Click += new System.EventHandler(this.buttonNormal_Click);
            // 
            // buttonDepth
            // 
            this.buttonDepth.Location = new System.Drawing.Point(239, 390);
            this.buttonDepth.Name = "buttonDepth";
            this.buttonDepth.Size = new System.Drawing.Size(75, 23);
            this.buttonDepth.TabIndex = 4;
            this.buttonDepth.Text = "Depth";
            this.buttonDepth.UseVisualStyleBackColor = true;
            this.buttonDepth.Click += new System.EventHandler(this.buttonDepth_Click);
            // 
            // RenderingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(550, 413);
            this.Controls.Add(this.buttonDepth);
            this.Controls.Add(this.buttonNormal);
            this.Controls.Add(this.buttonThickness);
            this.Controls.Add(this.buttonSurface);
            this.Controls.Add(this.pictureBox1);
            this.Name = "RenderingForm";
            this.Text = "RenderingForm";
            this.Load += new System.EventHandler(this.RenderingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button buttonSurface;
        private System.Windows.Forms.Button buttonThickness;
        private System.Windows.Forms.Button buttonNormal;
        private System.Windows.Forms.Button buttonDepth;
    }
}