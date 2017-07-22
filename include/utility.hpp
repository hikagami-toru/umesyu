#ifndef UTILITY_HPP
#define UTILITY_HPP

template<typename>
struct Index {
    int data;
};

namespace util {

template<typename F>
void times(int n, F const& f) {
    for (int i = 0; i < n; ++i)
        f();
}

}

#endif // UTILITY_HPP
