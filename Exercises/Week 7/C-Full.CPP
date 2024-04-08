#include <iostream>

class Hung_Str {
public:
    Hung_Str() : a(new char[10000]) {}

    Hung_Str(const char * str) : a(nullptr), len(0) {
        while (str[len] != '\0') {
            len++;
        }

        a = new char[10000];
        for (int i = 0; i <= len; ++i) {
            a[i] = str[i];
        }
    }

    ~Hung_Str() {
        delete[] a; 
    }

    inline size_t strlen() const {
        size_t len = 0;
        while (a[len++] != '\0') {}
        return --len;
    }

    inline char* strcpy() {
        char * result = new char[strlen() + 1];
        for (int i = 0; i < len; ++i)
            result[i] = a[i];
        result[len] = '\0';
    }

    template <class T>
    void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }

    inline void deleteChar(const char c) {
        char *fast = a, *slow = a;
        while (*slow != '\0') {
            if (*slow != c) {
                *fast = *slow;
                fast++;
            }
            slow++;
        }
        *fast = '\0';
        len = strlen();
    }

    inline void padRight(int n) {
        if (len >= n) return;
        char *move = (a + len);
        while (len < n) a[len++] = ' ';
        a[len] = '\0';
        len = n;
    }

    
    inline void padLeft(int n) {
        if (len >= n) return;
        int move = n - len;
        for (int i = len; i >= 0; --i)
            a[i + move] = a[i];
        for (int i = 0; i < move; ++i)
            a[i] = ' ';
        
        len = n;
    }

    inline void reverse() {
        char *left = a, *right = (a + len - 1);
        while (left < right) {
            swap(*left, *right);
            left++, right--;
        }
    }

    inline bool isPalindrome() {
        int i = 0, j = len - 1;
        while (i < j) {
            if (a[i] != a[j])
                return false;
            i++, j--;
        }
        return true;
    }

    inline void truncate(int n) {
        if (n >= len) return;
        a[n] = '\0';
        len = n;
    }

    inline void trim_left() {
        char *slow = a, *fast = a;
        while (*fast == ' ') fast++;
        while (*fast != '\0') {
            *slow = *fast;
            slow++, fast++;
        }

        *slow = '\0';
        len = strlen();
    }

    inline void trim_right() {
        char *fast = (a + len) - 1;
        while (*fast == ' ') fast--;
        *(++fast) = '\0';
        len = strlen();
    }

    friend std::istream& operator>>(std::istream& is, Hung_Str& str) {
        is >> str.a;
        str.len = str.strlen();
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Hung_Str& str) {
        os << str.a;
        return os;
    }

    Hung_Str& operator=(const char str[]) {
        delete[] a;
        
        len = 0;
        while (str[len] != '\0') len++;

        a = new char[len + 1];
        char *move = a;
        while (*str != '\0') {
            *move = *str;
            move++, str++;
        } *move = '\0';

        return *this;
    }

private:
    char * a;
    int len;
};

int main() {
    Hung_Str str = "aasdajdsh kjashjaksh";
    std::cout << "Main string: " << str << ".\n";
    str.reverse();
    std::cout << "Reversed string: " << str << ".\n";
    str.deleteChar('a');
    std::cout << "Deleted all 'a' character: " << str << ".\n";
    str.padLeft(20);
    std::cout << "Padded left(20): " << str << ".\n";
    str.padRight(25);
    std::cout << "Padded right(25): " << str << ".\n";
    str.truncate(18);
    std::cout << "Truncated to 18 character: " << str << ".\n";
    std::cout << "Is palindrome?: " << str.isPalindrome() << ".\n";
    str.trim_left();
    std::cout << "Trimmed left: " << str << ".\n";
    str.trim_right();
    std::cout << "Trimmed right: " << str << ".\n";

    return 0;
}
