#include <iostream>
#include <string>
#include <cctype>
#include <compare>
#include <algorithm>

class CaseInsensitiveString {
private:
    std::string s;
    static char to_lower(char c) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
public:
    CaseInsensitiveString() = default;
    CaseInsensitiveString(const char* str) : s(str) {}
    CaseInsensitiveString(std::string str) : s(std::move(str)) {}
    std::weak_ordering operator<=>(const CaseInsensitiveString& other) const {
        for (size_t i = 0; i < std::min(s.length(), other.s.length()); ++i) {
            char c1 = to_lower(s[i]);
            char c2 = to_lower(other.s[i]);
            if (c1 < c2) return std::weak_ordering::less;
            if (c1 > c2) return std::weak_ordering::greater;
        }
        if (s.length() < other.s.length()) return std::weak_ordering::less;
        if (s.length() > other.s.length()) return std::weak_ordering::greater;
        return std::weak_ordering::equivalent;
    }
    bool operator==(const CaseInsensitiveString& other) const {
        return (*this <=> other) == 0;
    }
    const std::string& str() const { return s; }
};

std::ostream& operator<<(std::ostream& os, const CaseInsensitiveString& cis) {
    return os << cis.str();
}

int main() {
    CaseInsensitiveString s1("Hello");
    CaseInsensitiveString s2("HELLO");

    std::cout << std::boolalpha;
    std::cout << "s1 == s2: " << (s1 == s2) << " (Hello == HELLO)\n";

    std::cout << "s1 != s2: " << (s1 != s2) << '\n';

    std::cout << "s1 <= s2: " << (s1 <= s2) << " (Hello <= HELLO)\n";
    std::cout << "s1 >= s2: " << (s1 >= s2) << '\n';

    return 0;
}