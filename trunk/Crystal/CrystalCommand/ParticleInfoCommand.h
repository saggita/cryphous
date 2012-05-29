#pragma once

namespace Crystal{
	namespace Command{

public ref class ParticleInfoCommand
{
public:
	ParticleInfoCommand(){};

	void display(System::Windows::Forms::DataGridView^ view);
};

	}
}
