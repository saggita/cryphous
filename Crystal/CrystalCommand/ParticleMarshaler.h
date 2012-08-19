#pragma once

#include <vector>

namespace Crystal{
	namespace Geom {
		class Vector3d;
	}
	namespace Physics{
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
	}
	namespace Command{
		typedef array< float > ManagedPosition;
		typedef array< float > ManagedVector;
public ref class ParticleMarshaler
{
public:
	static System::Collections::Generic::List<ManagedPosition^>^ convertToManagedPositions(const Physics::ParticleVector& nativeParticles);

	static System::Collections::Generic::List<ManagedVector^>^ convertToManagedNormals(const Physics::ParticleVector& nativeParticles);

	static std::vector<Geom::Vector3d> convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions);
};

	}
}


