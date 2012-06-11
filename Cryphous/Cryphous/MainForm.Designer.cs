﻿namespace Cryphous
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
            this.fileSToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemSave = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemClose = new System.Windows.Forms.ToolStripMenuItem();
            this.settingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.simulationSettingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.objectSettingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.boundarySettingBToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.particleInfoPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listBoxInformation = new System.Windows.Forms.ListBox();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.buttonStart = new System.Windows.Forms.Button();
            this.timerSimulation = new System.Windows.Forms.Timer(this.components);
            this.buttonNextStep = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileSToolStripMenuItem,
            this.settingToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(589, 26);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileSToolStripMenuItem
            // 
            this.fileSToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItemOpen,
            this.toolStripMenuItemSave,
            this.toolStripMenuItemSaveAs,
            this.toolStripMenuItemClose});
            this.fileSToolStripMenuItem.Name = "fileSToolStripMenuItem";
            this.fileSToolStripMenuItem.Size = new System.Drawing.Size(57, 22);
            this.fileSToolStripMenuItem.Text = "File(&F)";
            // 
            // toolStripMenuItemOpen
            // 
            this.toolStripMenuItemOpen.Name = "toolStripMenuItemOpen";
            this.toolStripMenuItemOpen.Size = new System.Drawing.Size(137, 22);
            this.toolStripMenuItemOpen.Text = "Open(&O)";
            this.toolStripMenuItemOpen.Click += new System.EventHandler(this.toolStripMenuItemOpen_Click);
            // 
            // toolStripMenuItemSave
            // 
            this.toolStripMenuItemSave.Name = "toolStripMenuItemSave";
            this.toolStripMenuItemSave.Size = new System.Drawing.Size(137, 22);
            this.toolStripMenuItemSave.Text = "Save(&S)";
            this.toolStripMenuItemSave.Click += new System.EventHandler(this.toolStripMenuItemSave_Click);
            // 
            // toolStripMenuItemSaveAs
            // 
            this.toolStripMenuItemSaveAs.Name = "toolStripMenuItemSaveAs";
            this.toolStripMenuItemSaveAs.Size = new System.Drawing.Size(137, 22);
            this.toolStripMenuItemSaveAs.Text = "SaveAs(&A)";
            this.toolStripMenuItemSaveAs.Click += new System.EventHandler(this.toolStripMenuItemSaveAs_Click);
            // 
            // toolStripMenuItemClose
            // 
            this.toolStripMenuItemClose.Name = "toolStripMenuItemClose";
            this.toolStripMenuItemClose.Size = new System.Drawing.Size(137, 22);
            this.toolStripMenuItemClose.Text = "Close(&C)";
            this.toolStripMenuItemClose.Click += new System.EventHandler(this.toolStripMenuItemClose_Click);
            // 
            // settingToolStripMenuItem
            // 
            this.settingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.simulationSettingToolStripMenuItem,
            this.objectSettingToolStripMenuItem,
            this.boundarySettingBToolStripMenuItem,
            this.particleInfoPToolStripMenuItem});
            this.settingToolStripMenuItem.Name = "settingToolStripMenuItem";
            this.settingToolStripMenuItem.Size = new System.Drawing.Size(86, 22);
            this.settingToolStripMenuItem.Text = "Settings(&S)";
            // 
            // simulationSettingToolStripMenuItem
            // 
            this.simulationSettingToolStripMenuItem.Name = "simulationSettingToolStripMenuItem";
            this.simulationSettingToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.simulationSettingToolStripMenuItem.Text = "SimulationSetting(&S)";
            this.simulationSettingToolStripMenuItem.Click += new System.EventHandler(this.simulationSettingToolStripMenuItem_Click);
            // 
            // objectSettingToolStripMenuItem
            // 
            this.objectSettingToolStripMenuItem.Name = "objectSettingToolStripMenuItem";
            this.objectSettingToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.objectSettingToolStripMenuItem.Text = "ObjectSetting(&O)";
            this.objectSettingToolStripMenuItem.Click += new System.EventHandler(this.objectSettingToolStripMenuItem_Click);
            // 
            // boundarySettingBToolStripMenuItem
            // 
            this.boundarySettingBToolStripMenuItem.Name = "boundarySettingBToolStripMenuItem";
            this.boundarySettingBToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.boundarySettingBToolStripMenuItem.Text = "BoundarySetting(&B)";
            this.boundarySettingBToolStripMenuItem.Click += new System.EventHandler(this.boundarySettingBToolStripMenuItem_Click);
            // 
            // particleInfoPToolStripMenuItem
            // 
            this.particleInfoPToolStripMenuItem.Name = "particleInfoPToolStripMenuItem";
            this.particleInfoPToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.particleInfoPToolStripMenuItem.Text = "ParticleInfo(&P)";
            this.particleInfoPToolStripMenuItem.Click += new System.EventHandler(this.particleInfoPToolStripMenuItem_Click);
            // 
            // listBoxInformation
            // 
            this.listBoxInformation.FormattingEnabled = true;
            this.listBoxInformation.ItemHeight = 12;
            this.listBoxInformation.Location = new System.Drawing.Point(12, 157);
            this.listBoxInformation.Name = "listBoxInformation";
            this.listBoxInformation.Size = new System.Drawing.Size(273, 256);
            this.listBoxInformation.TabIndex = 4;
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(12, 48);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(273, 25);
            this.buttonRefresh.TabIndex = 2;
            this.buttonRefresh.Text = "Refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(12, 79);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(273, 23);
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
            this.buttonNextStep.Location = new System.Drawing.Point(12, 108);
            this.buttonNextStep.Name = "buttonNextStep";
            this.buttonNextStep.Size = new System.Drawing.Size(273, 23);
            this.buttonNextStep.TabIndex = 5;
            this.buttonNextStep.Text = "NestStep";
            this.buttonNextStep.UseVisualStyleBackColor = true;
            this.buttonNextStep.Click += new System.EventHandler(this.buttonNextStep_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(345, 79);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(151, 244);
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(589, 418);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.buttonNextStep);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.listBoxInformation);
            this.Controls.Add(this.menuStrip1);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileSToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemOpen;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemSave;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemSaveAs;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemClose;
        private System.Windows.Forms.ToolStripMenuItem settingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem simulationSettingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem objectSettingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem boundarySettingBToolStripMenuItem;
        private System.Windows.Forms.ListBox listBoxInformation;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Timer timerSimulation;
        private System.Windows.Forms.Button buttonNextStep;
        private System.Windows.Forms.ToolStripMenuItem particleInfoPToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}