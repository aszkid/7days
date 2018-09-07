#pragma once

#include <string>
#include <vector>

namespace jdm {

	class string_view {
		
	};

	/*
	 * Path manipulaton class.
	 */
	class path {
	public:
		path();
		path(const std::string &dir);
		~path();

		/*
		 * Modifiers
		 */
		path &cd(const std::string& dir);

		/*
		 * Functional 'modifiers'
		 */
		path operator/(const path &other) const;
		path operator/(const std::string &other) const;

		/*
		 * Accessors
		 */
		std::string str() const;
		const std::vector<std::string> &parts() const;

		/*
		 * Const operators
		 */
		bool operator==(const path& right) const;
	private:
		/*
		 * Consumes `m_raw`
		 */
		void make_parts();

		std::vector<std::string> m_parts;
		std::string m_raw;
	};

}
