#include "VisualParticleConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;

std::vector<float> VisualParticleConverter::toPositionArray(const VisualParticle& particle)
{
	std::vector<float> position(3);
	position[0] = particle.center.x;
	position[1] = particle.center.y;
	position[2] = particle.center.z;
	return position;
}

std::vector<float> VisualParticleConverter::toColorArray(const VisualParticle& particle)
{
	std::vector<float> color(4);
	color[0] = 0.5f;
	color[1] = 0.5f;
	color[2] = 0.9f;
	color[3] = 0.1f;
	return color;
}

std::vector<float> VisualParticleConverter::toPositionArray(const VisualParticleVector& particles)
{
	std::vector<float> positions;
	for( const VisualParticle& particle : particles ) {
		const std::vector<float>& position = toPositionArray( particle );
		positions.insert( positions.end(), position.begin(), position.end() );
	}
	return positions;
}

std::vector<float> VisualParticleConverter::toDensityArray(const VisualParticleVector& particles)
{
	std::vector<float> densities;
	for( const VisualParticle& particle : particles ) {
		densities.push_back( particle.density );
	}
	return densities;
}

std::vector<float> VisualParticleConverter::toColorArray(const VisualParticleVector& particles)
{
	std::vector<float> colors;
	for( const VisualParticle& particle : particles ) {
		const std::vector<float>& color = toColorArray( particle );
		colors.insert( colors.end(), color.begin(), color.end() );
	}
	return colors;
}