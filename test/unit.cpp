#include "itsaunit.hpp"
#include <gtest/gtest.h>

TEST(TestIsDimensionallyEquivalent, Positive) {
  itsaunit::Metre distance { 1 };
  itsaunit::Metre distance2 { 1 };

  static_assert(itsaunit::IsDimensionallyEquivalent(distance, distance2),
      "IsDimensionallyEquivalent is not constexpr.");
  ASSERT_TRUE(itsaunit::IsDimensionallyEquivalent(distance, distance2));
}

TEST(TestIsDimensionallyEquivalent, Negative) {
  itsaunit::Metre distance { 1 };
  itsaunit::Second time { 1 };

  static_assert(!itsaunit::IsDimensionallyEquivalent(distance, time),
      "IsDimensionallyEquivalent is not constexpr.");
  ASSERT_FALSE(itsaunit::IsDimensionallyEquivalent(distance, time));
}

TEST(TestArithmetic, EquivalencePositive) {
  using namespace itsaunit::literals;
  const auto distance1 = 1.0_m;
  itsaunit::Metre distance2 = 1_m;

  ASSERT_EQ(distance1, distance2);
}

TEST(TestArithmetic, EquivalenceNegative) {
  itsaunit::Metre distance1 { 1 };
  itsaunit::Metre distance2 { 2 };

  ASSERT_NE(distance1, distance2);
}

TEST(Arithmetic, AdditionTrivial) {
  itsaunit::Metre distance1 { 1 };
  itsaunit::Metre distance2 { 1 };
  ASSERT_EQ(itsaunit::Metre{ 2 }, distance1 + distance2);
}

TEST(Arithmetic, MultiplicationTrivial) {
  itsaunit::Metre distance1 { 1 };
  itsaunit::Metre distance2 { 1 };
  const auto expected = itsaunit::Unit<0, 2, 0, 0, 0, 0, 0>{ 1 };
  ASSERT_EQ(expected, distance1 * distance2);
}

TEST(Stringification, PrettySimple) {
  using namespace itsaunit::literals;
  ASSERT_EQ("1m", itsaunit::to_string(1_m));
}

TEST(Stringification, PrettyWithAddition) {
  using namespace itsaunit::literals;
  ASSERT_EQ("2m", itsaunit::to_string(1_m + 1_m));
}

TEST(Stringification, PrettyWithMultiplication) {
  using namespace itsaunit::literals;
  ASSERT_EQ("1m²", itsaunit::to_string(1_m * 1_m));
}
