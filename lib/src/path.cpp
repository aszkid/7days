#include "jdm/path.h"

#include <functional>
#include <numeric>

using namespace jdm;

path::path()
{}

path::path(const std::string &dir)
  : m_raw(dir)
{
	make_parts();
}

path::~path()
{}

void path::make_parts()
{
	std::string buf;
	for (const char c : m_raw) {
		if (c == '/') {
			if (buf.empty()) {
				// need more data
				continue;
			} else if (buf == "..") {
				// pop last dir if inside path
				if (!m_parts.empty()) {
					m_parts.pop_back();
				} else {
					m_parts.push_back(buf);
				}
			} else {
				if ((buf == "." && m_parts.empty())
				  || buf != ".") {
					m_parts.push_back(buf);
				}
			}

			buf.clear();
		} else {
			buf.push_back(c);
		}
	}

	if (!buf.empty()) {
		// non-slash terminated path
		if (buf == "..") {
			m_parts.pop_back();
		} else {
			m_parts.push_back(buf);
		}
		
		buf.clear();
	}

	if (!m_raw.empty() && m_parts.empty()) {
		// through path operations, we got to the the 'empty' path,
		// but that is translated by `./`
		m_parts.push_back(".");
	}

	m_raw.clear();
}

path &path::cd(const std::string &dir)
{
	m_raw = dir;
	make_parts();
	return *this;
}

path path::operator/(const path &other) const
{
	path res(str());
	res.cd(other.str());
	return res;
}

path path::operator/(const std::string &other) const
{
	return *this / path(other);
}

std::string path::str() const
{
	if (m_parts.empty()) {
		return std::string();
	}

	std::string res = std::accumulate(std::next(m_parts.begin()), m_parts.end(),
			m_parts[0],
			[](std::string a, std::string b) {
				return a + '/' + b;
			});
	return res;
}

const std::vector<std::string> &path::parts() const
{
	return m_parts;
}

bool path::operator==(const path& right) const
{
	return str() == right.str();
}
