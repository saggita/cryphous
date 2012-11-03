namespace Cryphous
{
    partial class LightSourceSettingForm
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataGridViewLightSourceSetting = new System.Windows.Forms.DataGridView();
            this.PosX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PosY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PosZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MinZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewLightSourceSetting)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewLightSourceSetting
            // 
            this.dataGridViewLightSourceSetting.AllowUserToAddRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewLightSourceSetting.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridViewLightSourceSetting.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewLightSourceSetting.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.PosX,
            this.PosY,
            this.PosZ,
            this.MaxY,
            this.MinZ,
            this.MaxZ,
            this.Column1});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridViewLightSourceSetting.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridViewLightSourceSetting.Location = new System.Drawing.Point(3, 12);
            this.dataGridViewLightSourceSetting.Name = "dataGridViewLightSourceSetting";
            this.dataGridViewLightSourceSetting.RowTemplate.Height = 21;
            this.dataGridViewLightSourceSetting.Size = new System.Drawing.Size(333, 128);
            this.dataGridViewLightSourceSetting.TabIndex = 2;
            // 
            // PosX
            // 
            this.PosX.HeaderText = "PosX";
            this.PosX.Name = "PosX";
            this.PosX.Width = 40;
            // 
            // PosY
            // 
            this.PosY.HeaderText = "PosY";
            this.PosY.Name = "PosY";
            this.PosY.Width = 40;
            // 
            // PosZ
            // 
            this.PosZ.HeaderText = "PosZ";
            this.PosZ.Name = "PosZ";
            this.PosZ.Width = 40;
            // 
            // MaxY
            // 
            this.MaxY.HeaderText = "DirX";
            this.MaxY.Name = "MaxY";
            this.MaxY.Width = 40;
            // 
            // MinZ
            // 
            this.MinZ.HeaderText = "DirY";
            this.MinZ.Name = "MinZ";
            this.MinZ.Width = 40;
            // 
            // MaxZ
            // 
            this.MaxZ.HeaderText = "DirZ";
            this.MaxZ.Name = "MaxZ";
            this.MaxZ.Width = 40;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "Photons";
            this.Column1.Name = "Column1";
            this.Column1.Width = 50;
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(138, 159);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 3;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(217, 159);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 4;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // LightSourceSettingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(348, 194);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.dataGridViewLightSourceSetting);
            this.Name = "LightSourceSettingForm";
            this.Text = "LightSourceSettingForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LightSourceSettingForm_FormClosing);
            this.Load += new System.EventHandler(this.LightSourceSettingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewLightSourceSetting)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewLightSourceSetting;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.DataGridViewTextBoxColumn PosX;
        private System.Windows.Forms.DataGridViewTextBoxColumn PosY;
        private System.Windows.Forms.DataGridViewTextBoxColumn PosZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxY;
        private System.Windows.Forms.DataGridViewTextBoxColumn MinZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
    }
}