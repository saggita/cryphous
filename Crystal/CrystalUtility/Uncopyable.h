#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__

namespace Crystal {

class Uncopyable
{
protected:
	Uncopyable() {};
	~Uncopyable() {};

private:
	Uncopyable( const Uncopyable& );
	const Uncopyable& operator=( const Uncopyable& );
};

}

#endif