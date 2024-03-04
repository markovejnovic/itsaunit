# itsaunit!

_It is infact a unit._

This is a zero-cost, blazing-fast library for adding dimensional type safety to
C++. I like [uom](https://docs.rs/uom/latest/uom/) quite a lot. It is a lot
more flexible than this system (I'm afraid you'll see). _itsaunit!_ attempts to
achieve feature parity with `uom` within the SI metric domain.

## License

**Everything in this repo is GPLv3 licensed :).**

## Getting Started

I'm getting tired working on this project in one continuous go, I'll keep this
brief...

```cpp
itsaunit::Metre distance1 { 1 };
const auto distance2 = 2_m;
const auto time_sq = 2_s * 2_s;
ASSERT_EQ("0.6666666ms⁻²", itsaunit::to_string((distance1 + distance2) / time_sq));
ASSERT_EQ("0.6666666ms^(-2)", itsaunit::to_string</* Pretty = */ false>((distance1 + distance2) / time_sq));
```
