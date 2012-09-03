#include "ImprovedPerlinNoise.h"

#include <cmath>

using namespace Crystal::Shader;

int p[] = { 151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
		151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};

ImprovedPerlinNoise::ImprovedPerlinNoise(void)
{
}


ImprovedPerlinNoise::~ImprovedPerlinNoise(void)
{
}

double fade(const double t) 
{ 
	return t * t * t * (t * (t * 6 - 15) + 10); 
}

double lerp(const double t, const double a, const double b) 
{ 
	return a + t * (b - a);
}

double grad(const int hash, const double x, const double y, const double z)
{
	const int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	const double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
		v = h<4 ? y : h==12||h==14 ? x : z;
	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

double ImprovedPerlinNoise::getNoise(const double x, const double y, const double z) const
{
	const int unitCubeX = static_cast<int>(floor(x)) & 255;// FIND UNIT CUBE THAT
	const int unitCubeY = static_cast<int>(floor(y)) & 255;// CONTAINS POINT.
	const int unitCubeZ = static_cast<int>(floor(z)) & 255;

	const double relativeX = x - floor(x);// FIND RELATIVE X,Y,Z
	const double relativeY = y - floor(y);// OF POINT IN CUBE.
	const double relativeZ = z - floor(z);

	const double u = fade(relativeX);// COMPUTE FADE CURVES
	const double v = fade(relativeY);// FOR EACH OF X,Y,Z.
	const double w = fade(relativeZ);

	const int A = p[unitCubeX] + unitCubeY;// HASH COORDINATES OF
	const int AA = p[A] + unitCubeZ;// THE 8 CUBE CORNERS,
	const int AB = p[A+1] + unitCubeZ;
	
	const int B = p[unitCubeX+1] + unitCubeY;
	const int BA = p[B] + unitCubeZ;
	const int BB = p[B+1] + unitCubeZ;

	return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
									grad(p[BA], x-1, y, z)),
							lerp(u, grad(p[AB], x, y-1, z),
									grad(p[BB], x-1, y-1, z ))),
					lerp(v, lerp(u, grad(p[AA+1], x, y, z-1),
									grad(p[BA+1], x-1, y, z-1)),
							lerp(u, grad(p[AB+1], x, y-1, z-1),
									grad(p[BB+1], x-1, y-1, z-1 ))));// AND ADD BLENDED RESULTS FROM 8 CORNERS OF CUBE
}