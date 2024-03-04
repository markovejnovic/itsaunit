#ifndef ITSAUNIT_DETAIL_STRINGIFY_HPP
#define ITSAUNIT_DETAIL_STRINGIFY_HPP

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace itsaunit {
namespace detail {

template<int64_t Order, bool Pretty = true>
auto stringify_order(const char* const UnitInQuestion) -> std::string {
  if constexpr (Order == 0) { return ""; }
  if constexpr (Order == 1) {
    return std::to_string(Order) + std::string(UnitInQuestion);
  }

  if constexpr (Pretty) {
    static constexpr std::array<std::string_view, 10> UTF8_SUPER_DIGITS = {
      "⁰",
      "¹",
      "²",
      "³",
      "⁴",
      "⁵",
      "⁶",
      "⁷",
      "⁸",
      "⁹"
    };
    static constexpr const std::string_view UTF8_SUPER_MINUS = { "⁻" };

    std::string workStr; 
    int64_t workNum = Order;

    while (workNum != 0) {
      constexpr auto BASE = 10;
      const auto digit = workNum % BASE;

      // TODO(markovejnovic): Performance here is pretty bad.
      workStr = std::string(UTF8_SUPER_DIGITS[digit]) + workStr;

      workNum /= BASE;
    }

    workStr = std::string(UnitInQuestion)
      + (Order < 0 ? std::string(UTF8_SUPER_MINUS) : "")
      + workStr;

    return workStr;
  } else {
    return std::string(UnitInQuestion)
      + "^"
      + (Order < 0 ? "-(" + std::string(Order) + ")" : std::string(Order));
  }
}

} // namespace detail
} // namespace itsaunit

#endif // ITSAUNIT_DETAIL_STRINGIFY_HPP
