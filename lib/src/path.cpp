#include "jdm/path.h"

#include <functional>
#include <numeric>

using namespace jdm;

path::path()
{
}

path::path(const std::string &dir) : m_raw(dir)
{
	make_parts();
}

path::~path()
{
}

void path::make_parts()
{
	// should only run when creating path from zero
	if (m_parts.empty())
		m_absolute = (m_raw.find("/") == 0);


	std::string buf;
	for (const char c : m_raw) {
		// handle separator
		if (c == '/') {
			if (handle_token(buf)) buf.clear();
		} else {
			buf.push_back(c);
		}
	}

	if (!buf.empty()) {
		// non-slash terminated
		handle_token(buf);
	}

	if (!m_raw.empty() && m_parts.empty() && !is_absolute()) {
		// through path operations, we got to the the 'empty' path,
		// but that is translated by `./` for non-absolute paths
		m_parts.push_back(".");
	}

	m_raw.clear();
}

bool path::handle_token(const std::string &tok)
{
	if (tok.empty()) {
		return false;
	}

	if (tok == "..") {
		if (m_parts.empty()) {
			// top-level `..` remains
			m_parts.push_back(tok);
		} else {
			// go upstairs
			m_parts.pop_back();
		}
	} else if (tok == ".") {
		// need `./`
		if (m_parts.empty() && !is_absolute()) m_parts.push_back(tok);
	} else {
		m_parts.push_back(tok);
	}

	return true;
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
	std::string res;
	if (m_absolute) res += "/";

	if (m_parts.empty()) {
		return res;
	}

	res += std::accumulate(
		std::next(m_parts.begin()), m_parts.end(), m_parts[0],
		[](std::string a, std::string b) { return a + '/' + b; });

	return res;
}

path::operator std::string() const
{
	return str();
}

bool path::is_absolute() const
{
	return m_absolute;
}

const std::vector<std::string> &path::parts() const
{
	return m_parts;
}

bool path::operator==(const path &right) const
{
	return str() == right.str();
}

std::ostream &operator<<(std::ostream &os, const path &c)
{
	return os << c.str();
}
