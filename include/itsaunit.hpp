#ifndef ITSAUNIT_HPP
#define ITSAUNIT_HPP

#include "detail/stringify.hpp"
#include <cmath>
#include <cstdint>
#include <ratio>
#include <string>
#include <type_traits>

#ifndef ITSAUNIT_DEFAULT_REPTYPE
#  define ITSAUNIT_DEFAULT_REPTYPE double
#endif

namespace itsaunit {

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class Rep = ITSAUNIT_DEFAULT_REPTYPE,
  class Ratio = std::ratio<1>
> class Unit {
public:
  using rep = Rep;
  using ratio = Ratio;

  constexpr Unit(Rep numericValue) : value_(numericValue) {}

  template<class ORep, class ORatio>
  [[nodiscard]] constexpr explicit operator Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder, KelvinOrder,
    MoleOrder, CandelaOrder, ORep, ORatio
  >() const {
    return {
      static_cast<ORep>(value_)
    };
  }

private:
  Rep value_;

  template<
    int64_t OSecondOrder, int64_t OMetreOrder, int64_t OKilogramOrder,
    int64_t OAmpereOrder, int64_t OKelvinOrder, int64_t OMoleOrder,
    int64_t OCandelaOrder, class ORep, class ORatio,
    bool OPretty
  >
  friend auto to_string(
    const Unit<
      OSecondOrder, OMetreOrder, OKilogramOrder, OAmpereOrder,
      OKelvinOrder, OMoleOrder, OCandelaOrder, ORep, ORatio
    >& operand
  ) -> std::string;

  template<
    int64_t OSecondOrder, int64_t OMetreOrder, int64_t OKilogramOrder,
    int64_t OAmpereOrder, int64_t OKelvinOrder, int64_t OMoleOrder,
    int64_t OCandelaOrder,
    class ORepLhs, class ORatioLhs,
    class ORepRhs, class ORatioRhs
  >
  friend constexpr auto operator+(
    const Unit<
      OSecondOrder, OMetreOrder, OKilogramOrder, OAmpereOrder,
      OKelvinOrder, OMoleOrder, OCandelaOrder, ORepLhs, ORatioLhs
    >& lhs,
    const Unit<
      OSecondOrder, OMetreOrder, OKilogramOrder, OAmpereOrder,
      OKelvinOrder, OMoleOrder, OCandelaOrder, ORepLhs, ORatioRhs
    >& rhs
  ) -> Unit<
    OSecondOrder, OMetreOrder, OKilogramOrder, OAmpereOrder,
    OKelvinOrder, OMoleOrder, OCandelaOrder,
    std::common_type_t<ORepLhs, ORepRhs>,
    std::ratio_add<ORatioLhs, ORatioRhs>
  >;

  template<
    int64_t OSecondOrder, int64_t OMetreOrder, int64_t OKilogramOrder,
    int64_t OAmpereOrder, int64_t OKelvinOrder, int64_t OMoleOrder,
    int64_t OCandelaOrder,
    class ORepLhs, class ORatioLhs,
    class ORepRhs, class ORatioRhs
  >
  friend constexpr auto operator==(
    const Unit<
      OSecondOrder, OMetreOrder, OKilogramOrder, OAmpereOrder,
      OKelvinOrder, OMoleOrder, OCandelaOrder, ORepLhs, ORatioLhs
    >& lhs,
    const Unit<
      OSecondOrder, OMetreOrder, OKilogramOrder, OAmpereOrder,
      OKelvinOrder, OMoleOrder, OCandelaOrder, ORepLhs, ORatioRhs
    >& rhs
  ) -> bool;

  template<
    int64_t LhsSecondOrder, int64_t LhsMetreOrder, int64_t LhsKilogramOrder,
    int64_t LhsAmpereOrder, int64_t LhsKelvinOrder, int64_t LhsMoleOrder,
    int64_t LhsCandelaOrder,
    int64_t RhsSecondOrder, int64_t RhsMetreOrder, int64_t RhsKilogramOrder,
    int64_t RhsAmpereOrder, int64_t RhsKelvinOrder, int64_t RhsMoleOrder,
    int64_t RhsCandelaOrder,
    class LhsRep, class LhsRatio,
    class RhsRep, class RhsRatio
  >
  friend constexpr auto operator*(
    const Unit<
      LhsSecondOrder, LhsMetreOrder, LhsKilogramOrder,
      LhsAmpereOrder, LhsKelvinOrder, LhsMoleOrder,
      LhsCandelaOrder,
      LhsRep, LhsRatio
    >& lhs,
    const Unit<
      RhsSecondOrder, RhsMetreOrder, RhsKilogramOrder,
      RhsAmpereOrder, RhsKelvinOrder, RhsMoleOrder,
      RhsCandelaOrder,
      RhsRep, RhsRatio
    >& rhs
  ) ->
    Unit<
      LhsSecondOrder + RhsSecondOrder,
      LhsMetreOrder + RhsMetreOrder,
      LhsKilogramOrder + RhsKilogramOrder,
      LhsAmpereOrder + RhsAmpereOrder,
      LhsKelvinOrder + RhsKelvinOrder,
      LhsMoleOrder + RhsMoleOrder,
      LhsCandelaOrder + RhsCandelaOrder,
      std::common_type_t<LhsRep, RhsRep>,
      std::ratio_multiply<LhsRatio, RhsRatio>
    >;
};

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class Rep, class Ratio,
  bool Pretty = true
>
auto to_string(
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, Rep, Ratio
  >& operand
) -> std::string {
  return std::to_string(operand.value_)
    + detail::stringify_order<SecondOrder, Pretty>("s")
    + detail::stringify_order<MetreOrder, Pretty>("m")
    + detail::stringify_order<KilogramOrder, Pretty>("kg")
    + detail::stringify_order<AmpereOrder, Pretty>("A")
    + detail::stringify_order<KelvinOrder, Pretty>("K")
    + detail::stringify_order<MoleOrder, Pretty>("mol")
    + detail::stringify_order<CandelaOrder, Pretty>("cd")
  ;
}

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>
>
[[nodiscard]] constexpr auto operator-(
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, Rep, Ratio
  >& operand
) ->
  Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, Rep, Ratio
  > {
  return Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KilogramOrder, MoleOrder, CandelaOrder, Rep, Ratio
  > { - operand.value_ };
}

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class RepLhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioLhs = std::ratio<1>,
  class RepRhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioRhs = std::ratio<1>
>
[[nodiscard]] constexpr auto operator==(
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioLhs
  >& lhs,
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioRhs
  >& rhs
) -> bool {
  return
    std::common_type_t<RepLhs, RepRhs>(lhs.value_)
      == std::common_type_t<RepLhs, RepRhs>(rhs.value_);
}

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class RepLhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioLhs = std::ratio<1>,
  class RepRhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioRhs = std::ratio<1>
>
[[nodiscard]] constexpr auto operator!=(
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioLhs
  >& lhs,
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioRhs
  >& rhs
) -> bool {
  return !(lhs == rhs);
}

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class RepLhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioLhs = std::ratio<1>,
  class RepRhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioRhs = std::ratio<1>
>
[[nodiscard]] constexpr auto operator+(
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioLhs
  >& lhs,
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioRhs
  >& rhs
) ->
  Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder,
    std::common_type_t<RepLhs, RepRhs>,
    std::ratio_add<RatioLhs, RatioRhs>
  > {
  return Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KilogramOrder, MoleOrder, CandelaOrder,
    std::common_type_t<RepLhs, RepRhs>,
    std::ratio_add<RatioLhs, RatioRhs>
  > {
    std::common_type_t<RepLhs, RepRhs>(lhs.value_)
      + std::common_type_t<RepLhs, RepRhs>(rhs.value_)
  };
}

template<
  int64_t SecondOrder, int64_t MetreOrder, int64_t KilogramOrder,
  int64_t AmpereOrder, int64_t KelvinOrder, int64_t MoleOrder,
  int64_t CandelaOrder,
  class RepLhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioLhs = std::ratio<1>,
  class RepRhs = ITSAUNIT_DEFAULT_REPTYPE, class RatioRhs = std::ratio<1>
>
[[nodiscard]] constexpr auto operator-(
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioLhs
  >& lhs,
  const Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder, RepLhs, RatioRhs
  >& rhs
) ->
  Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KelvinOrder, MoleOrder, CandelaOrder,
    std::common_type_t<RepLhs, RepRhs>,
    std::ratio_subtract<RatioLhs, RatioRhs>
  > {
  return Unit<
    SecondOrder, MetreOrder, KilogramOrder, AmpereOrder,
    KilogramOrder, MoleOrder, CandelaOrder,
    std::common_type_t<RepLhs, RepRhs>,
    std::ratio_subtract<RatioLhs, RatioRhs>
  > {
    std::common_type<RepLhs, RepRhs>(lhs.value_)
      - std::common_type<RepLhs, RepRhs>(rhs.value_)
  };
}

template<
  int64_t LhsSecondOrder, int64_t LhsMetreOrder, int64_t LhsKilogramOrder,
  int64_t LhsAmpereOrder, int64_t LhsKelvinOrder, int64_t LhsMoleOrder,
  int64_t LhsCandelaOrder,
  int64_t RhsSecondOrder, int64_t RhsMetreOrder, int64_t RhsKilogramOrder,
  int64_t RhsAmpereOrder, int64_t RhsKelvinOrder, int64_t RhsMoleOrder,
  int64_t RhsCandelaOrder,
  class LhsRep = ITSAUNIT_DEFAULT_REPTYPE, class LhsRatio = std::ratio<1>,
  class RhsRep = ITSAUNIT_DEFAULT_REPTYPE, class RhsRatio = std::ratio<1>
>
[[nodiscard]] constexpr auto operator*(
  const Unit<
    LhsSecondOrder, LhsMetreOrder, LhsKilogramOrder,
    LhsAmpereOrder, LhsKelvinOrder, LhsMoleOrder,
    LhsCandelaOrder,
    LhsRep, LhsRatio
  >& lhs,
  const Unit<
    RhsSecondOrder, RhsMetreOrder, RhsKilogramOrder,
    RhsAmpereOrder, RhsKelvinOrder, RhsMoleOrder,
    RhsCandelaOrder,
    RhsRep, RhsRatio
  >& rhs
) ->
  Unit<
    LhsSecondOrder + RhsSecondOrder,
    LhsMetreOrder + RhsMetreOrder,
    LhsKilogramOrder + RhsKilogramOrder,
    LhsAmpereOrder + RhsAmpereOrder,
    LhsKelvinOrder + RhsKelvinOrder,
    LhsMoleOrder + RhsMoleOrder,
    LhsCandelaOrder + RhsCandelaOrder,
    std::common_type_t<LhsRep, RhsRep>,
    std::ratio_multiply<LhsRatio, RhsRatio>
  > {
  return {
    std::common_type_t<LhsRep, RhsRep>(lhs.value_)
      * std::common_type_t<LhsRep, RhsRep>(rhs.value_)
  };
}

template<
  int64_t LhsSecondOrder, int64_t LhsMetreOrder, int64_t LhsKilogramOrder,
  int64_t LhsAmpereOrder, int64_t LhsKelvinOrder, int64_t LhsMoleOrder,
  int64_t LhsCandelaOrder,
  int64_t RhsSecondOrder, int64_t RhsMetreOrder, int64_t RhsKilogramOrder,
  int64_t RhsAmpereOrder, int64_t RhsKelvinOrder, int64_t RhsMoleOrder,
  int64_t RhsCandelaOrder,
  class LhsRep = ITSAUNIT_DEFAULT_REPTYPE, class LhsRatio = std::ratio<1>,
  class RhsRep = ITSAUNIT_DEFAULT_REPTYPE, class RhsRatio = std::ratio<1>
>
[[nodiscard]] constexpr auto operator/(
  const Unit<
    LhsSecondOrder, LhsMetreOrder, LhsKilogramOrder,
    LhsAmpereOrder, LhsKelvinOrder, LhsMoleOrder,
    LhsCandelaOrder,
    LhsRep, LhsRatio
  >& lhs,
  const Unit<
    RhsSecondOrder, RhsMetreOrder, RhsKilogramOrder,
    RhsAmpereOrder, RhsKelvinOrder, RhsMoleOrder,
    RhsCandelaOrder,
    RhsRep, RhsRatio
  >& rhs
) ->
  Unit<
    LhsSecondOrder - RhsSecondOrder,
    LhsMetreOrder - RhsMetreOrder,
    LhsKilogramOrder - RhsKilogramOrder,
    LhsAmpereOrder - RhsAmpereOrder,
    LhsKelvinOrder - RhsKelvinOrder,
    LhsMoleOrder - RhsMoleOrder,
    LhsCandelaOrder - RhsCandelaOrder,
    std::common_type_t<LhsRep, RhsRep>,
    std::ratio_divide<LhsRatio, RhsRatio>
  > {
  return {
    std::common_type_t<LhsRep, RhsRep>(lhs.value_)
      / std::common_type_t<LhsRep, RhsRep>(rhs.value_)
  };
}

template<
  int64_t LhsSecondOrder, int64_t LhsMetreOrder, int64_t LhsKilogramOrder,
  int64_t LhsAmpereOrder, int64_t LhsKelvinOrder, int64_t LhsMoleOrder,
  int64_t LhsCandelaOrder,
  int64_t RhsSecondOrder, int64_t RhsMetreOrder, int64_t RhsKilogramOrder,
  int64_t RhsAmpereOrder, int64_t RhsKelvinOrder, int64_t RhsMoleOrder,
  int64_t RhsCandelaOrder,
  class LhsRep = ITSAUNIT_DEFAULT_REPTYPE, class LhsRatio = std::ratio<1>,
  class RhsRep = ITSAUNIT_DEFAULT_REPTYPE, class RhsRatio = std::ratio<1>
>
[[nodiscard]] constexpr auto IsDimensionallyEquivalent(
  const Unit<
    LhsSecondOrder, LhsMetreOrder, LhsKilogramOrder,
    LhsAmpereOrder, LhsKelvinOrder, LhsMoleOrder,
    LhsCandelaOrder,
    LhsRep, LhsRatio
  >& lhs,
  const Unit<
    RhsSecondOrder, RhsMetreOrder, RhsKilogramOrder,
    RhsAmpereOrder, RhsKelvinOrder, RhsMoleOrder,
    RhsCandelaOrder,
    RhsRep, RhsRatio
  >& rhs
) -> bool {
  return std::is_same_v<decltype(lhs), decltype(rhs)>;
}

namespace t {

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Second = Unit<1, 0, 0, 0, 0, 0, 0, Rep, Ratio>;

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Metre = Unit<0, 1, 0, 0, 0, 0, 0, Rep, Ratio>;

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Kilogram = Unit<0, 0, 1, 0, 0, 0, 0, Rep, Ratio>;

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Ampere = Unit<0, 0, 0, 1, 0, 0, 0, Rep, Ratio>;

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Kelvin = Unit<0, 0, 0, 0, 1, 0, 0, Rep, Ratio>;

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Mole = Unit<0, 0, 0, 0, 0, 1, 0, Rep, Ratio>;

template<class Rep = ITSAUNIT_DEFAULT_REPTYPE, class Ratio = std::ratio<1>>
using Candela = Unit<0, 0, 0, 0, 0, 0, 1, Rep, Ratio>;

} // namespace t

using Second = t::Second<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;
using Metre = t::Metre<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;
using Kilogram = t::Kilogram<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;
using Ampere = t::Ampere<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;
using Kelvin = t::Kelvin<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;
using Mole = t::Mole<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;
using Candela = t::Candela<ITSAUNIT_DEFAULT_REPTYPE, std::ratio<1>>;

namespace literals {

[[nodiscard]] constexpr auto operator""_s(
  long double val
) -> Second {
  return Second { t::Second<long double> { val } };
}

[[nodiscard]] constexpr auto operator""_s(
  unsigned long long int val
) -> Second {
  return Second { t::Second<unsigned long long int> { val } };
}

[[nodiscard]] constexpr auto operator""_m(
  long double val
) -> Metre {
  return Metre { t::Metre<long double> { val } };
}

[[nodiscard]] constexpr auto operator""_m(
  unsigned long long int val
) -> Metre {
  return Metre { t::Metre<unsigned long long int> { val } };
}

} // namespace literals

} // namespace itsaunit

#endif // ITSAUNIT_HPP
