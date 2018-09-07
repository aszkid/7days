#include "path.h"

using namespace jdm;

path::path()
{}

path::~path()
{}

path path::cd(const std::string &dir)
{
	return *this;
}
