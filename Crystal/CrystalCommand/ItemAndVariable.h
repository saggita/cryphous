#pragma once

namespace Crystal{
	namespace Command{

public ref class ItemAndVariable abstract : public System::Object
{
public:
	ItemAndVariable(void) : System::Object(){};
	virtual ~ItemAndVariable(void) {};
	virtual void applyToItem() abstract;
	virtual void applyToVariable() abstract;
};

ref class BoolCheckBox : public ItemAndVariable
{
public:
	BoolCheckBox(bool* boolean, System::Windows::Forms::CheckBox^ checkBox) :
	  ItemAndVariable() {
		this->boolean = boolean;
		this->checkBox = checkBox;

		applyToItem();
	}

	virtual ~BoolCheckBox() {};

	virtual void applyToItem() override {
		checkBox->Checked = *boolean;
	}

	virtual void applyToVariable() override {
		*boolean = checkBox->Checked;
	}


private:
	bool* boolean;
	System::Windows::Forms::CheckBox^ checkBox;
};

ref class IntTrackBar : public ItemAndVariable
{
public:
	IntTrackBar(int* integer, System::Windows::Forms::TrackBar^ trackBar) :
		ItemAndVariable() {
		this->integer = integer;
		this->trackBar = trackBar;
		applyToItem();
	}

	virtual ~IntTrackBar() {};

	virtual void applyToItem() override {
		trackBar->Value = System::Convert::ToInt32( *integer );
	}

	virtual void applyToVariable() override {
		*integer = System::Convert::ToInt32( trackBar->Value );
	}

private:
	int* integer;
	System::Windows::Forms::TrackBar^ trackBar;
};

ref class FloatTextBox : public ItemAndVariable
{
public:
	FloatTextBox(float* floatPrecise, System::Windows::Forms::TextBox^ textBox) :
	  ItemAndVariable() {
		  this->floatPrecise = floatPrecise;
		  this->textBox = textBox;
		  applyToItem();
	  }

	  virtual ~FloatTextBox() {};

	  virtual void applyToItem() override {
		  textBox->Text = (*floatPrecise).ToString();
	  }

	  virtual void applyToVariable() override {
		  if( textBox->Text == "") {
			  *floatPrecise = 0.0;
			  return;
		  }
		  *floatPrecise = float::Parse( textBox->Text );
	  }

private:
	float* floatPrecise;
	System::Windows::Forms::TextBox^ textBox;
};

ref class IntTextBox : public ItemAndVariable
{
public:
	IntTextBox(int* integer, System::Windows::Forms::TextBox^ textBox) :
	  ItemAndVariable() {
		  this->integer = integer;
		  this->textBox = textBox;
		  applyToItem();
	  }

	  virtual ~IntTextBox() {};

	  virtual void applyToItem() override {
		  textBox->Text = (*integer).ToString();
	  }

	  virtual void applyToVariable() override {
		  if( textBox->Text == "" ) {
			  *integer = 0;
			  return;
		  }
		  *integer = int::Parse( textBox->Text );
	  }

private:
	int* integer;
	System::Windows::Forms::TextBox^ textBox;
};

	}
}