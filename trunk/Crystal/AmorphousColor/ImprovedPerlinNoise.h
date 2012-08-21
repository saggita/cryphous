#ifndef __IMPROVED_PERLIN_NOISE_H__
#define __IMPROVED_PERLIN_NOISE_H__

namespace Crystal{
	namespace Color{

class ImprovedPerlinNoise
{
public:
	ImprovedPerlinNoise(void);

	~ImprovedPerlinNoise(void);

	double getNoise(const double x, const double y, const double z) const;
};

	}
}
#endif __IMPROVED_PERLIN_NOISE_H__