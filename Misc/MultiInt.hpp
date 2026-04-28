#pragma once

template <typename... Ints>
struct MultiInt {
    std::tuple<Ints...> v;
    MultiInt() = default;
    template <typename T> requires std::is_integral_v<T>
    MultiInt(T x) : v{ Ints(x)... } {}
    MultiInt(Ints... args) : v{args...} {}
    MultiInt(std::tuple<Ints...> t) : v(t) {}
    MultiInt& operator+=(const MultiInt& o) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            ((std::get<I>(v) += std::get<I>(o.v)), ...);
        }(std::index_sequence_for<Ints...>{});
        return *this;
    }
    MultiInt& operator-=(const MultiInt& o) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            ((std::get<I>(v) -= std::get<I>(o.v)), ...);
        }(std::index_sequence_for<Ints...>{});
        return *this;
    }
    MultiInt& operator*=(const MultiInt& o) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            ((std::get<I>(v) *= std::get<I>(o.v)), ...);
        }(std::index_sequence_for<Ints...>{});
        return *this;
    }
    MultiInt& operator/=(const MultiInt& o) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            ((std::get<I>(v) /= std::get<I>(o.v)), ...);
        }(std::index_sequence_for<Ints...>{});
        return *this;
    }
    MultiInt operator+(const MultiInt& o) const { auto res = *this; return res += o; }
    MultiInt operator-(const MultiInt& o) const { auto res = *this; return res -= o; }
    MultiInt operator*(const MultiInt& o) const { auto res = *this; return res *= o; }
    MultiInt operator/(const MultiInt& o) const { auto res = *this; return res /= o; }
    bool operator==(const MultiInt& o) const requires requires { v == o.v; } {
        return v == o.v;
    }
    std::strong_ordering operator<=>(const MultiInt& o) const requires requires { v <=> o.v; } {
        return v <=> o.v;
    }
    friend ostream& operator<<(ostream& os, const MultiInt& obj) {
        std::apply([&os](const auto&... args) {
            bool first = true;
            ((os << (first ? "" : " ") << args, first = false), ...);
        }, obj.v);
        return os;
    }
};
