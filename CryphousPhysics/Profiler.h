#ifndef __CRYPHOUS_PROFILER_H__
#define __CRYPHOUS_PROFILER_H__

#include <ctime>

#include <vector>
#include <map>
#include <string>

namespace Cryphous{
	namespace Physics{

class Timer
{
 public:
	 Timer() {
		 startTime = std::clock(); 
	 }
	 
	 void restart() { 
		 startTime = std::clock(); 
	 }
	 
	 double getElapsedTime() const {
		 return double( std::clock() - startTime) / CLOCKS_PER_SEC; 
	 }

 private:
	std::clock_t startTime;
};

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
	}

	void end( const std::string& profileName ) {
		strAndTimes[profileName] += strAndTimers[profileName].getElapsedTime();
	}

	std::map< std::string, double > getStrAndTimes() const { return strAndTimes; }

private:
	std::map< std::string, Timer > strAndTimers;
	std::map< std::string, double > strAndTimes;
};

	}
}

#endif