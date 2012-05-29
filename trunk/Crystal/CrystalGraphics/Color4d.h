#pragma once

#include <cmath>

namespace Crystal{
	namespace Graphics{

class Color4d
{
public:
	Color4d(void): red(0.0), green(0.0), blue(0.0), alpha(0.0) {};

	Color4d(const double red, const double green, const double blue, const double alpha = 0.0): 
		red(red), green(green), blue(blue), alpha( alpha)
		{};

	void setRed(const double red) { this->red = red; }

	void setGreen(const double green) { this->green = green; }

	void setBlue(const double blue) { this->blue = blue; }

	void setAlpha(const double alpha) { this->alpha = alpha; }

	double getRed() const { return red; }

	double getGreen() const { return green; }

	double getBlue() const { return blue; }

	double getAlpha() const { return alpha; }

	float getRedFloat() const { return static_cast<float>(red); }

	float getGreenFloat() const { return static_cast<float>(green); }

	float getBlueFloat() const { return static_cast<float>(blue); }

	float getAlphaFloat() const { return static_cast<float>(alpha); }

	bool equals(const Color4d& rhs) const;

	bool operator==(const Color4d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Color4d& rhs) const {
		return !equals(rhs);
	}

	Color4d& operator+=(const Color4d& rhs) {
		this->red += rhs.getRed();
		this->green += rhs.getGreen();
		this->blue += rhs.getBlue();
		this->alpha += rhs.getAlpha();
		return *this; }

	Color4d& operator-=(const Color4d& rhs) {
		this->red -= rhs.getRed();
		this->green -= rhs.getGreen();
		this->blue -= rhs.getBlue();
		this->alpha -= rhs.getAlpha();
		return *this;
	}

	Color4d& scale(const double factor) {
		this->red *= factor;
		this->green *= factor;
		this->blue *= factor;
		this->alpha *= factor;
		return *this;
	}

	Color4d& operator*=(const double factor) {
		return scale( factor );
	}

	Color4d operator*(const double factor) const {
		Color4d color = *this;
		return color.scale( factor);
	}

	Color4d& operator/=(const double factor) {
		return scale( 1.0 / factor );
	}

	Color4d operator/(const double factor) const {
		Color4d color = *this;
		return color.scale( 1.0 / factor );
	}

	Color4d getBlended(const Color4d& rhs, const double rhsRatio)  const;

	Color4d normalize();

	Color4d getNormalize() const {
		Color4d color = *this;
		return color.normalize();
	}

private:
	double red;
	double green;
	double blue;
	double alpha;
};

	}
}