namespace Cryphous
{
    partial class MainForm
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
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.settingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.objectSettingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.externalForceEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listBoxInformation = new System.Windows.Forms.ListBox();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.buttonStart = new System.Windows.Forms.Button();
            this.timerSimulation = new System.Windows.Forms.Timer(this.components);
            this.buttonNextStep = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.buttonRenderingTest = new System.Windows.Forms.Button();
            this.buttonViewReset = new System.Windows.Forms.Button();
            this.graphicsSettingGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.settingToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(767, 26);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // settingToolStripMenuItem
            // 
            this.settingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.objectSettingToolStripMenuItem,
            this.externalForceEToolStripMenuItem,
            this.graphicsSettingGToolStripMenuItem});
            this.settingToolStripMenuItem.Name = "settingToolStripMenuItem";
            this.settingToolStripMenuItem.Size = new System.Drawing.Size(86, 22);
            this.settingToolStripMenuItem.Text = "Settings(&S)";
            // 
            // objectSettingToolStripMenuItem
            // 
            this.objectSettingToolStripMenuItem.Name = "objectSettingToolStripMenuItem";
            this.objectSettingToolStripMenuItem.Size = new System.Drawing.Size(187, 22);
            this.objectSettingToolStripMenuItem.Text = "ObjectSetting(&O)";
            this.objectSettingToolStripMenuItem.Click += new System.EventHandler(this.objectSettingToolStripMenuItem_Click);
            // 
            // externalForceEToolStripMenuItem
            // 
            this.externalForceEToolStripMenuItem.Name = "externalForceEToolStripMenuItem";
            this.externalForceEToolStripMenuItem.Size = new System.Drawing.Size(187, 22);
            this.externalForceEToolStripMenuItem.Text = "ExternalForce(&E)";
            this.externalForceEToolStripMenuItem.Click += new System.EventHandler(this.externalForceEToolStripMenuItem_Click);
            // 
            // listBoxInformation
            // 
            this.listBoxInformation.FormattingEnabled = true;
            this.listBoxInformation.ItemHeight = 12;
            this.listBoxInformation.Location = new System.Drawing.Point(3, 0);
            this.listBoxInformation.Name = "listBoxInformation";
            this.listBoxInformation.Size = new System.Drawing.Size(120, 256);
            this.listBoxInformation.TabIndex = 4;
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(3, 338);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(120, 25);
            this.buttonRefresh.TabIndex = 2;
            this.buttonRefresh.Text = "Refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(3, 379);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(120, 23);
            this.buttonStart.TabIndex = 1;
            this.buttonStart.Text = "Start";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // timerSimulation
            // 
            this.timerSimulation.Interval = 1;
            this.timerSimulation.Tick += new System.EventHandler(this.timerSimulation_Tick);
            // 
            // buttonNextStep
            // 
            this.buttonNextStep.Location = new System.Drawing.Point(3, 420);
            this.buttonNextStep.Name = "buttonNextStep";
            this.buttonNextStep.Size = new System.Drawing.Size(120, 23);
            this.buttonNextStep.TabIndex = 5;
            this.buttonNextStep.Text = "NestStep";
            this.buttonNextStep.UseVisualStyleBackColor = true;
            this.buttonNextStep.Click += new System.EventHandler(this.buttonNextStep_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(640, 480);
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 26);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.pictureBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.buttonRenderingTest);
            this.splitContainer1.Panel2.Controls.Add(this.buttonViewReset);
            this.splitContainer1.Panel2.Controls.Add(this.listBoxInformation);
            this.splitContainer1.Panel2.Controls.Add(this.buttonRefresh);
            this.splitContainer1.Panel2.Controls.Add(this.buttonStart);
            this.splitContainer1.Panel2.Controls.Add(this.buttonNextStep);
            this.splitContainer1.Size = new System.Drawing.Size(767, 480);
            this.splitContainer1.SplitterDistance = 640;
            this.splitContainer1.TabIndex = 7;
            // 
            // buttonRenderingTest
            // 
            this.buttonRenderingTest.Location = new System.Drawing.Point(1, 228);
            this.buttonRenderingTest.Name = "buttonRenderingTest";
            this.buttonRenderingTest.Size = new System.Drawing.Size(120, 25);
            this.buttonRenderingTest.TabIndex = 7;
            this.buttonRenderingTest.Text = "RenderingTest";
            this.buttonRenderingTest.UseVisualStyleBackColor = true;
            this.buttonRenderingTest.Click += new System.EventHandler(this.buttonRenderingTest_Click);
            // 
            // buttonViewReset
            // 
            this.buttonViewReset.Location = new System.Drawing.Point(3, 295);
            this.buttonViewReset.Name = "buttonViewReset";
            this.buttonViewReset.Size = new System.Drawing.Size(120, 25);
            this.buttonViewReset.TabIndex = 6;
            this.buttonViewReset.Text = "ViewReset";
            this.buttonViewReset.UseVisualStyleBackColor = true;
            this.buttonViewReset.Click += new System.EventHandler(this.buttonViewReset_Click);
            // 
            // graphicsSettingGToolStripMenuItem
            // 
            this.graphicsSettingGToolStripMenuItem.Name = "graphicsSettingGToolStripMenuItem";
            this.graphicsSettingGToolStripMenuItem.Size = new System.Drawing.Size(187, 22);
            this.graphicsSettingGToolStripMenuItem.Text = "GraphicsSetting(&G)";
            this.graphicsSettingGToolStripMenuItem.Click += new System.EventHandler(this.graphicsSettingGToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(767, 506);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.KeyPreview = true;
            this.Name = "MainForm";
            this.Text = "Cryphous";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainForm_KeyDown);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem settingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem objectSettingToolStripMenuItem;
        private System.Windows.Forms.ListBox listBoxInformation;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Timer timerSimulation;
        private System.Windows.Forms.Button buttonNextStep;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button buttonViewReset;
        private System.Windows.Forms.Button buttonRenderingTest;
        private System.Windows.Forms.ToolStripMenuItem externalForceEToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem graphicsSettingGToolStripMenuItem;
    }
}