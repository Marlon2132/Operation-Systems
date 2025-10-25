#include <gtest/gtest.h>
#include "FactorialClass.h"
#include "VecClass.h"

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

    EXPECT_THROW(f.setN(0), invalid_argument);
    EXPECT_THROW(f.fillFactValues(), invalid_argument);
}

TEST(FactorialClassTest, getFactValues___ThrowsWhenEmpty) {
    FactorialClass f;

    EXPECT_THROW(f.getFactValues(), logic_error);

    f.setN(3);
    f.fillFactValues();

    EXPECT_NO_THROW({
        vector<unsigned long long> v = f.getFactValues();
        EXPECT_EQ(v.size(), 3);
    });
}

TEST(VecClassTest, resetArr___ThrowsOnNonPositive) {
    VecClass v;

    EXPECT_THROW(v.resetArr(0), invalid_argument);
    EXPECT_THROW(v.resetArr(-1), invalid_argument);
}

TEST(VecClassTest, resetArr___ResizesAndInitializes) {
    VecClass v;

    EXPECT_NO_THROW(v.resetArr(5));

    vector<long double> a = v.getArr();

    EXPECT_EQ(a.size(), 5);

    for (long double x : a) {
        EXPECT_EQ(x, 0);
    }
}

TEST(VecClassTest, getArr___ThrowsWhenEmpty) {
    VecClass v;

    EXPECT_THROW(v.getArr(), logic_error);
}


TEST(VecClassTest, fillArr___WritesAndBoundsCheck) {
    VecClass v;

    v.resetArr(3);

    EXPECT_NO_THROW(v.fillArr(0, 1.5));
    EXPECT_NO_THROW(v.fillArr(1, -2.25));
    EXPECT_NO_THROW(v.fillArr(2, 3));

    vector<long double> a = v.getArr();

    EXPECT_EQ(a[0], 1.5);
    EXPECT_EQ(a[1], -2.25);
    EXPECT_EQ(a[2], 3);

    EXPECT_THROW(v.fillArr(3, 4), invalid_argument);
    EXPECT_THROW(v.fillArr(100, 4), invalid_argument);
}

TEST(VecClassTest, fillSetArr___ThrowsWhenArrEmpty) {
    VecClass v;

    EXPECT_THROW(v.fillSetArr(), logic_error);
    EXPECT_THROW(v.getSetArr(), logic_error);
}

TEST(VecClassTest, fillSetArr___ProducesUniquePreserveOrder) {
    VecClass v;
    v.resetArr(8);

    // arr: {1,2,1,3,2,4,3,4}
    v.fillArr(0, 1);
    v.fillArr(1, 2);
    v.fillArr(2, 1);
    v.fillArr(3, 3);
    v.fillArr(4, 2);
    v.fillArr(5, 4);
    v.fillArr(6, 3);
    v.fillArr(7, 4);

    EXPECT_NO_THROW(v.fillSetArr());

    vector<long double> s = v.getSetArr();

    ASSERT_EQ(s.size(), 4);

    EXPECT_EQ(s[0], 1);
    EXPECT_EQ(s[1], 2);
    EXPECT_EQ(s[2], 3);
    EXPECT_EQ(s[3], 4);
}

TEST(VecClassTest, fillSetArr___AllEqualAndSingle) {
    VecClass v;

    v.resetArr(5);

    for (unsigned long long i = 0; i < 5; ++i) {
        v.fillArr(i, 7.5);
    }

    v.fillSetArr();

    vector<long double> s1 = v.getSetArr();

    ASSERT_EQ(s1.size(), 1);

    EXPECT_EQ(s1[0], 7.5);

    v.resetArr(1);
    v.fillArr(0, -0.125);
    v.fillSetArr();

    vector<long double> s2 = v.getSetArr();

    ASSERT_EQ(s2.size(), 1);

    EXPECT_EQ(s2[0], -0.125);
}