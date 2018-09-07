#pragma once

#include <string>
#include <vector>

namespace jdm {

	class path {
	public:
		path();
		~path();

		path cd(const std::string& dir);
	private:
		std::vector<std::string> m_parts;
		std::string m_raw;
	};

}
