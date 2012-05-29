#pragma once



namespace Crystal{
	namespace Command{

public ref class AnimationCommandBase abstract
{
public:
	AnimationCommandBase(void);
	
	virtual ~AnimationCommandBase(void);

	virtual void refresh() = 0;

	virtual void proceed() = 0;

	virtual int getStep() = 0;

protected:
	System::Diagnostics::Stopwatch^ stopWatch;
};

	}
}