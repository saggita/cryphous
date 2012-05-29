
#include "RigidSolver.h"

#include "Particle.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"

#include <algorithm>
#include <cmath>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

/// コンストラクタ.
RigidSolver::RigidSolver(Particle* particleX, Particle* particleY) :
particleX( particleX ),
particleY( particleY )
{
}

/// 法線方向の力を計算する.
void RigidSolver::calculateNormalForce()
{
	// オーバーラップしているベクトルを求める.
	const double particleLength = particleX->getRadius() + particleY->getRadius();
	const Vector3d distanceVector( particleX->center, particleY->center );
	const double overlapLength = std::max( 0.0, particleLength - distanceVector.getLength() );

	// 実効質量を求める.
	const double massEffective = 1.0 / ( 1.0 / particleX->getMass() + 1.0 / particleY->getMass() );
	const double normalRestitution = 1.0;	// 法線応力係数. TODO.
	const double timeStep = 1.0e-3;
	const double correspondingCoefficient = 2.0 * massEffective * log( normalRestitution ) / timeStep;

	// 相対速度を求める.
	const Vector3d velocityVector( particleX->velocity, particleY->velocity );
	const double relativeVelosity = velocityVector.getInnerProduct( distanceVector );
}
