#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Crystal {
	namespace UI {

	public ref class ParticleObserveForm : public System::Windows::Forms::Form
	{
	private:
		Command::ParticleInfoCommand^ command;
	public:
		ParticleObserveForm(Command::ParticleInfoCommand^ command)
		{
			InitializeComponent();
			this->command = command;
		}

		System::Void onDisplay() {
			command->display( dataGridView1);
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~ParticleObserveForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnObjectID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMass;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnDensity;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnPositionX;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnPositionY;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnPositionZ;




























































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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnObjectID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMass = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnDensity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnPositionX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnPositionY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnPositionZ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->ColumnID, 
				this->ColumnObjectID, this->ColumnMass, this->ColumnDensity, this->ColumnPositionX, this->ColumnPositionY, this->ColumnPositionZ});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView1->Location = System::Drawing::Point(0, 0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->dataGridView1->RowTemplate->Height = 21;
			this->dataGridView1->Size = System::Drawing::Size(402, 355);
			this->dataGridView1->TabIndex = 0;
			// 
			// ColumnID
			// 
			this->ColumnID->HeaderText = L"ID";
			this->ColumnID->Name = L"ColumnID";
			this->ColumnID->ReadOnly = true;
			this->ColumnID->Width = 50;
			// 
			// ColumnObjectID
			// 
			this->ColumnObjectID->HeaderText = L"Parent";
			this->ColumnObjectID->Name = L"ColumnObjectID";
			this->ColumnObjectID->ReadOnly = true;
			this->ColumnObjectID->Width = 50;
			// 
			// ColumnMass
			// 
			this->ColumnMass->HeaderText = L"Mass";
			this->ColumnMass->Name = L"ColumnMass";
			this->ColumnMass->ReadOnly = true;
			this->ColumnMass->Width = 50;
			// 
			// ColumnDensity
			// 
			this->ColumnDensity->HeaderText = L"Density";
			this->ColumnDensity->Name = L"ColumnDensity";
			this->ColumnDensity->ReadOnly = true;
			this->ColumnDensity->Width = 50;
			// 
			// ColumnPositionX
			// 
			this->ColumnPositionX->HeaderText = L"X";
			this->ColumnPositionX->Name = L"ColumnPositionX";
			this->ColumnPositionX->ReadOnly = true;
			this->ColumnPositionX->Width = 50;
			// 
			// ColumnPositionY
			// 
			this->ColumnPositionY->HeaderText = L"Y";
			this->ColumnPositionY->Name = L"ColumnPositionY";
			this->ColumnPositionY->ReadOnly = true;
			this->ColumnPositionY->Width = 50;
			// 
			// ColumnPositionZ
			// 
			this->ColumnPositionZ->HeaderText = L"Z";
			this->ColumnPositionZ->Name = L"ColumnPositionZ";
			this->ColumnPositionZ->ReadOnly = true;
			this->ColumnPositionZ->Width = 50;
			// 
			// ParticleObserveForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(402, 355);
			this->Controls->Add(this->dataGridView1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"ParticleObserveForm";
			this->ShowInTaskbar = false;
			this->Text = L"ParticleObserveForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void buttonUpdate_Click(System::Object^  sender, System::EventArgs^  e) {
				 command->display( dataGridView1);
			 }
};
	}
}
