#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Crystal {
	namespace UI {

	public ref class GraphicsSettingForm : public System::Windows::Forms::Form
	{
	private:
		Command::MainCommandBase^ command;
	public:
		GraphicsSettingForm(Command::MainCommandBase^ command)
		{
			InitializeComponent();
			this->command = command;
		}

	protected:
		~GraphicsSettingForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::CheckBox^  checkBoxApplyPointSprite;

	private: System::Windows::Forms::TrackBar^  trackBarAlphaPower;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TrackBar^  trackBarPointSize;
	private: System::Windows::Forms::Label^  labelPointSize;






	private: System::Windows::Forms::CheckBox^  checkBoxBoundingBox;


	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->checkBoxApplyPointSprite = (gcnew System::Windows::Forms::CheckBox());
			this->trackBarAlphaPower = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->trackBarPointSize = (gcnew System::Windows::Forms::TrackBar());
			this->labelPointSize = (gcnew System::Windows::Forms::Label());
			this->checkBoxBoundingBox = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarAlphaPower))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarPointSize))->BeginInit();
			this->SuspendLayout();
			// 
			// checkBoxApplyPointSprite
			// 
			this->checkBoxApplyPointSprite->AutoSize = true;
			this->checkBoxApplyPointSprite->Location = System::Drawing::Point(220, 18);
			this->checkBoxApplyPointSprite->Name = L"checkBoxApplyPointSprite";
			this->checkBoxApplyPointSprite->Size = System::Drawing::Size(80, 16);
			this->checkBoxApplyPointSprite->TabIndex = 38;
			this->checkBoxApplyPointSprite->Text = L"PointSprite";
			this->checkBoxApplyPointSprite->UseVisualStyleBackColor = true;
			this->checkBoxApplyPointSprite->CheckedChanged += gcnew System::EventHandler(this, &GraphicsSettingForm::checkBoxApplyPointSprite_CheckedChanged);
			// 
			// trackBarAlphaPower
			// 
			this->trackBarAlphaPower->Location = System::Drawing::Point(78, 12);
			this->trackBarAlphaPower->Maximum = 100;
			this->trackBarAlphaPower->Name = L"trackBarAlphaPower";
			this->trackBarAlphaPower->Size = System::Drawing::Size(104, 45);
			this->trackBarAlphaPower->TabIndex = 36;
			this->trackBarAlphaPower->Value = 1;
			this->trackBarAlphaPower->Scroll += gcnew System::EventHandler(this, &GraphicsSettingForm::trackBarAlphaPower_Scroll);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(60, 12);
			this->label4->TabIndex = 35;
			this->label4->Text = L"PointAlpha";
			// 
			// trackBarPointSize
			// 
			this->trackBarPointSize->Location = System::Drawing::Point(78, 53);
			this->trackBarPointSize->Maximum = 100;
			this->trackBarPointSize->Minimum = 1;
			this->trackBarPointSize->Name = L"trackBarPointSize";
			this->trackBarPointSize->Size = System::Drawing::Size(104, 45);
			this->trackBarPointSize->TabIndex = 34;
			this->trackBarPointSize->Value = 1;
			this->trackBarPointSize->Scroll += gcnew System::EventHandler(this, &GraphicsSettingForm::trackBarPointSize_Scroll);
			// 
			// labelPointSize
			// 
			this->labelPointSize->AutoSize = true;
			this->labelPointSize->Location = System::Drawing::Point(13, 58);
			this->labelPointSize->Name = L"labelPointSize";
			this->labelPointSize->Size = System::Drawing::Size(52, 12);
			this->labelPointSize->TabIndex = 33;
			this->labelPointSize->Text = L"PointSize";
			// 
			// checkBoxBoundingBox
			// 
			this->checkBoxBoundingBox->AutoSize = true;
			this->checkBoxBoundingBox->Location = System::Drawing::Point(220, 58);
			this->checkBoxBoundingBox->Name = L"checkBoxBoundingBox";
			this->checkBoxBoundingBox->Size = System::Drawing::Size(91, 16);
			this->checkBoxBoundingBox->TabIndex = 63;
			this->checkBoxBoundingBox->Text = L"BoundingBox";
			this->checkBoxBoundingBox->UseVisualStyleBackColor = true;
			this->checkBoxBoundingBox->CheckedChanged += gcnew System::EventHandler(this, &GraphicsSettingForm::checkBoxBoundingBox_CheckedChanged);
			// 
			// GraphicsSettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(356, 93);
			this->Controls->Add(this->checkBoxBoundingBox);
			this->Controls->Add(this->checkBoxApplyPointSprite);
			this->Controls->Add(this->trackBarAlphaPower);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->trackBarPointSize);
			this->Controls->Add(this->labelPointSize);
			this->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->ForeColor = System::Drawing::SystemColors::InfoText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"GraphicsSettingForm";
			this->ShowInTaskbar = false;
			this->Text = L"GraphicsSettingForm";
			this->Load += gcnew System::EventHandler(this, &GraphicsSettingForm::GraphicsSettingForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarAlphaPower))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarPointSize))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void trackBarAlphaPower_Scroll(System::Object^  sender, System::EventArgs^  e) {
			command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }

private: System::Void trackBarPointSize_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarLineAlpha_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarLineWidth_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarLineLength_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void GraphicsSettingForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->setTrackBar(
					 trackBarPointSize,
					 trackBarAlphaPower,
					 checkBoxApplyPointSprite,
					 checkBoxBoundingBox);
		 }
private: System::Void checkBoxReactingOnly_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 	 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void checkBoxApplyPointSprite_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void buttonApply_Click(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarOffsetRed_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarOffsetGreen_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarOffsetBlue_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void checkBoxBoundingBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
private: System::Void trackBarBlurRatio_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 command->getGraphicsSettingCommand()->save();
			 command->rendering();
		 }
};
	}
}
