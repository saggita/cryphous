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
		typedef array< float > ManagedPosition;//System::Collections::Generic::List<double> ManagedPosition;
public ref class ParticleMarshaler
{
public:
	static System::Collections::Generic::List<ManagedPosition^>^ convertToManaged(const Physics::ParticleVector& nativeParticles);

	static std::vector<Geom::Vector3d> convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions);
};

	}
}


