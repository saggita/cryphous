#include "MainCommand.h"

#include "ExportSettingCommand.h"
#include "SimulationSettingCommand.h"
#include "ObjectSettingCommand.h"
#include "BoundarySettingCommand.h"
#include "FileIOCommand.h"
#include "ParticleInfoCommand.h"
#include "SimulationCommand.h"
#include "ParticleExportCommand.h"
#include "GraphicsSettingCommand.h"
#include "ProfileInfoCommand.h"
#include "ApplicationSettings.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/ParticleFactory.h"

#include "../CrystalGraphics/Renderer.h"
#include "../CrystalGraphics/GraphicsSettings.h"

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Diagnostics;


MainCommand::MainCommand(System::Windows::Forms::PictureBox^ pictureBox)
{
	this->simulationSettingCommand = gcnew SimulationSettingCommand();
	this->objectSettingCommand = gcnew ObjectSettingCommand();
	this->fileIOCommand = gcnew FileIOCommand();
	this->particleInfoCommand = gcnew ParticleInfoCommand();
	this->boundarySettingCommand = gcnew BoundarySettingCommand();
	this->animationCommandBase = gcnew SimulationCommand();
	this->particleExportSettingCommand = gcnew ExportSettingCommand("particles", "cparticles");
	this->particleExportCommand = gcnew ParticleExportCommand( particleExportSettingCommand );
	this->graphicsSettingCommand = gcnew GraphicsSettingCommand();
	this->fileIOCommand = gcnew FileIOCommand();
	this->profileInfoCommand = gcnew ProfileInfoCommand();
	this->pictureBox = pictureBox;

	ApplicationSettings::get()->renderer->setPictureBox( (HWND)(pictureBox->Handle.ToInt32()) );
}

MainCommand::~MainCommand(void)
{
}

void MainCommand::proceedSimulation()
{
	animationCommandBase->proceed();
	rendering();
	particleExportCommand->exportToFile( animationCommandBase->getStep() );
}

void MainCommand::refreshSimulation()
{
	animationCommandBase->refresh();
	rendering();
}

void MainCommand::rendering()
{
	ApplicationSettings::get()->renderer->rendering( ApplicationSettings::get()->factory, pictureBox->Width, pictureBox->Height, ApplicationSettings::get()->simulationSetting->boundaryBox );
}

void MainCommand::displayInformation(System::Windows::Forms::ListBox^ listBox){
	profileInfoCommand->display( listBox );
}

void MainCommand::rotateX(int angle)
{
	GraphicsSettings::get()->angleX += angle;
	rendering();
}

void MainCommand::rotateY(int angle)
{
	GraphicsSettings::get()->angleY += angle;
	rendering();
}

void MainCommand::rotateZ(int angle)
{
	GraphicsSettings::get()->angleZ += angle;
	rendering();
}

void MainCommand::zoom(double zoom)
{
	GraphicsSettings::get()->zoom += zoom;
	rendering();
}

void MainCommand::move(double x, double y)
{
	GraphicsSettings::get()->cameraX += x;
	GraphicsSettings::get()->cameraY += y;
	rendering();
}

void MainCommand::viewReset()
{
	GraphicsSettings::get()->resetCameraAndAngle();
	rendering();
}