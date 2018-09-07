#include "jdm/path.h"

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
				// pop last dir
				m_parts.pop_back();
			} else if (buf != ".") {
				// push buffer
				m_parts.push_back(buf);
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

	m_raw.clear();
}

path &path::cd(const std::string &dir)
{
	m_raw = dir;
	make_parts();
	return *this;
}

std::string path::str() const
{
	std::string res;

	for (const auto& part : m_parts) {
		res.append(part);
		res.push_back('/');
	}

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
