#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../src/lal.h"

TEST_CASE("checking zero vector")
{
   CHECK(zero_vector() == true);
}

