#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Crystal {
	namespace UI {

	public ref class ExportSettingForm : public System::Windows::Forms::Form
	{
	private:
		Command::ExportSettingCommand^ command;
	public:
		ExportSettingForm(Command::ExportSettingCommand^ command)
		{
			InitializeComponent();
			this->command = command;
			command->setTextBox(this->textBoxOutputInterval,
				this->textBoxOutputFile);
			command->display();
		}

	protected:
		~ExportSettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxOutputInterval;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxOutputFile;
	private: System::Windows::Forms::Button^  buttonFileSet;
	private: System::Windows::Forms::Button^  buttonFileReset;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxOutputInterval = (gcnew System::Windows::Forms::TextBox());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxOutputFile = (gcnew System::Windows::Forms::TextBox());
			this->buttonFileSet = (gcnew System::Windows::Forms::Button());
			this->buttonFileReset = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(30, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"OutputInterval";
			// 
			// textBoxOutputInterval
			// 
			this->textBoxOutputInterval->Location = System::Drawing::Point(140, 12);
			this->textBoxOutputInterval->Name = L"textBoxOutputInterval";
			this->textBoxOutputInterval->Size = System::Drawing::Size(100, 19);
			this->textBoxOutputInterval->TabIndex = 1;
			this->textBoxOutputInterval->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(59, 95);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 2;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &ExportSettingForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Location = System::Drawing::Point(142, 95);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 3;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &ExportSettingForm::buttonCancel_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 12);
			this->label2->TabIndex = 4;
			this->label2->Text = L"OutputFile";
			// 
			// textBoxOutputFile
			// 
			this->textBoxOutputFile->Location = System::Drawing::Point(140, 41);
			this->textBoxOutputFile->Name = L"textBoxOutputFile";
			this->textBoxOutputFile->Size = System::Drawing::Size(100, 19);
			this->textBoxOutputFile->TabIndex = 5;
			// 
			// buttonFileSet
			// 
			this->buttonFileSet->Location = System::Drawing::Point(140, 66);
			this->buttonFileSet->Name = L"buttonFileSet";
			this->buttonFileSet->Size = System::Drawing::Size(54, 23);
			this->buttonFileSet->TabIndex = 6;
			this->buttonFileSet->Text = L"Set";
			this->buttonFileSet->UseVisualStyleBackColor = true;
			this->buttonFileSet->Click += gcnew System::EventHandler(this, &ExportSettingForm::buttonFileSet_Click);
			// 
			// buttonFileReset
			// 
			this->buttonFileReset->Location = System::Drawing::Point(200, 66);
			this->buttonFileReset->Name = L"buttonFileReset";
			this->buttonFileReset->Size = System::Drawing::Size(54, 23);
			this->buttonFileReset->TabIndex = 7;
			this->buttonFileReset->Text = L"Reset";
			this->buttonFileReset->UseVisualStyleBackColor = true;
			this->buttonFileReset->Click += gcnew System::EventHandler(this, &ExportSettingForm::button2_Click);
			// 
			// ExportSettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(284, 125);
			this->Controls->Add(this->buttonFileReset);
			this->Controls->Add(this->buttonFileSet);
			this->Controls->Add(this->textBoxOutputFile);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->textBoxOutputInterval);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ExportSettingForm";
			this->ShowInTaskbar = false;
			this->Text = L"ExportSettingForm";
			this->Load += gcnew System::EventHandler(this, &ExportSettingForm::ExportSettingForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void ExportSettingForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			command->resetFileName();
			command->display();
		 }

private: System::Void buttonFileSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 command->setFileName();
			 command->display();
		 }

private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
			 command->save();
			 this->Close();
		 }
};

	}
}