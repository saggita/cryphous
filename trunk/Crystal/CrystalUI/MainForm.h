#pragma once

namespace Crystal {
	namespace UI {

public ref class MainForm : public System::Windows::Forms::Form
{
private:
	Command::MainCommand^ command;
	System::Drawing::Point previousPoint;
	bool isLeftDown;
	bool isRightDown;

private: 
	System::Windows::Forms::Button^  buttonSimulationRefresh;
	System::Windows::Forms::ListBox^  listBoxInformation;
	System::Windows::Forms::MenuStrip^  menuStrip1;
	System::Windows::Forms::ToolStripMenuItem^  settingsToolStripMenuItem;

	System::Windows::Forms::ToolStripMenuItem^  objectSettingToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^  fileSToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemOpen;
	System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemSave;
	System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemSaveAs;



private: System::Windows::Forms::ToolStripMenuItem^  boundarySettingBToolStripMenuItem;














private: System::Windows::Forms::Button^  buttonViewReset;
private: System::Windows::Forms::ToolStripMenuItem^  sToolStripMenuItem;


private: System::Windows::Forms::ToolStripMenuItem^  exportParticleEToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  graphicsSettingGToolStripMenuItem;
private: System::Windows::Forms::Button^  buttonParticleInfo;

		 System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemClose;

public:
	MainForm(void);

protected:
	~MainForm();

private:
	System::Void buttonNextStep_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void timerSimulation_Tick(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonSimulationRefresh_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void simulationSettingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void objectSettingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void toolStripMenuItemOpen_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void toolStripMenuItemSaveAs_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void toolStripMenuItemSave_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void toolStripMenuItemClose_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MainForm_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	System::Void MainForm_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	System::Void particleInfoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void objectInfoOToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

private:
	System::Windows::Forms::Panel^  panelMainOperation; 
	System::Windows::Forms::PictureBox^  pictureBox1;
	System::Windows::Forms::Button^  buttonNextStep;
	System::Windows::Forms::Timer^  timerSimulation;
	System::ComponentModel::IContainer^  components;
	System::Windows::Forms::Button^  buttonStart;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
	/// コード エディタで変更しないでください。
	/// </summary>
	void InitializeComponent(void)
	{
		this->components = (gcnew System::ComponentModel::Container());
		this->panelMainOperation = (gcnew System::Windows::Forms::Panel());
		this->buttonParticleInfo = (gcnew System::Windows::Forms::Button());
		this->buttonViewReset = (gcnew System::Windows::Forms::Button());
		this->listBoxInformation = (gcnew System::Windows::Forms::ListBox());
		this->buttonSimulationRefresh = (gcnew System::Windows::Forms::Button());
		this->buttonStart = (gcnew System::Windows::Forms::Button());
		this->buttonNextStep = (gcnew System::Windows::Forms::Button());
		this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		this->timerSimulation = (gcnew System::Windows::Forms::Timer(this->components));
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->fileSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItemOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItemSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItemSaveAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItemClose = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->graphicsSettingGToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->objectSettingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->boundarySettingBToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->sToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->exportParticleEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->panelMainOperation->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
		this->menuStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// panelMainOperation
		// 
		this->panelMainOperation->Controls->Add(this->buttonParticleInfo);
		this->panelMainOperation->Controls->Add(this->buttonViewReset);
		this->panelMainOperation->Controls->Add(this->listBoxInformation);
		this->panelMainOperation->Controls->Add(this->buttonSimulationRefresh);
		this->panelMainOperation->Controls->Add(this->buttonStart);
		this->panelMainOperation->Controls->Add(this->buttonNextStep);
		this->panelMainOperation->Dock = System::Windows::Forms::DockStyle::Right;
		this->panelMainOperation->Location = System::Drawing::Point(800, 26);
		this->panelMainOperation->Name = L"panelMainOperation";
		this->panelMainOperation->Size = System::Drawing::Size(124, 450);
		this->panelMainOperation->TabIndex = 0;
		// 
		// buttonParticleInfo
		// 
		this->buttonParticleInfo->Location = System::Drawing::Point(0, 221);
		this->buttonParticleInfo->Name = L"buttonParticleInfo";
		this->buttonParticleInfo->Size = System::Drawing::Size(124, 23);
		this->buttonParticleInfo->TabIndex = 6;
		this->buttonParticleInfo->Text = L"MoreInfo";
		this->buttonParticleInfo->UseVisualStyleBackColor = true;
		this->buttonParticleInfo->Click += gcnew System::EventHandler(this, &MainForm::buttonParticleInfo_Click);
		// 
		// buttonViewReset
		// 
		this->buttonViewReset->Location = System::Drawing::Point(0, 328);
		this->buttonViewReset->Name = L"buttonViewReset";
		this->buttonViewReset->Size = System::Drawing::Size(124, 23);
		this->buttonViewReset->TabIndex = 5;
		this->buttonViewReset->Text = L"ViewReset";
		this->buttonViewReset->UseVisualStyleBackColor = true;
		this->buttonViewReset->Click += gcnew System::EventHandler(this, &MainForm::buttonViewReset_Click);
		// 
		// listBoxInformation
		// 
		this->listBoxInformation->FormattingEnabled = true;
		this->listBoxInformation->ItemHeight = 12;
		this->listBoxInformation->Location = System::Drawing::Point(0, 0);
		this->listBoxInformation->Name = L"listBoxInformation";
		this->listBoxInformation->Size = System::Drawing::Size(124, 244);
		this->listBoxInformation->TabIndex = 4;
		// 
		// buttonSimulationRefresh
		// 
		this->buttonSimulationRefresh->Location = System::Drawing::Point(0, 357);
		this->buttonSimulationRefresh->Name = L"buttonSimulationRefresh";
		this->buttonSimulationRefresh->Size = System::Drawing::Size(124, 23);
		this->buttonSimulationRefresh->TabIndex = 2;
		this->buttonSimulationRefresh->Text = L"Refresh";
		this->buttonSimulationRefresh->UseVisualStyleBackColor = true;
		this->buttonSimulationRefresh->Click += gcnew System::EventHandler(this, &MainForm::buttonSimulationRefresh_Click);
		// 
		// buttonStart
		// 
		this->buttonStart->Location = System::Drawing::Point(0, 386);
		this->buttonStart->Name = L"buttonStart";
		this->buttonStart->Size = System::Drawing::Size(124, 23);
		this->buttonStart->TabIndex = 1;
		this->buttonStart->Text = L"Start";
		this->buttonStart->UseVisualStyleBackColor = true;
		this->buttonStart->Click += gcnew System::EventHandler(this, &MainForm::buttonStart_Click);
		// 
		// buttonNextStep
		// 
		this->buttonNextStep->Location = System::Drawing::Point(0, 415);
		this->buttonNextStep->Name = L"buttonNextStep";
		this->buttonNextStep->Size = System::Drawing::Size(124, 23);
		this->buttonNextStep->TabIndex = 0;
		this->buttonNextStep->Text = L"NextStep";
		this->buttonNextStep->UseVisualStyleBackColor = true;
		this->buttonNextStep->Click += gcnew System::EventHandler(this, &MainForm::buttonNextStep_Click);
		// 
		// pictureBox1
		// 
		this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pictureBox1->Location = System::Drawing::Point(0, 26);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(800, 450);
		this->pictureBox1->TabIndex = 1;
		this->pictureBox1->TabStop = false;
		this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox1_MouseDown);
		this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox1_MouseMove);
		this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox1_MouseUp);
		// 
		// timerSimulation
		// 
		this->timerSimulation->Interval = 1;
		this->timerSimulation->Tick += gcnew System::EventHandler(this, &MainForm::timerSimulation_Tick);
		// 
		// menuStrip1
		// 
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileSToolStripMenuItem, 
			this->settingsToolStripMenuItem});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(924, 26);
		this->menuStrip1->TabIndex = 2;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// fileSToolStripMenuItem
		// 
		this->fileSToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripMenuItemOpen, 
			this->toolStripMenuItemSave, this->toolStripMenuItemSaveAs, this->toolStripMenuItemClose});
		this->fileSToolStripMenuItem->Name = L"fileSToolStripMenuItem";
		this->fileSToolStripMenuItem->Size = System::Drawing::Size(57, 22);
		this->fileSToolStripMenuItem->Text = L"File(&F)";
		// 
		// toolStripMenuItemOpen
		// 
		this->toolStripMenuItemOpen->Name = L"toolStripMenuItemOpen";
		this->toolStripMenuItemOpen->Size = System::Drawing::Size(137, 22);
		this->toolStripMenuItemOpen->Text = L"Open(&O)";
		this->toolStripMenuItemOpen->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuItemOpen_Click);
		// 
		// toolStripMenuItemSave
		// 
		this->toolStripMenuItemSave->Name = L"toolStripMenuItemSave";
		this->toolStripMenuItemSave->Size = System::Drawing::Size(137, 22);
		this->toolStripMenuItemSave->Text = L"Save(&S)";
		this->toolStripMenuItemSave->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuItemSave_Click);
		// 
		// toolStripMenuItemSaveAs
		// 
		this->toolStripMenuItemSaveAs->Name = L"toolStripMenuItemSaveAs";
		this->toolStripMenuItemSaveAs->Size = System::Drawing::Size(137, 22);
		this->toolStripMenuItemSaveAs->Text = L"SaveAs(&A)";
		this->toolStripMenuItemSaveAs->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuItemSaveAs_Click);
		// 
		// toolStripMenuItemClose
		// 
		this->toolStripMenuItemClose->Name = L"toolStripMenuItemClose";
		this->toolStripMenuItemClose->Size = System::Drawing::Size(137, 22);
		this->toolStripMenuItemClose->Text = L"Close(&C)";
		this->toolStripMenuItemClose->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuItemClose_Click);
		// 
		// settingsToolStripMenuItem
		// 
		this->settingsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->graphicsSettingGToolStripMenuItem, 
			this->objectSettingToolStripMenuItem, this->boundarySettingBToolStripMenuItem, this->sToolStripMenuItem, this->exportParticleEToolStripMenuItem});
		this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
		this->settingsToolStripMenuItem->Size = System::Drawing::Size(86, 22);
		this->settingsToolStripMenuItem->Text = L"Settings(&S)";
		// 
		// graphicsSettingGToolStripMenuItem
		// 
		this->graphicsSettingGToolStripMenuItem->Name = L"graphicsSettingGToolStripMenuItem";
		this->graphicsSettingGToolStripMenuItem->Size = System::Drawing::Size(216, 22);
		this->graphicsSettingGToolStripMenuItem->Text = L"GraphicsSetting(&G)";
		this->graphicsSettingGToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::graphicsSettingGToolStripMenuItem_Click);
		// 
		// objectSettingToolStripMenuItem
		// 
		this->objectSettingToolStripMenuItem->Name = L"objectSettingToolStripMenuItem";
		this->objectSettingToolStripMenuItem->Size = System::Drawing::Size(216, 22);
		this->objectSettingToolStripMenuItem->Text = L"ObjectSetting(&O)";
		this->objectSettingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::objectSettingToolStripMenuItem_Click);
		// 
		// boundarySettingBToolStripMenuItem
		// 
		this->boundarySettingBToolStripMenuItem->Name = L"boundarySettingBToolStripMenuItem";
		this->boundarySettingBToolStripMenuItem->Size = System::Drawing::Size(216, 22);
		this->boundarySettingBToolStripMenuItem->Text = L"BoundarySetting(&B)";
		this->boundarySettingBToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::boundarySettingBToolStripMenuItem_Click);
		// 
		// sToolStripMenuItem
		// 
		this->sToolStripMenuItem->Name = L"sToolStripMenuItem";
		this->sToolStripMenuItem->Size = System::Drawing::Size(216, 22);
		this->sToolStripMenuItem->Text = L"SimulationSetting(&S)";
		this->sToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::sToolStripMenuItem_Click);
		// 
		// exportParticleEToolStripMenuItem
		// 
		this->exportParticleEToolStripMenuItem->Name = L"exportParticleEToolStripMenuItem";
		this->exportParticleEToolStripMenuItem->Size = System::Drawing::Size(216, 22);
		this->exportParticleEToolStripMenuItem->Text = L"ExportParticleSetting(&E)";
		this->exportParticleEToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exportParticleEToolStripMenuItem_Click);
		// 
		// MainForm
		// 
		this->AllowDrop = true;
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->ClientSize = System::Drawing::Size(924, 476);
		this->Controls->Add(this->pictureBox1);
		this->Controls->Add(this->panelMainOperation);
		this->Controls->Add(this->menuStrip1);
		this->KeyPreview = true;
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"MainForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"CrystalUI";
		this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
		this->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::MainForm_DragDrop);
		this->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::MainForm_DragEnter);
		this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
		this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MainForm_MouseMove);
		this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MainForm_MouseWheel);
		this->panelMainOperation->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion
private: System::Void boundarySettingBToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void saveImagesIToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void simulationSettingSToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MainForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void MainForm_MouseWheel(System::Object^ , System::Windows::Forms::MouseEventArgs^ e);
private: System::Void MainForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) { };
private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void buttonViewReset_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void sToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void exportParticleEToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void graphicsSettingGToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void buttonParticleInfo_Click(System::Object^  sender, System::EventArgs^  e);
};

	}
}