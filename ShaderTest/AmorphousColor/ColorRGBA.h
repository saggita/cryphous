#ifndef __COLOR_RGBA_H__
#define __COLOR_RGBA_H__

#include <cmath>

namespace Amorphous{
	namespace Color{

template <typename T = double>
class ColorRGBA
{
public:
	ColorRGBA(void): red(0.0), green(0.0), blue(0.0), alpha(0.0) {};

	ColorRGBA(const T red, const T green, const T blue, const T alpha = 0.0): 
		red(red), green(green), blue(blue), alpha( alpha)
		{};

	void setRed(const T red) { this->red = red; }

	void setGreen(const T green) { this->green = green; }

	void setBlue(const T blue) { this->blue = blue; }

	void setAlpha(const T alpha) { this->alpha = alpha; }

	T getRed() const { return red; }

	T getGreen() const { return green; }

	T getBlue() const { return blue; }

	T getAlpha() const { return alpha; }

	/*float getRedFloat() const { return static_cast<float>(red); }

	float getGreenFloat() const { return static_cast<float>(green); }

	float getBlueFloat() const { return static_cast<float>(blue); }

	float getAlphaFloat() const { return static_cast<float>(alpha); }*/

	bool equals(const ColorRGBA& rhs) const {
		return Geom::Tolerances::isEqualAsDistance( red, rhs.getRed() ) &&
			Geom::Tolerances::isEqualAsDistance( green, rhs.getGreen() ) &&
			Geom::Tolerances::isEqualAsDistance( blue, rhs.getBlue() ) &&
			Geom::Tolerances::isEqualAsDistance( alpha, rhs.getAlpha() );
	}

	bool operator==(const ColorRGBA& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const ColorRGBA& rhs) const {
		return !equals(rhs);
	}

	ColorRGBA& operator+=(const ColorRGBA& rhs) {
		this->red += rhs.getRed();
		this->green += rhs.getGreen();
		this->blue += rhs.getBlue();
		this->alpha += rhs.getAlpha();
		return *this; }

	ColorRGBA& operator-=(const ColorRGBA& rhs) {
		this->red -= rhs.getRed();
		this->green -= rhs.getGreen();
		this->blue -= rhs.getBlue();
		this->alpha -= rhs.getAlpha();
		return *this;
	}

	ColorRGBA operator+(const ColorRGBA& rhs) const{
		ColorRGBA color(*this);
		color += rhs;
		return color;
	}

	ColorRGBA operator-(const ColorRGBA& rhs) const{
		ColorRGBA color(*this);
		color -= rhs;
		return color;
	}

	ColorRGBA& scale(const T factor) {
		this->red *= factor;
		this->green *= factor;
		this->blue *= factor;
		this->alpha *= factor;
		return *this;
	}

	ColorRGBA& operator*=(const T factor) {
		return scale( factor );
	}

	ColorRGBA operator*(const T factor) const {
		ColorRGBA color = *this;
		return color.scale( factor);
	}

	ColorRGBA& operator/=(const T factor) {
		return scale( 1.0 / factor );
	}

	ColorRGBA operator/(const T factor) const {
		ColorRGBA color = *this;
		return color.scale( 1.0 / factor );
	}

	ColorRGBA getBlended(const ColorRGBA& rhs, const T rhsRatio)  const {
		const double lhsRatio = 1.0 - rhsRatio;
		ColorRGBA lhsColor = *this;
		lhsColor *= lhsRatio;
		ColorRGBA rhsColor = rhs;
		rhsColor *= rhsRatio;
		lhsColor += rhsColor;
		return lhsColor.normalize();
	}

	ColorRGBA normalize() {
		red = std::max( 0.0, red );
		green = std::max( 0.0, green );
		blue = std::max( 0.0, blue );
	
		const double maxColor = std::max( red, std::max( green, blue ) );
		(*this) /= maxColor;
		return *this;
	}

	ColorRGBA getNormalize() const {
		ColorRGBA color = *this;
		return color.normalize();
	}

private:
	T red;
	T green;
	T blue;
	T alpha;
};

	}
}

#endif __COLOR_RGBA_H__