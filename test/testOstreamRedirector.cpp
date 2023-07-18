#include <sstream>

#include <catch2/catch_test_macros.hpp>

#include "../src/OstreamRedirector.hpp"

TEST_CASE("Test Ostream") {
    std::stringstream ss;
    {
        ss << "a";
        auto os_redir = juan::OstreamRedirector(ss);
        ss << "b";
        auto capture = os_redir.get();
        REQUIRE(os_redir.get() == "b");
    }
    ss << "c";
    REQUIRE(ss.str() == "ac");
}
