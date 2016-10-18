#include <functional>
#include <iostream>

// Scope Guard [1] for declarative control flow.
//
// See also [2, 3, 4, 5].
//
// [1] https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Scope_Guard
// [2] http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4189
// [3] https://www.youtube.com/watch?v=WjTrfoiB0MQ
// [4] http://stackoverflow.com/questions/48647/does-scopeguard-use-really-lead-to-better-code
// [5] https://github.com/facebook/folly/blob/master/folly/ScopeGuard.h

class ScopeGuard {
    bool dismiss_{false};
    std::function<void()> f_;

public:
    ScopeGuard(std::function<void()> f)
        : f_{f} {
    }

    void Dismiss() {
        dismiss_ = true;
    }

    ~ScopeGuard() {
        if (!dismiss_) {
            f_();
        }
    }
};

static void Foo(bool dismiss) {
    ScopeGuard guard([]{ std::cout << "stack unwinding in Foo!" << std::endl; });
    // do something useful here
    if (dismiss) {
        guard.Dismiss();
    }
    std::cout << "sup" << std::endl;
}

int main() {
    Foo(true);
    Foo(false);
}
