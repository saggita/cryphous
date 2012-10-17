#include "Command.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/LightSourceFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/LightSource.h"
#include "../CrystalGraphics/Renderer.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System;
using namespace System::Xml;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

Command::Command(System::Windows::Forms::PictureBox^ pictureBox)
{
	this->pictureBox = pictureBox;

	factory = new PhysicsObjectFactory;
	simulation = new Simulation;
	simulationSetting = new SimulationSetting;
	lightSourceFactory = new LightSourceFactory;
	graphicsSettings = new GraphicsSettings;
	renderer = new Renderer(*graphicsSettings);
	conditions = new std::list<PhysicsObjectCondition>;
	renderer->setPictureBox( (HWND)(pictureBox->Handle.ToInt32()) );
}

Command::~Command()
{
	delete lightSourceFactory;
	delete graphicsSettings;
	delete conditions;
	delete renderer;
	delete simulationSetting;
	delete simulation;
	delete factory;
}

void Command::clearConditions()
{
	conditions->clear();
}

void Command::refresh()
{
	factory->init();
	for( std::list<PhysicsObjectCondition>::iterator iter = conditions->begin(); iter != conditions->end(); ++iter ) {
		factory->createPhysicsObject((*iter), *simulationSetting);
	}
	lightSourceFactory->init();

	renderer->init();	
	simulation->init();
	Profiler::get()->init();
}

float Command::getParticleDiameter()
{
	return simulationSetting->particleDiameter;
}

void Command::setParticleDiameter(const float diameter)
{
	simulationSetting->particleDiameter = diameter;
}

unsigned int Command::createPhysicsObject(String^ type, const float density, const float pressureCoe, const float viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Geom::Vector3d> points = convertToNative(managedPositions);
	
	PhysicsObjectCondition::ObjectType objectType = PhysicsObjectCondition::Fluid;
	if(  type == "Fluid") {
		objectType = PhysicsObjectCondition::Fluid;
	}
	else if( type == "Obstacle" ) {
		objectType = PhysicsObjectCondition::Obstacle;
	}
	else if( type == "Rigid") {
		objectType = PhysicsObjectCondition::Rigid;
	}
	else if( type == "Elastic") {
		objectType = PhysicsObjectCondition::Elastic;
	}
	else{
		Debug::Assert( false );
	}

	PhysicsObjectCondition* condition = new PhysicsObjectCondition( points, density, pressureCoe, viscosityCoe, objectType );
	conditions->push_back( *condition );
	return factory->createPhysicsObject( *condition,  *(simulationSetting) )->getID();
}

void Command::addParticles(unsigned int index, System::Collections::Generic::List<ManagedPosition^> ^managedPosition, System::Collections::Generic::List<ManagedPosition^> ^managedVelocity)
{
	if( factory->getPhysicsObjects().size() <= index ) {
		return;
	}
	std::vector<Geom::Vector3d> points = convertToNative(managedPosition);
	std::vector<Geom::Vector3d> velocities = convertToNative(managedVelocity);

	factory->addParticles(index, points, velocities );
}

void Command::proceed()
{
	simulation->simulate( factory, lightSourceFactory, *(simulationSetting) );
	rendering();
}

int Command::getStep()
{
	return simulation->getStep();
}

void Command::displayBoundarySetting(System::Windows::Forms::DataGridView^ view)
{
	view->Rows->Clear();

	const Box& box = simulationSetting->boundaryBox;

	array<Object^>^ minData = {
		box.getMinX(), box.getMinY(), box.getMinZ()
	};
	view->Rows->Add( minData );

	array<Object^>^ maxData = {
		box.getMaxX(), box.getMaxY(), box.getMaxZ()
	};
	view->Rows->Add( maxData );
}

void Command::saveBoundarySetting(System::Windows::Forms::DataGridView^ view)
{
	const float minX = Convert::ToSingle( view->Rows[0]->Cells[0]->Value );
	const float minY = Convert::ToSingle( view->Rows[0]->Cells[1]->Value );
	const float minZ = Convert::ToSingle( view->Rows[0]->Cells[2]->Value );

	const float maxX = Convert::ToSingle( view->Rows[1]->Cells[0]->Value );
	const float maxY = Convert::ToSingle( view->Rows[1]->Cells[1]->Value );
	const float maxZ = Convert::ToSingle( view->Rows[1]->Cells[2]->Value );

	simulationSetting->boundaryBox = Box( Crystal::Geom::Vector3d( minX, minY, minZ), Crystal::Geom::Vector3d( maxX, maxY, maxZ) );
}

void Command::setExternalForce(float x, float y, float z)
{
	simulationSetting->externalForce = Vector3d( x, y, z );
}

void Command::setGraphicsSetting(int pointSize, int pointAlpha, int lineSize, int lineAlpha)
{
	graphicsSettings->pointSize = pointSize;
	graphicsSettings->pointAlpha = pointAlpha;
	graphicsSettings->lineSize = lineSize;
	graphicsSettings->lineAlpha = lineAlpha;
}

void Command::rendering()
{
	renderer->rendering( factory, lightSourceFactory, pictureBox->Width, pictureBox->Height, simulationSetting->boundaryBox );
}

void Command::rotateX(int angle)
{
	graphicsSettings->angleX += angle;
	rendering();
}

void Command::rotateY(int angle)
{
	graphicsSettings->angleY += angle;
	rendering();
}

void Command::rotateZ(int angle)
{
	graphicsSettings->angleZ += angle;
	rendering();
}

void Command::zoom(float zoom)
{
	graphicsSettings->zoom += zoom;
	rendering();
}

void Command::move(float x, float y)
{
	graphicsSettings->cameraX += x;
	graphicsSettings->cameraY += y;
	rendering();
}

void Command::viewReset()
{
	graphicsSettings->resetCameraAndAngle();
	rendering();
}

void Command::displayProfile(System::Windows::Forms::ListBox^ listBox)
{
	listBox->Items->Clear();
	listBox->Items->Add("Particles = " + factory->getParticles().size() );
	listBox->Items->Add("Photons = " + lightSourceFactory->getPhotons().size() );
	listBox->Items->Add("Step = " + simulation->getStep() );
	listBox->Items->Add("Time = " + simulation->getSimulationTime() );
	listBox->Items->Add(" ");

	std::map< std::string, double>& strAndTimes = Profiler::get()->getStrAndTimes();
	for( std::map< std::string, double>::const_iterator iter = strAndTimes.begin(); iter != strAndTimes.end(); ++iter ) {
		System::String^ str = gcnew System::String( iter->first.c_str()  );
		listBox->Items->Add( str + "=" + iter->second );
	}
}

void Command::displayParticles(System::Windows::Forms::DataGridView^ view)
{
	view->Rows->Clear();

	const ParticleVector& particles = factory->getParticles();
	
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		Particle* particle = *iter;

		array<Object^>^ rowData = {
					particle->getID(),
					particle->getMass(),
					particle->density,
					particle->center.getX(),
					particle->center.getY(),
					particle->center.getZ()
				};
			
		view->Rows->Add( rowData );
	}
}

void Command::setSimulationSetting(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength )
{
	(simulationSetting->timeStep) = float::Parse( textBoxTimeStep->Text );
	(simulationSetting->particleDiameter) = float::Parse( textBoxEffectLength->Text );
}

void Command::displaySimulationSetting(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength )
{
	textBoxTimeStep->Text = (simulationSetting->timeStep).ToString();
	textBoxEffectLength->Text = (simulationSetting->particleDiameter).ToString();
}

std::vector<Vector3d> Command::convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Vector3d> nativePositions;
	
	for each(ManagedPosition^ pos in managedPositions) {
		nativePositions.push_back( Vector3d( pos[0], pos[1], pos[2] ) );
	}

	assert( managedPositions->Count == nativePositions.size() );
	return nativePositions;
}

void Command::setLightSourceSetting(const float posX, const float posY, const float posZ, const float dirX, const float dirY, const float dirZ)
{
	const Vector3d center( posX, posY, posZ );
	lightSourceFactory->createLightSource( center );
}