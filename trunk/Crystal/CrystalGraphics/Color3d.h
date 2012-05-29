#pragma once

#include <cmath>

namespace Crystal{
	namespace Graphics{

class Color3d
{
public:
	Color3d(void): red(0.0), green(0.0), blue(0.0) {};

	Color3d(const double red, const double green, const double blue): 
		red(red), green(green), blue(blue)
		{};

	void setRed(const double red) { this->red = red; }

	void setGreen(const double green) { this->green = green; }

	void setBlue(const double blue) { this->blue = blue; }

	double getRed() const { return red; }

	double getGreen() const { return green; }

	double getBlue() const { return blue; }

	float getRedFloat() const { return static_cast<float>(red); }

	float getGreenFloat() const { return static_cast<float>(green); }

	float getBlueFloat() const { return static_cast<float>(blue); }

	bool operator==(const Color3d& rhs) const {
		return (this->red == rhs.getRed() &&
			this->green == rhs.getGreen() &&
			this->blue == rhs.getBlue() );
	}

	Color3d& operator+=(const Color3d& rhs) {
		this->red += rhs.getRed();
		this->green += rhs.getGreen();
		this->blue += rhs.getBlue();
		return *this; }

	Color3d& operator-=(const Color3d& rhs) {
		this->red -= rhs.getRed();
		this->green -= rhs.getGreen();
		this->blue -= rhs.getBlue();
		return *this;
	}

	Color3d& scale(const double factor) {
		this->red *= factor;
		this->green *= factor;
		this->blue *= factor;
		return *this;
	}

	Color3d& operator*=(const double factor) {
		return scale( factor );
	}

	Color3d operator*(const double factor) const {
		Color3d color = *this;
		return color.scale( factor);
	}

	Color3d& operator/=(const double factor) {
		return scale( 1.0 / factor );
	}

	Color3d operator/(const double factor) const {
		Color3d color = *this;
		return color.scale( 1.0 / factor );
	}

	Color3d getBlended(const Color3d& rhs, const double rhsRatio)  const {
		const double lhsRatio = 1.0 - rhsRatio;
		Color3d lhsColor = *this;
		lhsColor *= lhsRatio;
		Color3d rhsColor = rhs;
		rhsColor *= rhsRatio;
		lhsColor += rhsColor;
		return lhsColor.normalize();
	}

	Color3d normalize() {
		const double denominator =
			std::sqrt( this->red * this->red + this->green * this->green + this->blue * this->blue );
		(*this) /= denominator;
		return *this;
	}

	Color3d getNormalize() const {
		Color3d color = *this;
		return color.normalize();
	}

private:
	double red;
	double green;
	double blue;
};

	}
}