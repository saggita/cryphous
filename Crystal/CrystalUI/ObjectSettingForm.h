#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Crystal {
	namespace UI {

public ref class ObjectSettingForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Button^  buttonAdd;
	private: System::Windows::Forms::Button^  buttonDelete;
	private: System::Windows::Forms::DataGridViewComboBoxColumn^  headerType;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  headerPressure;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  headerViscosity;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  headerDensity;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMinX;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMaxX;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMaxY;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMinY;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMinZ;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMaxZ;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnDivideLength;






































































	private:
		Command::ObjectSettingCommand^ command;

	public:
		ObjectSettingForm(Command::ObjectSettingCommand^ command) {
			InitializeComponent();
			this->command = command;
		}

	protected:
		
		~ObjectSettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::DataGridView^  dataGridViewObjectSetting;
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
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->dataGridViewObjectSetting = (gcnew System::Windows::Forms::DataGridView());
			this->buttonAdd = (gcnew System::Windows::Forms::Button());
			this->buttonDelete = (gcnew System::Windows::Forms::Button());
			this->headerType = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->headerPressure = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->headerViscosity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->headerDensity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMinX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMaxX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMaxY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMinY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMinZ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMaxZ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnDivideLength = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridViewObjectSetting))->BeginInit();
			this->SuspendLayout();
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(385, 165);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 1;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &ObjectSettingForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Location = System::Drawing::Point(466, 165);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 2;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &ObjectSettingForm::buttonCancel_Click);
			// 
			// dataGridViewObjectSetting
			// 
			this->dataGridViewObjectSetting->AllowUserToAddRows = false;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridViewObjectSetting->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridViewObjectSetting->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewObjectSetting->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(11) {this->headerType, 
				this->headerPressure, this->headerViscosity, this->headerDensity, this->ColumnMinX, this->ColumnMaxX, this->ColumnMaxY, this->ColumnMinY, 
				this->ColumnMinZ, this->ColumnMaxZ, this->ColumnDivideLength});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewObjectSetting->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridViewObjectSetting->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridViewObjectSetting->Location = System::Drawing::Point(0, 0);
			this->dataGridViewObjectSetting->Name = L"dataGridViewObjectSetting";
			this->dataGridViewObjectSetting->RowTemplate->Height = 21;
			this->dataGridViewObjectSetting->Size = System::Drawing::Size(613, 191);
			this->dataGridViewObjectSetting->TabIndex = 0;
			// 
			// buttonAdd
			// 
			this->buttonAdd->Location = System::Drawing::Point(109, 165);
			this->buttonAdd->Name = L"buttonAdd";
			this->buttonAdd->Size = System::Drawing::Size(75, 23);
			this->buttonAdd->TabIndex = 12;
			this->buttonAdd->Text = L"Add";
			this->buttonAdd->UseVisualStyleBackColor = true;
			this->buttonAdd->Click += gcnew System::EventHandler(this, &ObjectSettingForm::buttonAdd_Click);
			// 
			// buttonDelete
			// 
			this->buttonDelete->Location = System::Drawing::Point(190, 165);
			this->buttonDelete->Name = L"buttonDelete";
			this->buttonDelete->Size = System::Drawing::Size(75, 23);
			this->buttonDelete->TabIndex = 13;
			this->buttonDelete->Text = L"Delete";
			this->buttonDelete->UseVisualStyleBackColor = true;
			this->buttonDelete->Click += gcnew System::EventHandler(this, &ObjectSettingForm::buttonDelete_Click);
			// 
			// headerType
			// 
			this->headerType->HeaderText = L"Type";
			this->headerType->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Fluid", L"Obstacle", L"Rigid"});
			this->headerType->Name = L"headerType";
			this->headerType->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->headerType->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			// 
			// headerPressure
			// 
			this->headerPressure->DataPropertyName = L"pressureCoefficient";
			this->headerPressure->HeaderText = L"Pressure";
			this->headerPressure->Name = L"headerPressure";
			this->headerPressure->Width = 60;
			// 
			// headerViscosity
			// 
			this->headerViscosity->HeaderText = L"Viscosity";
			this->headerViscosity->Name = L"headerViscosity";
			this->headerViscosity->Width = 60;
			// 
			// headerDensity
			// 
			this->headerDensity->HeaderText = L"Density";
			this->headerDensity->Name = L"headerDensity";
			this->headerDensity->Width = 60;
			// 
			// ColumnMinX
			// 
			this->ColumnMinX->HeaderText = L"MinX";
			this->ColumnMinX->Name = L"ColumnMinX";
			this->ColumnMinX->Width = 40;
			// 
			// ColumnMaxX
			// 
			this->ColumnMaxX->HeaderText = L"MaxX";
			this->ColumnMaxX->Name = L"ColumnMaxX";
			this->ColumnMaxX->Width = 40;
			// 
			// ColumnMaxY
			// 
			this->ColumnMaxY->HeaderText = L"MaxY";
			this->ColumnMaxY->Name = L"ColumnMaxY";
			this->ColumnMaxY->Width = 40;
			// 
			// ColumnMinY
			// 
			this->ColumnMinY->HeaderText = L"MinY";
			this->ColumnMinY->Name = L"ColumnMinY";
			this->ColumnMinY->Width = 40;
			// 
			// ColumnMinZ
			// 
			this->ColumnMinZ->HeaderText = L"MinZ";
			this->ColumnMinZ->Name = L"ColumnMinZ";
			this->ColumnMinZ->Width = 40;
			// 
			// ColumnMaxZ
			// 
			this->ColumnMaxZ->HeaderText = L"MaxZ";
			this->ColumnMaxZ->Name = L"ColumnMaxZ";
			this->ColumnMaxZ->Width = 40;
			// 
			// ColumnDivideLength
			// 
			this->ColumnDivideLength->HeaderText = L"Divide";
			this->ColumnDivideLength->Name = L"ColumnDivideLength";
			this->ColumnDivideLength->Width = 50;
			// 
			// ObjectSettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(613, 191);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->buttonDelete);
			this->Controls->Add(this->buttonAdd);
			this->Controls->Add(this->dataGridViewObjectSetting);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ObjectSettingForm";
			this->ShowInTaskbar = false;
			this->Text = L"ObjectSetting";
			this->Load += gcnew System::EventHandler(this, &ObjectSettingForm::ObjectSettingForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridViewObjectSetting))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
		private:
			System::Void ObjectSettingForm_Load(System::Object^  sender, System::EventArgs^  e){
				command->setView( this->dataGridViewObjectSetting );
				command->displaySettings( );
			}

			System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
				command->saveSettings();
				Close();
			}

			System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
				Close();
			}

			System::Void buttonAdd_Click(System::Object^  sender, System::EventArgs^  e) {
				command->addObject();
			}
			
			System::Void buttonDelete_Click(System::Object^  sender, System::EventArgs^  e) {
				command->deleteObject();
			}
};
	}
}
