#pragma once

#include <list>

namespace Crystal {
	namespace Physics {
		class PhysicsObjectCondition;
		typedef std::list<PhysicsObjectCondition*> PhysicsObjectConditionList;
	}

	namespace Command {

/// アプリケーション設定クラス.
public ref class ApplicationSettings
{
public:

	/// コンストラクタ.
	ApplicationSettings(void);

	/// デストラクタ.
	~ApplicationSettings();

	/// XMLへ書き出す.
	System::Xml::XmlDocument^ writeToXML();

	/// XMLから読み込む.
	bool readFromXML( System::Xml::XmlDocument^ doc );
};

	}	// namespace Command
}	// namespace Crystal