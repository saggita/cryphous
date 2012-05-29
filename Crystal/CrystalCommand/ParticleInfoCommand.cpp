
#include "ParticleInfoCommand.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"

using namespace Crystal::Physics;
using namespace Crystal::Command;

void ParticleInfoCommand::display(System::Windows::Forms::DataGridView^ view)
{
	view->Rows->Clear();

	const ParticleVector& particles = PhysicsObjectFactory::get()->getSortedParticles();
	
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		Particle* particle = *iter;

		array<Object^>^ rowData = {
					particle->getID(),
					particle->getParent()->getID(),
					particle->getMass(),
					particle->getDensity(),
					particle->center.getX(),
					particle->center.getY(),
					particle->center.getZ()
				};
			
		view->Rows->Add( rowData );
	}
}
