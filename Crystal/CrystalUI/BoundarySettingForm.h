#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Crystal {
	namespace UI {

	/// 境界条件設定用フォーム
	public ref class BoundarySettingForm : public System::Windows::Forms::Form
	{
	private:
		Command::BoundarySettingCommand^ command;

	public:
		BoundarySettingForm(Command::BoundarySettingCommand^ command)
		{
			InitializeComponent();
			this->command = command;
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~BoundarySettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnX;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnY;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnZ;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;



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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnZ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->ColumnX, 
				this->ColumnY, this->ColumnZ});
			this->dataGridView1->Location = System::Drawing::Point(9, 11);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowTemplate->Height = 21;
			this->dataGridView1->Size = System::Drawing::Size(195, 68);
			this->dataGridView1->TabIndex = 0;
			// 
			// ColumnX
			// 
			this->ColumnX->HeaderText = L"X";
			this->ColumnX->Name = L"ColumnX";
			this->ColumnX->Width = 50;
			// 
			// ColumnY
			// 
			this->ColumnY->HeaderText = L"Y";
			this->ColumnY->Name = L"ColumnY";
			this->ColumnY->Width = 50;
			// 
			// ColumnZ
			// 
			this->ColumnZ->HeaderText = L"Z";
			this->ColumnZ->Name = L"ColumnZ";
			this->ColumnZ->Width = 50;
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(25, 85);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 1;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &BoundarySettingForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Location = System::Drawing::Point(106, 85);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 2;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &BoundarySettingForm::buttonCancel_Click);
			// 
			// BoundarySettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(205, 120);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->dataGridView1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"BoundarySettingForm";
			this->ShowInTaskbar = false;
			this->Text = L"BoundarySettingForm";
			this->Load += gcnew System::EventHandler(this, &BoundarySettingForm::BoundarySettingForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
				 command->saveBoundarySetting( this->dataGridView1 );
				 this->Close();
			}
	private: System::Void BoundarySettingForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 command->displayBoundarySetting( this->dataGridView1 );
			 }
};

	}	// namespace UI
}	// namespace Crystal
