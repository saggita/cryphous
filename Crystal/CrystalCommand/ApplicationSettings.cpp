#include "ApplicationSettings.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalGraphics/Renderer.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System;
using namespace System::Xml;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

ApplicationSettings::ApplicationSettings(System::Windows::Forms::PictureBox^ pictureBox)
{
	this->graphicsSettingCommand = gcnew GraphicsSettingCommand(this);
	this->pictureBox = pictureBox;

	factory = new PhysicsObjectFactory;
	simulation = new Simulation;
	simulationSetting = new SimulationSetting;
	graphicsSettings = new GraphicsSettings;
	renderer = new Renderer(*graphicsSettings);
	conditions = new std::list<PhysicsObjectCondition>;
	renderer->setPictureBox( (HWND)(pictureBox->Handle.ToInt32()) );
}

ApplicationSettings::~ApplicationSettings()
{
	delete graphicsSettings;
	delete conditions;
	delete renderer;
	delete simulationSetting;
	delete simulation;
	delete factory;
}

void ApplicationSettings::refresh()
{
	factory->init();
	for( std::list<PhysicsObjectCondition>::iterator iter = conditions->begin(); iter != conditions->end(); ++iter ) {
		factory->createPhysicsObject((*iter), *simulationSetting);
	}
	renderer->init();	
	simulation->init();
	Profiler::get()->init();
}

float ApplicationSettings::getParticleDiameter()
{
	return simulationSetting->particleDiameter;
}

void ApplicationSettings::setParticleDiameter(const float diameter)
{
	simulationSetting->particleDiameter = diameter;
}

void ApplicationSettings::createPhysicsObject(String^ type, const float density, const float pressureCoe, const float viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Geom::Vector3d> points = ParticleMarshaler::convertToNative(managedPositions);

	const Box& box = simulationSetting->boundaryBox;

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
	else{
		Debug::Assert( false );
	}

	PhysicsObjectCondition* condition = new PhysicsObjectCondition(
		points,
		density,
		pressureCoe,
		viscosityCoe,
		objectType
		);
	factory->createPhysicsObject( *condition,  *(simulationSetting) );
	conditions->push_back( *condition );
}

void ApplicationSettings::addParticles(int index, System::Collections::Generic::List<ManagedPosition^> ^managedPosition, System::Collections::Generic::List<ManagedPosition^> ^managedVelocity)
{
	std::vector<Geom::Vector3d> points = ParticleMarshaler::convertToNative(managedPosition);
	std::vector<Geom::Vector3d> velocities = ParticleMarshaler::convertToNative(managedVelocity);

	factory->addParticles(index, points, velocities );
}

void ApplicationSettings::proceed()
{
	simulation->simulate( factory, *(simulationSetting) );
	rendering();
}

int ApplicationSettings::getStep()
{
	return simulation->getStep();
}

List<ManagedPosition^>^ ApplicationSettings::getManagedPositions()
{
	const ParticleVector& nativeParticles = factory->getParticles();
	return ParticleMarshaler::convertToManagedPositions( nativeParticles );
}

List<ManagedVector^>^ ApplicationSettings::getManagedNormals()
{
	const ParticleVector& nativeParticles = factory->getParticles();
	return ParticleMarshaler::convertToManagedNormals( nativeParticles );
}

void ApplicationSettings::displayBoundarySetting(System::Windows::Forms::DataGridView^ view)
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

void ApplicationSettings::saveBoundarySetting(System::Windows::Forms::DataGridView^ view)
{
	const float minX = Convert::ToSingle( view->Rows[0]->Cells[0]->Value );
	const float minY = Convert::ToSingle( view->Rows[0]->Cells[1]->Value );
	const float minZ = Convert::ToSingle( view->Rows[0]->Cells[2]->Value );

	const float maxX = Convert::ToSingle( view->Rows[1]->Cells[0]->Value );
	const float maxY = Convert::ToSingle( view->Rows[1]->Cells[1]->Value );
	const float maxZ = Convert::ToSingle( view->Rows[1]->Cells[2]->Value );

	simulationSetting->boundaryBox = Box( Crystal::Geom::Vector3d( minX, minY, minZ), Crystal::Geom::Vector3d( maxX, maxY, maxZ) );
}

void ApplicationSettings::rendering()
{
	renderer->rendering( factory, pictureBox->Width, pictureBox->Height, simulationSetting->boundaryBox );
}

void ApplicationSettings::rotateX(int angle)
{
	graphicsSettings->angleX += angle;
	rendering();
}

void ApplicationSettings::rotateY(int angle)
{
	graphicsSettings->angleY += angle;
	rendering();
}

void ApplicationSettings::rotateZ(int angle)
{
	graphicsSettings->angleZ += angle;
	rendering();
}

void ApplicationSettings::zoom(float zoom)
{
	graphicsSettings->zoom += zoom;
	rendering();
}

void ApplicationSettings::move(float x, float y)
{
	graphicsSettings->cameraX += x;
	graphicsSettings->cameraY += y;
	rendering();
}

void ApplicationSettings::viewReset()
{
	graphicsSettings->resetCameraAndAngle();
	rendering();
}

void ApplicationSettings::displayProfile(System::Windows::Forms::ListBox^ listBox)
{
	listBox->Items->Clear();
	listBox->Items->Add("Cryphous");
	listBox->Items->Add("Powered by");
	listBox->Items->Add("Crystal 1.6");
	listBox->Items->Add("(c) 2012 Kuroro");
	listBox->Items->Add(" ");
	listBox->Items->Add("Particles = " + factory->getParticles().size() );
	listBox->Items->Add("Step = " + simulation->getStep() );
	listBox->Items->Add("Time = " + simulation->getSimulationTime() );
	listBox->Items->Add(" ");

	std::map< std::string, double>& strAndTimes = Profiler::get()->getStrAndTimes();
	for( std::map< std::string, double>::const_iterator iter = strAndTimes.begin(); iter != strAndTimes.end(); ++iter ) {
		System::String^ str = gcnew System::String( iter->first.c_str()  );
		listBox->Items->Add( str + "=" + iter->second );
	}
}

void ApplicationSettings::displayParticles(System::Windows::Forms::DataGridView^ view)
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
