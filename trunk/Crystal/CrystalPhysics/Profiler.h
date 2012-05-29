#pragma once

#include <boost/timer.hpp>

#include <vector>
#include <map>
#include <string>

namespace Crystal{
	namespace Physics{

class Profiler
{
private:
	Profiler(void){};

	~Profiler(void){};

public:
	static Profiler* get(){
		static Profiler profiler;
		return &profiler;
	}

	void init() {
		strAndTimers.clear();
		strAndTimes.clear();
	}

	void start( const std::string& profileName ) {
		strAndTimers[profileName].restart();
		//timer.restart();
	}

	void end( const std::string& profileName ) {
		//strAndTimes[profileName] += timer.elapsed();
		strAndTimes[profileName] += strAndTimers[profileName].elapsed();
	}

	std::map< std::string, double > getStrAndTimes() const { return strAndTimes; }

private:
	//boost::timer timer;
	std::map< std::string, boost::timer > strAndTimers;
	std::map< std::string, double > strAndTimes;
};

	}
}