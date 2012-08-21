#ifndef __COLOR_MATCHING_XYZ_H__
#define __COLOR_MATCHING_XYZ_H__

#include <vector>

namespace Crystal{
	namespace Color{

class ColorMatchingXYZ
{
public:
	struct MatchingTable{
		double waveLength;
		double x;
		double y;
		double z;
	};

	typedef std::vector<MatchingTable> MatchingTableVector;

	ColorMatchingXYZ(void);
	~ColorMatchingXYZ(void){};

	MatchingTableVector getMatchingTable() { return matchingTable; }

private:
	MatchingTableVector matchingTable;

	bool setUpTable();
};

	}
}
#endif __COLOR_MATCHING_XYZ_H__