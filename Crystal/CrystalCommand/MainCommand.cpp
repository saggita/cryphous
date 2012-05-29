#include "MainCommand.h"

#include "ExportSettingCommand.h"
#include "SimulationSettingCommand.h"
#include "ObjectSettingCommand.h"
#include "BoundarySettingCommand.h"
#include "FileIOCommand.h"
#include "ParticleInfoCommand.h"
#include "SimulationCommand.h"
#include "ParticleExportCommand.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/ParticleFactory.h"

#include <map>

using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Diagnostics;


MainCommand::MainCommand(System::Windows::Forms::PictureBox^ pictureBox)
: MainCommandBase( pictureBox )
{
	this->simulationSettingCommand = gcnew SimulationSettingCommand();
	this->objectSettingCommand = gcnew ObjectSettingCommand();
	this->fileIOCommand = gcnew FileIOCommand();
	this->particleInfoCommand = gcnew ParticleInfoCommand();
	this->boundarySettingCommand = gcnew BoundarySettingCommand();
	this->animationCommandBase = gcnew SimulationCommand();
	this->particleExportSettingCommand = gcnew ExportSettingCommand("particles", "cparticles");
	this->particleExportCommand = gcnew ParticleExportCommand( particleExportSettingCommand );
}

MainCommand::~MainCommand(void)
{
}

void MainCommand::proceedSimulation()
{
	MainCommandBase::proceedSimulation();
	particleExportCommand->exportToFile( animationCommandBase->getStep() );
}