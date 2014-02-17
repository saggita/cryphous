#ifndef __CRYSTAL_GRAPHICS_COLOR_H__
#define __CRYSTAL_GRAPHICS_COLOR_H__

namespace Crystal {
	namespace Graphics {

class Color {
private:
	float red;
	float green;
	float blue;
	float alpha;

public:
	Color()
	{}

	Color(float red, float green, float blue, float alpha) :
		red( red ), green( green ), blue( blue ), alpha( alpha )
	{}

	float getRed() const { return red; }

	float getGreen() const { return green; }

	float getBlue() const { return blue; }

	float getAlpha() const { return alpha; }

	static Color White() {
		return Color( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	static Color Black() {
		return Color( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	static Color Red() {
		return Color( 1.0f, 0.0f, 0.0f, 1.0f );
	}

	static Color Green() {
		return Color( 0.0f, 1.0f, 0.0f, 1.0f );
	}

	static Color Blue() {
		return Color( 0.0f, 0.0f, 1.0f, 1.0f );
	}

	static Color Yellow() {
		return Color( 1.0f, 1.0f, 0.0f, 1.0f);
	}
	
	static Color Cyan() {
		return Color( 0.0f, 1.0f, 1.0f, 1.0f );
	}

	static Color Magenta() {
		return Color( 1.0f, 0.0f, 1.0f, 1.0f );
	}

	std::vector<float> toArray3() const {
		std::vector<float> results(3);
		results[0] = red;
		results[1] = green;
		results[2] = blue;
		return results;
	}

	std::vector<float> toArray4() const {
		std::vector<float> results(4);
		results[0] = red;
		results[1] = green;
		results[2] = blue;
		results[3] = alpha;
		return results;
	
	}

};

class ColorCollection {
public:
	void push_back( const Color& color ) {
		colors.push_back( color );
	}

	size_t size() const { return colors.size(); }

	std::vector<float> toArray3() const {
		std::vector< float > results;
		for( const Color& color : colors ) {
			std::vector< float > tmp = color.toArray3();
			results.insert( results.end(), tmp.begin(), tmp.end() );
		}
		return results;
	}

	std::vector<float> toArray4() const {
		std::vector< float > results;
		for( const Color& color : colors ) {
			std::vector< float > tmp = color.toArray4();
			results.insert( results.end(), tmp.begin(), tmp.end() );
		}
		return results;
	}

private:
	std::vector< Color > colors;
};
	}
}

#endif