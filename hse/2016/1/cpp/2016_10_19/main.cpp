#include <iostream>
#include <string>

#include <cassert>
#include <cstdint>

// http://en.cppreference.com/w/cpp/language/operator_precedence
// http://en.cppreference.com/w/cpp/language/integer_literal

static constexpr uint32_t SetBit(const uint32_t value, const uint8_t index) noexcept {
    assert(index <= sizeof(uint32_t) * 8);
    return value | (uint32_t{1} << index);
}

static constexpr bool GetBit(const uint32_t value, const uint8_t index) noexcept {
    assert(index <= sizeof(uint32_t) * 8);
    return value & (uint32_t{1} << index);
}

static constexpr uint32_t ResetBit(const uint32_t value, const uint8_t index) noexcept {
    assert(index <= sizeof(uint32_t) * 8);
    return value & ~(uint32_t{1} << index);
}

// Should be reduced to exactly one assembly instruction.
//
// There is also a lot of compiler specific builtins [1].
//
// [1] https://gcc.gnu.org/onlinedocs/gcc-6.1.0/gcc/Other-Builtins.html
static constexpr uint32_t RotateLeft(const uint32_t value, const uint8_t index) noexcept {
    assert(index <= sizeof(uint32_t) * 8);
    return (value << index) | (value >> (sizeof(uint32_t) * 8 - index));
}

static constexpr uint32_t RotateRight(const uint32_t value, const uint8_t index) noexcept {
    assert(index <= sizeof(uint32_t) * 8);
    return RotateLeft(value, (sizeof(uint32_t) * 8 - index));
}

static std::string GetBitRepresentation(const uint32_t value) {
    std::string str;
    str.reserve(sizeof(uint32_t) * 8);
    for (ssize_t i = sizeof(uint32_t) * 8 - 1; i >= 0; --i) {
        str += GetBit(value, static_cast<uint8_t>(i)) ? '1' : '0';
    }
    return str;
}

static std::ostream& Pad(std::ostream& out) {
    return out << "\t\t";
}

int main() {
    {
        uint32_t x = 1;
        Pad(std::cout) << x << std::endl;
        Pad(std::cout) << SetBit(x, 8) << std::endl;
        std::cout << std::endl;
    }
    {
        uint32_t x = 1;
        Pad(std::cout) << GetBit(x, 0) << std::endl;
        Pad(std::cout) << GetBit(x, 1) << std::endl;
        Pad(std::cout) << GetBit(SetBit(x, 8), 8) << std::endl;
        std::cout << std::endl;
    }
    {
        uint32_t x = 1;
        Pad(std::cout) << GetBitRepresentation(x) << std::endl;
        Pad(std::cout) << GetBitRepresentation(SetBit(x, 8)) << std::endl;
        std::cout << std::endl;
    }
    {
        uint32_t x = 1;
        Pad(std::cout) << GetBitRepresentation(x) << std::endl;
        Pad(std::cout) << GetBitRepresentation(ResetBit(SetBit(SetBit(x, 8), 3), 8)) << std::endl;
        std::cout << std::endl;
    }
    {
        uint32_t x = 1;
        Pad(std::cout) << x << std::endl;
        // Pad(std::cout) << SetBit(x, 255) << std::endl; // assert failure
        std::cout << std::endl;
    }
    {
        uint32_t x = 100500;
        Pad(std::cout) << GetBitRepresentation(x) << std::endl;
        Pad(std::cout) << GetBitRepresentation(RotateLeft(x, 7)) << std::endl;
        Pad(std::cout) << GetBitRepresentation(RotateLeft(x, 27)) << std::endl;
        Pad(std::cout) << GetBitRepresentation(RotateLeft(x, 32)) << std::endl;
        std::cout << std::endl;
    }
    {
        uint32_t x = 100500;
        Pad(std::cout) << GetBitRepresentation(x) << std::endl;
        Pad(std::cout) << GetBitRepresentation(RotateRight(x, 7)) << std::endl;
        Pad(std::cout) << GetBitRepresentation(RotateRight(x, 27)) << std::endl;
        Pad(std::cout) << GetBitRepresentation(RotateRight(x, 0)) << std::endl;
        std::cout << std::endl;
    }
}
