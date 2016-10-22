#include <iostream>
#include <iterator>
#include <string>

// https://contest.yandex.ru/contest/3016/problems/C/

// https://en.wikipedia.org/wiki/Esc_key
static constexpr char kEsc = 27;

namespace {
    enum class VimMode { kNormal, kInsert };

    class Vim {
        VimMode mode_{VimMode::kNormal};
        std::string screen_;
        size_t pos_{0};

     public:
        const std::string& GetScreen() const noexcept {
            return screen_;
        }

        void OnKeyPressed(const char key) {
            switch (mode_) {
                case VimMode::kNormal:
                    OnKeyPressedInNormalMode(key);
                    return;
                case VimMode::kInsert:
                    OnKeyPressedInInsertMode(key);
                    return;
            }
        }

     private:
        void MoveCursorLeft() noexcept {
            if (pos_) {
                --pos_;
            }
        }

        void MoveCursorRight() noexcept {
            if (pos_ < screen_.size()) {
                ++pos_;
            }
        }

        void InsertCharacter(const char character) {
            screen_.insert(pos_++, 1, character);
        }

        void OnKeyPressedInNormalMode(const char key) {
            switch (key) {
                case 'h':
                    MoveCursorLeft();
                    break;
                case 'l':
                    MoveCursorRight();
                    break;
                case 'i':
                    mode_ = VimMode::kInsert;
                    break;
                default:
                    break;
            }
        }

        void OnKeyPressedInInsertMode(const char key) {
            switch (key) {
                case kEsc:
                    mode_ = VimMode::kNormal;
                    break;
                default:
                    InsertCharacter(key);
                    break;
            }
        }
    };
}

static char ReadKey(std::istreambuf_iterator<char>& it) {
    const auto cur = *it++;
    if ('<' != cur) {
        return cur;
    }

    // points to E
    ++it;  // points to S
    ++it;  // points to C
    ++it;  // points to >
    ++it;  // points to next character
    return kEsc;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Vim vim;
    for (std::istreambuf_iterator<char> it{std::cin}, end{}; it != end;) {
        vim.OnKeyPressed(ReadKey(it));
    }
    std::cout << vim.GetScreen();
}
