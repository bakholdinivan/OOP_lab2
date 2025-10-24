#include <gtest/gtest.h>
#include "twelve.h"
#include <sstream>
#include <stdexcept>

TEST(TwelveTests, ConstructionAndToString) {
    Twelve t1("1A5");
    EXPECT_EQ(t1.toString(), "1A5");

    Twelve t2("0");
    EXPECT_EQ(t2.toString(), "0");

    Twelve t3("B2");
    EXPECT_EQ(t3.toString(), "B2");
}

TEST(TwelveTests, Addition) {
    Twelve t1("1A5"); // 269
    Twelve t2("B2");  // 134
    Twelve sum1 = t1.add(t2); // 269 + 134 = 403 = "297"
    EXPECT_EQ(sum1.toString(), "297");
    Twelve sum2 = t2.add(t1); // коммутативность
    EXPECT_EQ(sum2.toString(), "297");
}

TEST(TwelveTests, Subtraction) {
    Twelve t1("1A5"); // 269
    Twelve t2("B2");  // 134
    Twelve diff1 = t1.sub(t2); // 269 - 134 = 135 = "B3"
    EXPECT_EQ(diff1.toString(), "B3");
    Twelve diff2 = t1.sub(t1); // 269 - 269 = 0
    EXPECT_EQ(diff2.toString(), "0");
    Twelve diff3 = t2.sub(Twelve("0")); // 134 - 0 = 134
    EXPECT_EQ(diff3.toString(), "B2");
}

TEST(TwelveTests, CopyAndCompare) {
    Twelve t1("1A5");
    Twelve t2 = t1.copy();
    EXPECT_EQ(t1.toString(), t2.toString());
    EXPECT_EQ(t1.compare(t2), 0);

    Twelve t3("B2");
    EXPECT_LT(t3.compare(t1), 0);  // t3 < t1
    EXPECT_GT(t1.compare(t3), 0);  // t1 > t3
}

TEST(TwelveTests, SubtractionNegativeThrows) {
    Twelve t1("B2"); // 134
    Twelve t2("1A5"); // 269
    EXPECT_THROW(Twelve res = t1.sub(t2), std::out_of_range);
}

TEST(TwelveTests, InvalidInput) {
    EXPECT_THROW(Twelve t("1G5"), std::invalid_argument);
    EXPECT_THROW(Twelve t(""), std::invalid_argument);
}

TEST(TwelveTests, LargeNumber) {
    Twelve t1("BBBB"); // максимальное 4-цифровое число в 12-ричной: 20735
    EXPECT_EQ(t1.toDecimal(), 20735uLL);
}

TEST(TwelveTests, MinimalNumber) {
    Twelve t("0");
    EXPECT_EQ(t.toDecimal(), 0uLL);
}

TEST(TwelveTests, DecimalRoundTrip) {
    unsigned long long num = 12345;
    Twelve t = Twelve::fromDecimal(num);
    EXPECT_EQ(t.toDecimal(), num);
}

TEST(TwelveTests, FromDecimalToString) {
    unsigned long long num = 144; // 144 = 1*12^2
    Twelve t = Twelve::fromDecimal(num);
    EXPECT_EQ(t.toString(), "100");
}

TEST(TwelveTests, AdditionWithCarry) {
    Twelve t1("B"); // 11
    Twelve t2("1"); // 1
    Twelve sum = t1.add(t2); // 11+1=12 -> "10"
    EXPECT_EQ(sum.toString(), "10");
}

TEST(TwelveTests, SubtractionWithZero) {
    Twelve t1("1A5");
    Twelve t2("0");
    Twelve diff = t1.sub(t2);
    EXPECT_EQ(diff.toString(), "1A5");
}

TEST(TwelveTests, CopyIndependence) {
    Twelve t1("A1");
    Twelve t2 = t1.copy();
    Twelve t3 = t2.add(Twelve("1"));
    EXPECT_NE(t1.toString(), t3.toString());
}