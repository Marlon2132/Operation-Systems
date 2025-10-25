#include <gtest/gtest.h>
#include "FactorialClass.h"

using namespace std;

TEST(FactorialClassTest, setN_and_getN___Natural) {
	FactorialClass f;

	EXPECT_NO_THROW(f.setN(10));
	EXPECT_EQ(f.getN(), 10);
}

TEST(FactorialClassTest, setN___LargeNatural) {
	FactorialClass f;

    EXPECT_THROW(f.setN(25), out_of_range);
}

TEST(FactorialClassTest, setN___NotNatural) {
	FactorialClass f;

	EXPECT_THROW(f.setN(-314), invalid_argument); // -314
	EXPECT_THROW(f.setN(0), invalid_argument); // 0
}

TEST(FactorialClassTest, fillFactValues_and_getFactValues___Normal) {
    FactorialClass f;
    f.setN(6);

    EXPECT_NO_THROW(f.fillFactValues());

    vector<unsigned long long> v = f.getFactValues();

    ASSERT_EQ(v.size(), 6);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 6);
	EXPECT_EQ(v[3], 24);
	EXPECT_EQ(v[4], 120);
	EXPECT_EQ(v[5], 720);
}

TEST(FactorialClassTest, fillFactValues___nIsNotSetOrInvalid) {
    FactorialClass f;

    EXPECT_THROW(f.setN(0), std::invalid_argument);
    EXPECT_THROW(f.fillFactValues(), std::invalid_argument);
}

TEST(FactorialClassTest, getFactValues___ThrowsWhenEmpty) {
    FactorialClass f;

    EXPECT_THROW(f.getFactValues(), std::logic_error);

    f.setN(3);
    f.fillFactValues();

    EXPECT_NO_THROW({
        vector<unsigned long long> v = f.getFactValues();
        EXPECT_EQ(v.size(), 3);
    });
}