#include "gtest/gtest.h"
#include <service/hash/Hash.h>

TEST(TestHash, testConsistency) {
    Hash hash1("test hash");
    auto res1 = hash1.toString();
    Hash hash2("test hash");
    auto res2 = hash2.toString();
    Hash hash3("test hash");
    auto res3 = hash3.toString();
    ASSERT_STREQ(res1.c_str(), res2.c_str());
    ASSERT_STREQ(res2.c_str(), res3.c_str());
}
