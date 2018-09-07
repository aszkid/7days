#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "jdm/path.h"

namespace jdm {
	std::ostream &operator << (std::ostream &os, path const &value)
	{
		os << value.str();
		return os;
	}
}

TEST_CASE("`path` with relative paths", "[path]") {
	using namespace jdm;

	REQUIRE(path() == path(""));
	REQUIRE(path("media/vids") == path("media").cd("vids"));
	REQUIRE(path("media/vids") == path("media/").cd("vids/"));
	REQUIRE(path("media/vids/") == path("media").cd("vids"));
	REQUIRE(path("media/vids") == path("media/vids/tech").cd(".."));
	REQUIRE(path("media/vids") == path("media/vids").cd("tech").cd(".."));
	REQUIRE(path("media/../media/vids") == path("media/vids"));
	REQUIRE(path("media/./vids") == path("media/vids"));
	REQUIRE(path("media/./vids/.././vids/funny/./") == path("media/vids/funny"));
}

TEST_CASE("`path` with absolute paths", "[path]") {
	using namespace jdm;

	REQUIRE(path("/var/www") == path("/var").cd("www"));
	REQUIRE(path("/media/vids") == path("/media").cd("vids"));
	REQUIRE(path("/media/vids") == path("/media/").cd("vids/"));
	REQUIRE(path("/media/vids/") == path("/media").cd("vids"));
	REQUIRE(path("/media/vids") == path("/media/vids/tech").cd(".."));
	REQUIRE(path("/media/vids") == path("/media/vids").cd("tech").cd(".."));
	REQUIRE(path("/media/../media/vids") == path("/media/vids"));
	REQUIRE(path("/media/./vids") == path("/media/vids"));
	REQUIRE(path("/media/./vids/.././vids/funny/./") == path("/media/vids/funny"));

}
