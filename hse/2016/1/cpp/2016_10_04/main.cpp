#include <iostream>
#include <string>
#include <vector>

template <typename T = float>
class ComplexNumber {
    T real_{};
    T imaginary_{};

    /* Make private members of ComplexNumber<U> instantiation available to ComplexNumber<T>
     * instantiation when T != U.
     *
     * Btw, please read about class templates [1] and learn the difference between class template
     * and class template instantiation.
     *
     * http://en.cppreference.com/w/cpp/language/class_template
     */
    template <typename U>
    friend class ComplexNumber;
public:
    ComplexNumber() = default;
    ComplexNumber(const T real, const T imaginary)
        : real_{real}
        , imaginary_{imaginary} {
    }
    explicit ComplexNumber(const T real)
        : ComplexNumber{real, {}} {
    }

    template <typename U>
    ComplexNumber& operator=(const U other) {
        // T::operator=(const U other);
        real_ = other;
        return *this;
    }

    T& real() {
        return real_;
    }

    const T& real() const {
        return real_;
    }

    T& imaginary() {
        return imaginary_;
    }

    const T& imaginary() const {
        return imaginary_;
    }

    template <typename U>
    ComplexNumber& operator+= (const ComplexNumber<U>& other) {
        real_ += other.real_;
        imaginary_ += other.imaginary_;
        return *this;
    }

    template <typename U>
    ComplexNumber& operator-= (const ComplexNumber<U>& other) {
        real_ -= other.real_;
        imaginary_ -= other.imaginary_;
        return *this;
    }

    template <typename U>
    ComplexNumber& operator*= (const ComplexNumber<U>& other) {
        const auto new_real = (real_ * other.real_ - imaginary_ * other.imaginary_);
        const auto new_imaginary = (imaginary_ * other.real_ + real_ * other.imaginary_);
        real_ = new_real;
        imaginary_ = new_imaginary;
        return *this;
    }
};

template <typename T, typename U>
ComplexNumber<T> operator+(ComplexNumber<T> lhs, const ComplexNumber<U>& rhs) {
    return lhs += rhs;
}

template <typename T, typename U>
ComplexNumber<T> operator-(ComplexNumber<T> lhs, const ComplexNumber<U>& rhs) {
    return lhs -= rhs;
}

template <typename T, typename U>
ComplexNumber<T> operator*(ComplexNumber<T> lhs, const ComplexNumber<U>& rhs) {
    return lhs *= rhs;
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const std::vector<T>&) {
    return out << "[opetator<< for vector]";
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const ComplexNumber<T>& v) {
    out << '{' << v.real() << ';' << v.imaginary() << '}';
    return out;
}

int main() {
    {
        ComplexNumber<> x;
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<> x{1, 2};
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<> x{1};
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<> x{1};
        std::cout << x.real() << ' ' << x.imaginary() << std::endl;
    }
    {
        const ComplexNumber<> x{1};
        std::cout << x.real() << ' ' << x.imaginary() << std::endl;
    }
    {
        ComplexNumber<> x{1};
        std::cout << static_cast<const ComplexNumber<>&>(x).real()
                  << ' ' << x.imaginary() << std::endl;
    }
    {
        ComplexNumber<> x{1};
        std::cout << x.real()
                  << ' ' << static_cast<const ComplexNumber<>&>(x).imaginary() << std::endl;
    }
    {
        ComplexNumber<int> x{1, 2};
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<int> x{1};
        std::cout << x.real() << ' ' << x.imaginary() << std::endl;
    }
    {
        const ComplexNumber<int> x{1};
        std::cout << x.real() << ' ' << x.imaginary() << std::endl;
    }
    {
        ComplexNumber<> x;
        std::cout << x << std::endl;
        x.real() = 1;
        x.imaginary() = 100500;

        ComplexNumber<> y = x;
        std::cout << y << std::endl;
    }
    {
        ComplexNumber<> x;
        std::cout << x << std::endl;
        x.real() = 1;
        x.imaginary() = 100500;

        ComplexNumber<> y;
        y = x;
        std::cout << y << std::endl;
    }
    {
        ComplexNumber<int> x;
        x = 100500;
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<float> x{1, 2};
        const ComplexNumber<int> y{10, 20};
        x += y;
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<float> x{1, 2};
        const ComplexNumber<int> y{10, 20};
        std::cout << (x + y) << std::endl;
    }
    {
        ComplexNumber<float> x{1, 0};
        const ComplexNumber<int> y{1, 0};
        x *= y;
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<float> x{1, 0};
        const ComplexNumber<int> y{1, 0};
        std::cout << (x * y) << std::endl;
    }
    {
        ComplexNumber<float> x{1, 0};
        const ComplexNumber<int> y{1, 1};
        x *= y;
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<float> x{1, 0};
        const ComplexNumber<int> y{1, 1};
        std::cout << (x * y) << std::endl;
    }
    {
        ComplexNumber<float> x{1, 1};
        const ComplexNumber<int> y{1, 1};
        x *= y;
        std::cout << x << std::endl;
    }
    {
        ComplexNumber<float> x{1, 1};
        const ComplexNumber<int> y{1, 1};
        std::cout << (x * y) << std::endl;
    }
}
