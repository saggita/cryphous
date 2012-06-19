namespace Cryphous
{
    partial class ParticleObserveDialog
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.ColumnID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnObjectID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnMass = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnDensity = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnPositionX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnPositionY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnPositionZ = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnID,
            this.ColumnObjectID,
            this.ColumnMass,
            this.ColumnDensity,
            this.ColumnPositionX,
            this.ColumnPositionY,
            this.ColumnPositionZ});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridView1.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView1.Location = new System.Drawing.Point(0, 0);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView1.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.dataGridView1.RowTemplate.Height = 21;
            this.dataGridView1.Size = new System.Drawing.Size(393, 481);
            this.dataGridView1.TabIndex = 1;
            // 
            // ColumnID
            // 
            this.ColumnID.HeaderText = "ID";
            this.ColumnID.Name = "ColumnID";
            this.ColumnID.ReadOnly = true;
            this.ColumnID.Width = 50;
            // 
            // ColumnObjectID
            // 
            this.ColumnObjectID.HeaderText = "ObjectID";
            this.ColumnObjectID.Name = "ColumnObjectID";
            this.ColumnObjectID.ReadOnly = true;
            this.ColumnObjectID.Width = 50;
            // 
            // ColumnMass
            // 
            this.ColumnMass.HeaderText = "Mass";
            this.ColumnMass.Name = "ColumnMass";
            this.ColumnMass.ReadOnly = true;
            this.ColumnMass.Width = 50;
            // 
            // ColumnDensity
            // 
            this.ColumnDensity.HeaderText = "Density";
            this.ColumnDensity.Name = "ColumnDensity";
            this.ColumnDensity.ReadOnly = true;
            this.ColumnDensity.Width = 50;
            // 
            // ColumnPositionX
            // 
            this.ColumnPositionX.HeaderText = "X";
            this.ColumnPositionX.Name = "ColumnPositionX";
            this.ColumnPositionX.ReadOnly = true;
            this.ColumnPositionX.Width = 50;
            // 
            // ColumnPositionY
            // 
            this.ColumnPositionY.HeaderText = "Y";
            this.ColumnPositionY.Name = "ColumnPositionY";
            this.ColumnPositionY.ReadOnly = true;
            this.ColumnPositionY.Width = 50;
            // 
            // ColumnPositionZ
            // 
            this.ColumnPositionZ.HeaderText = "Z";
            this.ColumnPositionZ.Name = "ColumnPositionZ";
            this.ColumnPositionZ.ReadOnly = true;
            this.ColumnPositionZ.Width = 50;
            // 
            // ParticleObserveDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(393, 481);
            this.Controls.Add(this.dataGridView1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ParticleObserveDialog";
            this.Text = "ParticleObserveDialog";
            this.Load += new System.EventHandler(this.ParticleObserveDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnID;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnObjectID;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnMass;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnDensity;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnPositionX;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnPositionY;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnPositionZ;
    }
}