#include "ProfileInfoCommand.h"

#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "ApplicationSettings.h"

#include "StringMarshaler.h"

#include <fstream>

using namespace Crystal::Physics;
using namespace Crystal::Command;

ProfileInfoCommand::ProfileInfoCommand(void)
{
}

void ProfileInfoCommand::display(System::Windows::Forms::ListBox^ listBox)
{
	listBox->Items->Clear();
	listBox->Items->Add("CrystalUI 1.2");
	listBox->Items->Add("(c) 2012 Kuroro");
	listBox->Items->Add(" ");
	listBox->Items->Add("Particles = " + ApplicationSettings::get()->factory->getSortedParticles().size() );
	listBox->Items->Add("Step = " + Simulation::get()->getStep() );
	listBox->Items->Add("Time = " + Simulation::get()->getSimulationTime() );
	listBox->Items->Add(" ");

	std::map< std::string, double>& strAndTimes = Profiler::get()->getStrAndTimes();
	for( std::map< std::string, double>::const_iterator iter = strAndTimes.begin(); iter != strAndTimes.end(); ++iter ) {
		System::String^ str = gcnew System::String( iter->first.c_str()  );
		listBox->Items->Add( str + "=" + iter->second );
	}
}