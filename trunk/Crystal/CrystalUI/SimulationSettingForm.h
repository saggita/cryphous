#pragma once

namespace Crystal {
	namespace UI {
		

	public ref class SimulationSettingForm : public System::Windows::Forms::Form
	{
	private:
		Command::SimulationSettingCommand^ command;

	public:
		SimulationSettingForm( Command::SimulationSettingCommand^ command ) {
			InitializeComponent();
			this->command = command;
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~SimulationSettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxTimeStep;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxEffectLength;




	protected: 

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxTimeStep = (gcnew System::Windows::Forms::TextBox());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxEffectLength = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"TimeStep";
			// 
			// textBoxTimeStep
			// 
			this->textBoxTimeStep->Location = System::Drawing::Point(105, 6);
			this->textBoxTimeStep->Name = L"textBoxTimeStep";
			this->textBoxTimeStep->Size = System::Drawing::Size(100, 19);
			this->textBoxTimeStep->TabIndex = 1;
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(25, 81);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 2;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &SimulationSettingForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->BackColor = System::Drawing::SystemColors::Control;
			this->buttonCancel->Location = System::Drawing::Point(105, 81);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 3;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &SimulationSettingForm::buttonCancel_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 44);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"EffectLength";
			// 
			// textBoxEffectLength
			// 
			this->textBoxEffectLength->Location = System::Drawing::Point(105, 44);
			this->textBoxEffectLength->Name = L"textBoxEffectLength";
			this->textBoxEffectLength->Size = System::Drawing::Size(100, 19);
			this->textBoxEffectLength->TabIndex = 7;
			// 
			// SimulationSettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(213, 112);
			this->Controls->Add(this->textBoxEffectLength);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->textBoxTimeStep);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"SimulationSettingForm";
			this->ShowInTaskbar = false;
			this->Text = L"SimulationSetting";
			this->Load += gcnew System::EventHandler(this, &SimulationSettingForm::SimulationSettingForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		System::Void SimulationSettingForm_Load(System::Object^  sender, System::EventArgs^  e) {
			command->setTextBox(textBoxTimeStep, textBoxEffectLength);
		}

		System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			Close();
		}

		System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
			command->save();
			Close();
		}
};

	}
}
