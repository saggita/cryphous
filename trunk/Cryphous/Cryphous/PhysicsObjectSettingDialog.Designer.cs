namespace Cryphous
{
    partial class PhysicsObjectSettingDialog
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataGridViewObjectSetting = new System.Windows.Forms.DataGridView();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.headerType = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.headerPressure = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.headerViscosity = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.headerDensity = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMinX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMinY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMinZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMaxX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMaxY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMaxZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewObjectSetting)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewObjectSetting
            // 
            this.dataGridViewObjectSetting.AllowUserToAddRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewObjectSetting.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridViewObjectSetting.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewObjectSetting.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.headerType,
            this.headerPressure,
            this.headerViscosity,
            this.headerDensity,
            this.ColumnMinX,
            this.ColumnMinY,
            this.ColumnMinZ,
            this.ColumnMaxX,
            this.ColumnMaxY,
            this.ColumnMaxZ});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridViewObjectSetting.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridViewObjectSetting.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewObjectSetting.Location = new System.Drawing.Point(0, 0);
            this.dataGridViewObjectSetting.Name = "dataGridViewObjectSetting";
            this.dataGridViewObjectSetting.RowTemplate.Height = 21;
            this.dataGridViewObjectSetting.Size = new System.Drawing.Size(597, 226);
            this.dataGridViewObjectSetting.TabIndex = 1;
            this.dataGridViewObjectSetting.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewObjectSetting_CellContentClick);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(238, 200);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 17;
            this.buttonDelete.Text = "Delete";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(135, 200);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonAdd.TabIndex = 16;
            this.buttonAdd.Text = "Add";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(464, 200);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 15;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(355, 200);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 14;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // headerType
            // 
            this.headerType.HeaderText = "Type";
            this.headerType.Items.AddRange(new object[] {
            "Fluid",
            "Rigid",
            "RigidTwoWay",
            "Air",
            "Cloth"});
            this.headerType.Name = "headerType";
            this.headerType.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.headerType.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // headerPressure
            // 
            this.headerPressure.DataPropertyName = "pressureCoefficient";
            this.headerPressure.HeaderText = "Pressure";
            this.headerPressure.Name = "headerPressure";
            this.headerPressure.Width = 50;
            // 
            // headerViscosity
            // 
            this.headerViscosity.HeaderText = "Viscosity";
            this.headerViscosity.Name = "headerViscosity";
            this.headerViscosity.Width = 50;
            // 
            // headerDensity
            // 
            this.headerDensity.HeaderText = "Density";
            this.headerDensity.Name = "headerDensity";
            this.headerDensity.Width = 50;
            // 
            // ColumnMinX
            // 
            this.ColumnMinX.HeaderText = "MinX";
            this.ColumnMinX.Name = "ColumnMinX";
            this.ColumnMinX.Width = 50;
            // 
            // ColumnMinY
            // 
            this.ColumnMinY.HeaderText = "MaxX";
            this.ColumnMinY.Name = "ColumnMinY";
            this.ColumnMinY.Width = 50;
            // 
            // ColumnMinZ
            // 
            this.ColumnMinZ.HeaderText = "MinY";
            this.ColumnMinZ.Name = "ColumnMinZ";
            this.ColumnMinZ.Width = 50;
            // 
            // ColumnMaxX
            // 
            this.ColumnMaxX.HeaderText = "MaxY";
            this.ColumnMaxX.Name = "ColumnMaxX";
            this.ColumnMaxX.Width = 50;
            // 
            // ColumnMaxY
            // 
            this.ColumnMaxY.HeaderText = "MaxZ";
            this.ColumnMaxY.Name = "ColumnMaxY";
            this.ColumnMaxY.Width = 50;
            // 
            // ColumnMaxZ
            // 
            this.ColumnMaxZ.HeaderText = "MaxZ";
            this.ColumnMaxZ.Name = "ColumnMaxZ";
            this.ColumnMaxZ.Width = 50;
            // 
            // PhysicsObjectSettingDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(597, 226);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.dataGridViewObjectSetting);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "PhysicsObjectSettingDialog";
            this.Text = "PhysicsObjectSettingDialog";
            this.Load += new System.EventHandler(this.PhysicsObjectSettingDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewObjectSetting)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewObjectSetting;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.DataGridViewComboBoxColumn headerType;
        private System.Windows.Forms.DataGridViewTextBoxColumn headerPressure;
        private System.Windows.Forms.DataGridViewTextBoxColumn headerViscosity;
        private System.Windows.Forms.DataGridViewTextBoxColumn headerDensity;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMinX;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMinY;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMinZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMaxX;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMaxY;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMaxZ;

    }
}