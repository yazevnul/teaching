#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

#include <cassert>
#include <cstdint>

template <typename T>
static constexpr
std::enable_if_t<std::is_unsigned<T>::value, T>
SetBit(const T value, const uint8_t index) noexcept {
    assert(index <= sizeof(T) * 8);
    return value | (T{1} << index);
}

template <typename T>
static constexpr
std::enable_if_t<std::is_unsigned<T>::value, bool>
GetBit(const T value, const uint8_t index) noexcept {
    assert(index <= sizeof(T) * 8);
    return value & (T{1} << index);
}

template <typename T>
static constexpr
std::enable_if_t<std::is_unsigned<T>::value, T>
ResetBit(const T value, const uint8_t index) noexcept {
    assert(index <= sizeof(T) * 8);
    return value & ~(T{1} << index);
}

template <typename T>
static constexpr
std::enable_if_t<std::is_unsigned<T>::value, T>
RotateLeft(const T value, const uint8_t index) noexcept {
    assert(index <= sizeof(T) * 8);
    return (value << index) | (value >> (sizeof(T) * 8 - index));
}

template <typename T>
static constexpr
std::enable_if_t<std::is_unsigned<T>::value, T>
RotateRight(const T value, const uint8_t index) noexcept {
    assert(index <= sizeof(T) * 8);
    return (value << (sizeof(T) * 8 - index)) | (value >> index);
}

template <typename T>
static
std::enable_if_t<std::is_unsigned<T>::value, std::string>
GetBitRepresentation(const T value) {
    std::string str;
    str.reserve(sizeof(T) * 8);
    for (ssize_t i = sizeof(T) * 8 - 1; i >= 0; --i) {
        str += GetBit(value, static_cast<uint8_t>(i)) ? '1' : '0';
    }
    return str;
}

template <typename T>
static
std::enable_if_t<std::is_unsigned<T>::value, bool>
IsPowerOfTwo(const T value) noexcept {
    return value != 0 && (value & (value - 1)) == 0;
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
    {
        Pad(std::cout) << IsPowerOfTwo(0u) << std::endl;
        Pad(std::cout) << IsPowerOfTwo(1u) << std::endl;
        Pad(std::cout) << IsPowerOfTwo(2u) << std::endl;
        Pad(std::cout) << IsPowerOfTwo(3u) << std::endl;
        Pad(std::cout) << IsPowerOfTwo(3u) << std::endl;
        // http://en.cppreference.com/w/cpp/types/numeric_limits
        Pad(std::cout) << IsPowerOfTwo(std::numeric_limits<uint32_t>::min()) << std::endl;
        Pad(std::cout) << IsPowerOfTwo(std::numeric_limits<uint32_t>::max()) << std::endl;
    }
}
