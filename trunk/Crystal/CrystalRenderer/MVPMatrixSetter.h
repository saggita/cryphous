#include "../CrystalGeom/Matrix4d.h"

#include <cmath>

namespace Crystal{
	namespace Renderer{
		class MVPMatrixSetter
		{
		public:
			static Geom::Matrix4d getOrthogonalViewMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ)
			{
				Geom::Matrix4d matrix;
				matrix.setIdentity();
				const float dx = right - left;
				const float dy = top - bottom;
				const float dz = farZ - nearZ;
				matrix.x00 = 2.0f / dx;
				matrix.x11 = 2.0f / dy;
				matrix.x22 = -2.0f / dz;
				matrix.x03 = -(right + left) / dx;
				matrix.x13 = -(top + bottom) / dy;
				matrix.x23 = -(farZ + nearZ) / dz;
				return matrix;
			}

			static Geom::Matrix4d getPerspectiveViewMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ)
			{
				Geom::Matrix4d matrix;
				matrix.setIdentity();
				const float dx = right - left;
				const float dy = top - bottom;
				const float dz = farZ - nearZ;
				matrix.x00 = 2.0f / dx;
				matrix.x11 = 2.0f / dy;
				matrix.x22 = -1.0f / dz;
				matrix.x32 = -1.0f;
				matrix.x02 = -(right + left) / dx;
				matrix.x13 = -(bottom + top) / dy;
				matrix.x23 = -nearZ / dz;
				return matrix;
			}
		};
	}
}