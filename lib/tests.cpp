#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "jdm/path.h"

namespace jdm
{
std::ostream &operator<<(std::ostream &os, path const &value)
{
	os << value.str();
	return os;
}
}

TEST_CASE("`path` with relative paths", "[path]")
{
	using namespace jdm;

	REQUIRE(path() == path(""));
	REQUIRE(path("media/vids") == path("media").cd("vids"));
	REQUIRE(path("media/vids") == path("media/").cd("vids/"));
	REQUIRE(path("media/vids/") == path("media").cd("vids"));
	REQUIRE(path("media/vids") == path("media/vids/tech").cd(".."));
	REQUIRE(path("media/vids") == path("media/vids").cd("tech").cd(".."));
	REQUIRE(path("media/../media/vids") == path("media/vids"));
	REQUIRE(path("media/./vids") == path("media/vids"));
	REQUIRE(path("media/./vids/.././vids/funny/./") ==
		path("media/vids/funny"));
	REQUIRE(path("media/game/run").cd("assets/tiles").cd("./base.json") ==
		path("media/game/run/assets/tiles/base.json"));
	REQUIRE(path("media/game/run/assets").cd("../").cd("../../") ==
		path("media"));
	/*
	 * Leading `../` cannot be simplified
	 */
	REQUIRE(path("../run") == path().cd("../").cd("run"));
	REQUIRE(path("./") == path("media").cd("test").cd("../").cd("../"));
	REQUIRE(path("./") ==
		path("media").cd("test").cd("../").cd("..").cd("caca").cd(
			"../../"));
	REQUIRE(path("./") == path("media").cd(".."));
	REQUIRE(path("..") == path("media").cd("../.."));
	REQUIRE(path(".././hello/./world/.././").str() == "../hello");
}

TEST_CASE("`path` with absolute paths", "[path]")
{
	using namespace jdm;

	REQUIRE(path("/var/www") == path("/var").cd("www"));
	REQUIRE(path("/media/vids") == path("/media").cd("vids"));
	REQUIRE(path("/media/vids") == path("/media/").cd("vids/"));
	REQUIRE(path("/media/vids/") == path("/media").cd("vids"));
	REQUIRE(path("/media/vids") == path("/media/vids/tech").cd(".."));
	REQUIRE(path("/media/vids") == path("/media/vids").cd("tech").cd(".."));
	REQUIRE(path("/media/../media/vids") == path("/media/vids"));
	REQUIRE(path("/media/./vids") == path("/media/vids"));
	REQUIRE(path("/media/./vids/.././vids/funny/./") ==
		path("/media/vids/funny"));
	REQUIRE(path("/hello/world").str() == "/hello/world");

	REQUIRE(path("/media").is_absolute() == true);
	REQUIRE(path("/media").str() == "/media");
	REQUIRE(path("/media").cd("..").is_absolute() == true);
	REQUIRE(path("/").str() == "/");
	REQUIRE(path("/media").cd("..") == path("/"));
	REQUIRE(path("/media").cd("..").str() == "/");
}

TEST_CASE("absolute vs. relative paths", "[path]")
{
	using namespace jdm;

	REQUIRE((path("media/data") == path("/media/data")) == false);
}
