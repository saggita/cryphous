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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataGridViewLightSourceSetting = new System.Windows.Forms.DataGridView();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.PosX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PosY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PosZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MinZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewLightSourceSetting)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewLightSourceSetting
            // 
            this.dataGridViewLightSourceSetting.AllowUserToAddRows = false;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle5.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle5.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewLightSourceSetting.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
            this.dataGridViewLightSourceSetting.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewLightSourceSetting.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.PosX,
            this.PosY,
            this.PosZ,
            this.MaxY,
            this.MinZ,
            this.MaxZ});
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle6.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridViewLightSourceSetting.DefaultCellStyle = dataGridViewCellStyle6;
            this.dataGridViewLightSourceSetting.Location = new System.Drawing.Point(3, 12);
            this.dataGridViewLightSourceSetting.Name = "dataGridViewLightSourceSetting";
            this.dataGridViewLightSourceSetting.RowTemplate.Height = 21;
            this.dataGridViewLightSourceSetting.Size = new System.Drawing.Size(289, 128);
            this.dataGridViewLightSourceSetting.TabIndex = 2;
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
            // LightSourceSettingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(297, 194);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.dataGridViewLightSourceSetting);
            this.Name = "LightSourceSettingForm";
            this.Text = "LightSourceSettingForm";
            this.Load += new System.EventHandler(this.LightSourceSettingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewLightSourceSetting)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewLightSourceSetting;
        private System.Windows.Forms.DataGridViewTextBoxColumn PosX;
        private System.Windows.Forms.DataGridViewTextBoxColumn PosY;
        private System.Windows.Forms.DataGridViewTextBoxColumn PosZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxY;
        private System.Windows.Forms.DataGridViewTextBoxColumn MinZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxZ;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
    }
}