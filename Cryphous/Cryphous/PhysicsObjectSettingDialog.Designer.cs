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
            this.headerType = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.headerPressure = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.headerViscosity = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.headerDensity = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MinX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MinY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MinZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaxZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Shape = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.ColumnX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxEffectLength = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxTimeStep = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.comboBoxExample = new System.Windows.Forms.ComboBox();
            this.buttonCopy = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewObjectSetting)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
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
            this.MinX,
            this.MaxX,
            this.MinY,
            this.MaxY,
            this.MinZ,
            this.MaxZ,
            this.Shape});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridViewObjectSetting.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridViewObjectSetting.Location = new System.Drawing.Point(0, 24);
            this.dataGridViewObjectSetting.Name = "dataGridViewObjectSetting";
            this.dataGridViewObjectSetting.RowTemplate.Height = 21;
            this.dataGridViewObjectSetting.Size = new System.Drawing.Size(583, 181);
            this.dataGridViewObjectSetting.TabIndex = 1;
            this.dataGridViewObjectSetting.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewObjectSetting_CellContentClick);
            // 
            // headerType
            // 
            this.headerType.HeaderText = "Type";
            this.headerType.Items.AddRange(new object[] {
            "Fluid",
            "Rigid",
            "Obstacle"});
            this.headerType.Name = "headerType";
            this.headerType.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.headerType.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // headerPressure
            // 
            this.headerPressure.DataPropertyName = "pressureCoefficient";
            this.headerPressure.HeaderText = "Press";
            this.headerPressure.Name = "headerPressure";
            this.headerPressure.ToolTipText = "圧力";
            this.headerPressure.Width = 50;
            // 
            // headerViscosity
            // 
            this.headerViscosity.HeaderText = "Visc";
            this.headerViscosity.Name = "headerViscosity";
            this.headerViscosity.ToolTipText = "粘性";
            this.headerViscosity.Width = 50;
            // 
            // headerDensity
            // 
            this.headerDensity.HeaderText = "Density";
            this.headerDensity.Name = "headerDensity";
            this.headerDensity.ToolTipText = "密度";
            this.headerDensity.Width = 50;
            // 
            // MinX
            // 
            this.MinX.HeaderText = "MinX";
            this.MinX.Name = "MinX";
            this.MinX.Width = 40;
            // 
            // MaxX
            // 
            this.MaxX.HeaderText = "MaxX";
            this.MaxX.Name = "MaxX";
            this.MaxX.Width = 40;
            // 
            // MinY
            // 
            this.MinY.HeaderText = "MinY";
            this.MinY.Name = "MinY";
            this.MinY.Width = 40;
            // 
            // MaxY
            // 
            this.MaxY.HeaderText = "MaxY";
            this.MaxY.Name = "MaxY";
            this.MaxY.Width = 40;
            // 
            // MinZ
            // 
            this.MinZ.HeaderText = "MinZ";
            this.MinZ.Name = "MinZ";
            this.MinZ.Width = 40;
            // 
            // MaxZ
            // 
            this.MaxZ.HeaderText = "MaxZ";
            this.MaxZ.Name = "MaxZ";
            this.MaxZ.Width = 40;
            // 
            // Shape
            // 
            this.Shape.HeaderText = "Shape";
            this.Shape.Items.AddRange(new object[] {
            "Box",
            "Sphere"});
            this.Shape.Name = "Shape";
            this.Shape.Width = 50;
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(698, 209);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 15;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(607, 209);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 14;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnX,
            this.ColumnY,
            this.ColumnZ});
            this.dataGridView1.Location = new System.Drawing.Point(598, 24);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 21;
            this.dataGridView1.Size = new System.Drawing.Size(195, 68);
            this.dataGridView1.TabIndex = 18;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick_1);
            // 
            // ColumnX
            // 
            this.ColumnX.HeaderText = "X";
            this.ColumnX.Name = "ColumnX";
            this.ColumnX.Width = 50;
            // 
            // ColumnY
            // 
            this.ColumnY.HeaderText = "Y";
            this.ColumnY.Name = "ColumnY";
            this.ColumnY.Width = 50;
            // 
            // ColumnZ
            // 
            this.ColumnZ.HeaderText = "Z";
            this.ColumnZ.Name = "ColumnZ";
            this.ColumnZ.Width = 50;
            // 
            // textBoxEffectLength
            // 
            this.textBoxEffectLength.Location = new System.Drawing.Point(673, 158);
            this.textBoxEffectLength.Name = "textBoxEffectLength";
            this.textBoxEffectLength.Size = new System.Drawing.Size(100, 19);
            this.textBoxEffectLength.TabIndex = 22;
            this.textBoxEffectLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(589, 158);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 21;
            this.label3.Text = "ParticleSize";
            // 
            // textBoxTimeStep
            // 
            this.textBoxTimeStep.Location = new System.Drawing.Point(673, 123);
            this.textBoxTimeStep.Name = "textBoxTimeStep";
            this.textBoxTimeStep.Size = new System.Drawing.Size(100, 19);
            this.textBoxTimeStep.TabIndex = 20;
            this.textBoxTimeStep.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(589, 126);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 19;
            this.label1.Text = "TimeStep";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(589, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 23;
            this.label2.Text = "Bounary";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 12);
            this.label4.TabIndex = 24;
            this.label4.Text = "Object";
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(311, 209);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonAdd.TabIndex = 25;
            this.buttonAdd.Text = "Add";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(404, 209);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 26;
            this.buttonDelete.Text = "Delete";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // comboBoxExample
            // 
            this.comboBoxExample.FormattingEnabled = true;
            this.comboBoxExample.Items.AddRange(new object[] {
            "DamBreak1",
            "DamBreak2",
            "SphereBreak"});
            this.comboBoxExample.Location = new System.Drawing.Point(64, 209);
            this.comboBoxExample.Name = "comboBoxExample";
            this.comboBoxExample.Size = new System.Drawing.Size(121, 20);
            this.comboBoxExample.TabIndex = 27;
            this.comboBoxExample.Text = "Example";
            this.comboBoxExample.SelectedIndexChanged += new System.EventHandler(this.comboBoxExample_SelectedIndexChanged);
            // 
            // buttonCopy
            // 
            this.buttonCopy.Location = new System.Drawing.Point(221, 209);
            this.buttonCopy.Name = "buttonCopy";
            this.buttonCopy.Size = new System.Drawing.Size(75, 23);
            this.buttonCopy.TabIndex = 28;
            this.buttonCopy.Text = "Copy";
            this.buttonCopy.UseVisualStyleBackColor = true;
            this.buttonCopy.Click += new System.EventHandler(this.buttonCopy_Click);
            // 
            // PhysicsObjectSettingDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(805, 252);
            this.Controls.Add(this.buttonCopy);
            this.Controls.Add(this.comboBoxExample);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxEffectLength);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxTimeStep);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.dataGridViewObjectSetting);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "PhysicsObjectSettingDialog";
            this.Text = "PhysicsObjectSettingDialog";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PhysicsObjectSettingDialog_FormClosing);
            this.Load += new System.EventHandler(this.PhysicsObjectSettingDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewObjectSetting)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewObjectSetting;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnX;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnY;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnZ;
        private System.Windows.Forms.TextBox textBoxEffectLength;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxTimeStep;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DataGridViewComboBoxColumn headerType;
        private System.Windows.Forms.DataGridViewTextBoxColumn headerPressure;
        private System.Windows.Forms.DataGridViewTextBoxColumn headerViscosity;
        private System.Windows.Forms.DataGridViewTextBoxColumn headerDensity;
        private System.Windows.Forms.DataGridViewTextBoxColumn MinX;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxX;
        private System.Windows.Forms.DataGridViewTextBoxColumn MinY;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxY;
        private System.Windows.Forms.DataGridViewTextBoxColumn MinZ;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaxZ;
        private System.Windows.Forms.DataGridViewComboBoxColumn Shape;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.ComboBox comboBoxExample;
        private System.Windows.Forms.Button buttonCopy;

    }
}