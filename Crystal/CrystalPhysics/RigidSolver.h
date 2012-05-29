#pragma once

namespace Crystal{
	namespace Physics{

class Particle;

/// 剛体粒子ソルバ.
class RigidSolver
{
public:
	/// コンストラクタ.
	RigidSolver(Particle* particleX, Particle* particleY);

	/// 法線方向の力を計算する.
	void calculateNormalForce();

	/// 接線方向の力を計算する.
	void calculateTangentForce();

private:
	Particle* particleX;
	Particle* particleY;
};

	}	// namespace Physics
}	// namespace Crystal;
