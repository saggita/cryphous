#pragma once

#include <list>

namespace Crystal {
	namespace Physics {
		class PhysicsObjectFactory;
		class PhysicsObjectCondition;
		typedef std::list<PhysicsObjectCondition*> PhysicsObjectConditionList;
	}

	namespace Command {

public ref class ApplicationSettings
{	
private:
	ApplicationSettings(void);

	~ApplicationSettings();


	static ApplicationSettings^ instance;

public:
	static ApplicationSettings^ get() {
		if( instance == nullptr ) {
			instance =  gcnew ApplicationSettings();
		}
		return instance;
	}

public:

	System::Xml::XmlDocument^ writeToXML();

	bool readFromXML( System::Xml::XmlDocument^ doc );

	Physics::PhysicsObjectFactory* factory;
};

	}
}