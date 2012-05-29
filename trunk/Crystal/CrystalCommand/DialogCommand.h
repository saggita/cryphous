#pragma once

#include "ItemAndVariable.h"

namespace Crystal{
	namespace Command{

public ref class DialogCommand
{
protected:
	DialogCommand(void){
	};

	virtual ~DialogCommand() {};

public:

	  virtual void save() {
		  for each( ItemAndVariable^ itemAndVariable in itemAndVariables ){
			  itemAndVariable->applyToVariable();
		  }
	  }

protected:
	System::Collections::Generic::Stack<ItemAndVariable^> itemAndVariables;
};

	}
}