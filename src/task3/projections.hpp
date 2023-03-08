#pragma once

#include <cstddef>
#include <type_traits>

namespace cls03 {

    template<size_t From, size_t To>
    struct range {
        static constexpr size_t size(){
            return To - From;
        }
        constexpr size_t operator()(size_t index) const {
            if (index > size() - 1) return size_t(-1);
            return From + index;
        }
    };

    template<class M1, class M2> struct concat {
        M1 m1;
        M2 m2;
        static constexpr size_t size() {
            return M1::size() + M2::size();
        }
        constexpr size_t operator()(size_t index) const {
            if (index > size() - 1) return size_t(-1);
            else if (index < M1::size()) return m1(index);
            else return m2(index - M1::size());
        }
    };

    template<class M1, class M2>
    constexpr auto operator + (M1, M2) {
        return concat<M1, M2>{};
    }

    template<size_t F, size_t C, size_t T>
    constexpr auto operator + (range<F, C>, range<C, T>) {
        return range<F, T>{};
    }

    template<class CL, size_t F, size_t C, size_t T>
    constexpr auto operator + (concat<CL, range<F, C>>, range<C, T>) {
        return CL{} + range<F, T>{};
    }

    template<class C1, class CL, class CR>
    constexpr auto operator + (C1, concat<CL, CR>) {
        return concat<concat<C1, CL>, CR>{};
    }

    template<class C1b, class C1e, class C2b, class C2e>
    constexpr auto operator + (concat<C1b, C1e>, concat<C2b, C2e>) {
        return ((C1b{} + C1e{}) + C2b{}) + C2e{};
    }
}
