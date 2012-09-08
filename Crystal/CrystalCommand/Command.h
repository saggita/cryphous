#pragma once

#include <vector>
#include <list>

namespace Crystal {
	namespace Geom{
		class Vector3d;
	}
	namespace Physics {
		class PhysicsObjectFactory;
		struct PhysicsObjectCondition;
		class SimulationSetting;
		class Simulation;
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
	}
	namespace Graphics {
		class Renderer;
		class GraphicsSettings;
	}

	namespace Command {
		typedef array< float > ManagedPosition;
		typedef array< float > ManagedVector;

public ref class Command
{	
public:
	Command(System::Windows::Forms::PictureBox^ pictureBox);

	~Command();

	void refresh();

	float getParticleDiameter();

	void setParticleDiameter(const float diameter);

	void createPhysicsObject(System::String^ type, const float density, const float pressureCoe, const float viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPosition);

	void addParticles(int index, System::Collections::Generic::List<ManagedPosition^>^ managedPosition, System::Collections::Generic::List<ManagedPosition^>^ managedVelocity);

	void proceed();

	int getStep();

	void clearConditions();

	System::Collections::Generic::List<ManagedPosition^>^ getManagedPositions();

	System::Collections::Generic::List<ManagedVector^>^ getManagedNormals();

	void displayBoundarySetting(System::Windows::Forms::DataGridView^ view);

	void saveBoundarySetting(System::Windows::Forms::DataGridView^ view);

	void rendering();

	void rotateX(int angle);

	void rotateY(int angle);

	void rotateZ(int angle);

	void zoom(float zoom);

	void move(float x, float y);

	void viewReset();

	void displayParticles(System::Windows::Forms::DataGridView^ view);

	void displayProfile(System::Windows::Forms::ListBox^ listBox);

	void setSimulationSetting(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength );

	void displaySimulationSetting(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength );

private:
	Physics::PhysicsObjectFactory* factory;
	Physics::SimulationSetting* simulationSetting;
	Physics::Simulation* simulation;
	Graphics::Renderer* renderer;
	Graphics::GraphicsSettings* graphicsSettings;
	std::list<Physics::PhysicsObjectCondition>* conditions;
	System::Windows::Forms::PictureBox^ pictureBox;

private:
	System::Collections::Generic::List<ManagedPosition^>^ convertToManagedPositions(const Physics::ParticleVector& nativeParticles);

	System::Collections::Generic::List<ManagedVector^>^ convertToManagedNormals(const Physics::ParticleVector& nativeParticles);

	std::vector<Geom::Vector3d> convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions);
};

	}
}