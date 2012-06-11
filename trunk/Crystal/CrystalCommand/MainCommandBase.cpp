#include "MainCommandBase.h"

#include "ExportSettingCommand.h"
#include "GraphicsSettingCommand.h"
#include "FileIOCommand.h"
#include "AnimationCommandBase.h"
#include "ProfileInfoCommand.h"
#include "ApplicationSettings.h"

#include "../CrystalGraphics/Renderer.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"

#include <boost/foreach.hpp>

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Diagnostics;


MainCommandBase::MainCommandBase(System::Windows::Forms::PictureBox^ pictureBox)
{
	this->exportImagesSettingCommand = gcnew ExportSettingCommand("images", "png");
	this->profileExportSettingCommand = gcnew ExportSettingCommand("profiles", "csv");
	this->graphicsSettingCommand = gcnew GraphicsSettingCommand();
	this->fileIOCommand = gcnew FileIOCommand();
	this->profileInfoCommand = gcnew ProfileInfoCommand();
	this->pictureBox = pictureBox;

	ApplicationSettings::get()->renderer->setPictureBox( (HWND)(pictureBox->Handle.ToInt32()) );
}

MainCommandBase::~MainCommandBase(void)
{
}

void MainCommandBase::proceedSimulation()
{
	animationCommandBase->proceed();
	rendering();
}

void MainCommandBase::refreshSimulation()
{
	animationCommandBase->refresh();
	rendering();
}

void MainCommandBase::rendering()
{
	ApplicationSettings::get()->renderer->rendering( ApplicationSettings::get()->factory, pictureBox->Width, pictureBox->Height, ApplicationSettings::get()->simulationSetting->boundaryBox );
}

void MainCommandBase::displayInformation(System::Windows::Forms::ListBox^ listBox){
	profileInfoCommand->display( listBox );
}

void MainCommandBase::rotateX(int angle)
{
	GraphicsSettings::get()->angleX += angle;
	rendering();
}

void MainCommandBase::rotateY(int angle)
{
	GraphicsSettings::get()->angleY += angle;
	rendering();
}

void MainCommandBase::rotateZ(int angle)
{
	GraphicsSettings::get()->angleZ += angle;
	rendering();
}

void MainCommandBase::zoom(double zoom)
{
	GraphicsSettings::get()->zoom += zoom;
	rendering();
}

void MainCommandBase::move(double x, double y)
{
	GraphicsSettings::get()->cameraX += x;
	GraphicsSettings::get()->cameraY += y;
	rendering();
}

void MainCommandBase::viewReset()
{
	GraphicsSettings::get()->resetCameraAndAngle();
	rendering();
}