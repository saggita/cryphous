#pragma once

#include <vector>

#include "../CrystalGeom/Vector3d.h"
#include "Particle.h"

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics{
		class Particle;
		class SpaceHash;
		class BoundarySolver;

/// 粒子ペアクラス.
class ParticlePair : private boost::noncopyable
{
public:

	ParticlePair();

	/// コンストラクタ.
	ParticlePair(Particle* particleX, Particle* particleY) :
	  particleX( particleX),
		  particleY( particleY),
		  distanceVector( particleY->center, particleX->center )
	{
		distance = distanceVector.getLength();
	}

	 /// デストラクタ.
	 ~ParticlePair() { };

public:
	/// 着目粒子を取得する.
	Particle* getParticleX() const { return particleX; }

	/// 対称粒子を取得する.
	Particle* getParticleY() const { return particleY; }

	/// 粒子間距離ベクトルを取得する.
	Geom::Vector3d getDistanceVector() const { return distanceVector; }

	/// 粒子間距離を取得する.
	double getDistance() const { return distance; }

private:
	Particle* particleX;	///< 着目粒子.
	Particle* particleY;	///< 対称粒子.
	Geom::Vector3d distanceVector;	///< 距離ベクトル.
	double distance;	///< 粒子間距離. キャッシュ.

};

typedef std::vector<ParticlePair*> ParticlePairVector; 
	}	// namespace Physics
}	// namespace Crystal