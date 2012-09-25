#include "../CrystalGeom/Matrix4d.h"

#include <cmath>

namespace Crystal{
	namespace Renderer{
		class ModelViewProjectionMatrix : public Geom::Matrix4d
		{
		public:
			ModelViewProjectionMatrix()
			{
			}

			ModelViewProjectionMatrix(const Geom::Matrix4d& matrix) :
				Geom::Matrix4d(matrix)
			{
			}

			void setTranslate(const float x, const float y, const float z)
			{
				x03 = x;
				x13 = y;
				x23 = z;
			}

			void translate(const float x, const float y, const float z)
			{
				ModelViewProjectionMatrix matrix;
				matrix.translate( x, y, z);
				(*this) *= matrix;
			}

			void setRotateX(const float angle)
			{
				x11 = ::cos( angle );
				x21 = ::sin( angle );
				x12 = -::sin( angle );
				x22 = ::cos( angle );
			}

			void rotateX(const float angle)
			{
				ModelViewProjectionMatrix matrix;
				matrix.setRotateX( angle );
				(*this) *= matrix;
			}

			void setRotateY(const float angle)
			{
				x00 = ::cos( angle );
				x20 = -::sin( angle );
				x02 = ::sin( angle );
				x22 = ::cos( angle );
			}

			void rotateY(const float angle)
			{
				ModelViewProjectionMatrix matrix;
				matrix.setRotateY( angle );
				(*this) *= matrix;
			}

			void setRotateZ(const float angle)
			{
				x00 = ::cos( angle );
				x10 = ::sin( angle );
				x01 = -::sin( angle );
				x11 = ::cos( angle );
			}

			void rotateZ(const float angle)
			{
				ModelViewProjectionMatrix matrix;
				matrix.setRotateZ( angle );
				(*this) *= matrix;
			}

			void setOrthogonalViewMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ)
			{
				setIdentity();
				const float dx = right - left;
				const float dy = top - bottom;
				const float dz = farZ - nearZ;
				x00 = 2.0f / dx;
				x11 = 2.0f / dy;
				x22 = -2.0f / dz;
				x03 = -(right + left) / dx;
				x13 = -(top + bottom) / dy;
				x23 = -(farZ + nearZ) / dz;
			}

			void setPerspectiveViewMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ)
			{
				setIdentity();
				const float dx = right - left;
				const float dy = top - bottom;
				const float dz = farZ - nearZ;
				x00 = 2.0f / dx;
				x11 = 2.0f / dy;
				x22 = -1.0f / dz;
				x32 = -1.0f;
				x02 = -(right + left) / dx;
				x13 = -(bottom + top) / dy;
				x23 = -nearZ / dz;
			}
		};
	}
}