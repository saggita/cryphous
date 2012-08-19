#include "ParticleMarshaler.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalPhysics/Particle.h"
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System::Collections::Generic;

List<ManagedPosition^>^ ParticleMarshaler::convertToManagedPositions(const ParticleVector& nativeParticles)
{
	List<ManagedPosition^>^ managedPositions = gcnew List<ManagedPosition^>();
	for( size_t i = 0; i < nativeParticles.size(); ++i ) {
		ManagedPosition^ newParticle = gcnew ManagedPosition(3);
		newParticle[0] = nativeParticles[i]->center.getX();
		newParticle[1] = nativeParticles[i]->center.getY();
		newParticle[2] = nativeParticles[i]->center.getZ();
		managedPositions->Add( newParticle );
	}

	assert( managedPositions->Count == nativeParticles.size() );
	return managedPositions;
}

List<ManagedVector^>^ ParticleMarshaler::convertToManagedNormals(const ParticleVector& nativeParticles)
{
	List<ManagedVector^>^ managedNormals = gcnew List<ManagedPosition^>();
	for( size_t i = 0; i < nativeParticles.size(); ++i ) {
		ManagedPosition^ normal = gcnew ManagedPosition(3);
		normal[0] = nativeParticles[i]->normal.getX();
		normal[1] = nativeParticles[i]->normal.getY();
		normal[2] = nativeParticles[i]->normal.getZ();
		managedNormals->Add( normal );
	}

	assert( managedNormals->Count == nativeParticles.size() );
	return managedNormals;
}

std::vector<Vector3d> ParticleMarshaler::convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Vector3d> nativePositions;
	
	for each(ManagedPosition^ pos in managedPositions) {
		nativePositions.push_back( Vector3d( pos[0], pos[1], pos[2] ) );
	}

	assert( managedPositions->Count == nativePositions.size() );
	return nativePositions;
}