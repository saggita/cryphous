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
		class LightSourceFactory;
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

	void clearLights();

	void refresh();

	float getParticleDiameter();

	void setParticleDiameter(const float diameter);

	unsigned int createPhysicsObject(System::String^ type, const float density, const float pressureCoe, const float viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPosition);

	void addParticles(unsigned int index, System::Collections::Generic::List<ManagedPosition^>^ managedPosition, System::Collections::Generic::List<ManagedPosition^>^ managedVelocity);

	void proceed();

	int getStep();

	void clearConditions();

	void displayBoundarySetting(System::Windows::Forms::DataGridView^ view);

	void saveBoundarySetting(System::Windows::Forms::DataGridView^ view);

	void setExternalForce(float x, float y, float z);

	void setGraphicsSetting(int pointSize, int pointAlpha, int photonSize, int photonAlpha, int lineSize, int lineAlpha, bool showAbsorbedPhotons, bool showBoundaryBox);

	void rendering();

	void rotateX(int angle);

	void rotateY(int angle);

	void rotateZ(int angle);

	void zoom(float zoom);

	void move(float x, float y);

	void viewReset();

	void displayProfile(System::Windows::Forms::ListBox^ listBox);

	void setSimulationSetting(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength );

	void displaySimulationSetting(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength );

	void setLightSourceSetting(const float posX, const float posY, const float posZ, size_t howManyPhotons, const float velocity);

	void exportParticles(System::String^ fileName);

public:
	Physics::PhysicsObjectFactory* factory;
	Physics::SimulationSetting* simulationSetting;
	Physics::Simulation* simulation;
	Physics::LightSourceFactory* lightSourceFactory;
	Graphics::Renderer* renderer;
	Graphics::GraphicsSettings* graphicsSettings;
	std::list<Physics::PhysicsObjectCondition>* conditions;
	System::Windows::Forms::PictureBox^ pictureBox;

private:
	std::vector<Geom::Vector3d> convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions);
};

	}
}