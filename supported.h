#ifndef supported
#define supported
#include<stdexcept>
inline void sassert(bool expression,const char* message="expression not supported")
{
	if(!expression)
	throw std::runtime_error(message);
}
#endif
