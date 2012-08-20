#include "MainCommand.h"

#include "ParticleInfoCommand.h"
#include "SimulationCommand.h"
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


MainCommand::MainCommand(System::Windows::Forms::PictureBox^ pictureBox, System::String^ productName)
{
	this->simulationCommand = gcnew SimulationCommand();
	this->graphicsSettingCommand = gcnew GraphicsSettingCommand();
	this->profileInfoCommand = gcnew ProfileInfoCommand();
	this->pictureBox = pictureBox;
	this->productName = productName;

	ApplicationSettings::get()->renderer->setPictureBox( (HWND)(pictureBox->Handle.ToInt32()) );
}

MainCommand::~MainCommand(void)
{
}

void MainCommand::proceedSimulation()
{
	simulationCommand->proceed();
	rendering();
}

void MainCommand::refreshSimulation()
{
	simulationCommand->refresh();
	rendering();
}

void MainCommand::rendering()
{
	ApplicationSettings::get()->renderer->rendering( ApplicationSettings::get()->factory, pictureBox->Width, pictureBox->Height, ApplicationSettings::get()->simulationSetting->boundaryBox );
}

void MainCommand::displayInformation( System::Windows::Forms::ListBox^ listBox){
	profileInfoCommand->display( productName, listBox );
}

void MainCommand::rotateX(int angle)
{
	ApplicationSettings::get()->graphicsSettings->angleX += angle;
	rendering();
}

void MainCommand::rotateY(int angle)
{
	ApplicationSettings::get()->graphicsSettings->angleY += angle;
	rendering();
}

void MainCommand::rotateZ(int angle)
{
	ApplicationSettings::get()->graphicsSettings->angleZ += angle;
	rendering();
}

void MainCommand::zoom(float zoom)
{
	ApplicationSettings::get()->graphicsSettings->zoom += zoom;
	rendering();
}

void MainCommand::move(float x, float y)
{
	ApplicationSettings::get()->graphicsSettings->cameraX += x;
	ApplicationSettings::get()->graphicsSettings->cameraY += y;
	rendering();
}

void MainCommand::viewReset()
{
	ApplicationSettings::get()->graphicsSettings->resetCameraAndAngle();
	rendering();
}