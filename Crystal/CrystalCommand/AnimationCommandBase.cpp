
#include "AnimationCommandBase.h"

using namespace Crystal::Command;

AnimationCommandBase::AnimationCommandBase(void)
{
	stopWatch = gcnew System::Diagnostics::Stopwatch();
}

AnimationCommandBase::~AnimationCommandBase(void)
{
}