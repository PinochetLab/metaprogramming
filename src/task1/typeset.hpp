#pragma once
#include <cstddef>
#include <variant>

namespace cls03 {

    template<class... Ts> 
    struct typeset {};

    template<class Typeset>
    constexpr bool is_empty = true;

    template<class T, class ... Ts>
    constexpr bool is_empty<typeset<T, Ts...>> = false;

    template<class Typeset>
    constexpr size_t size = 0;

    template<class T, class ... Ts>
    constexpr size_t size<typeset<T, Ts...>> = 1 + size<typeset<Ts...>>;

    template<size_t N, class Typeset>
    struct GetStruct;

    template<class T, class ... Ts>
    struct GetStruct<0, typeset<T, Ts ...>> {
        using get = T;
    };

    template<size_t N, class T, class ... Ts>
    struct GetStruct<N, typeset<T, Ts ...>> {
        using get = typename GetStruct<N - 1, typeset<Ts ...>>::get;
    };

    template<size_t N, class Typeset>
    using get = typename GetStruct<N, Typeset>::get;
    
    template<class T, class Typeset>
    constexpr bool belongs_to = false;

    template<class A, class T>
    constexpr bool belongs_to<A, typeset<T>> = std::is_same_v<A, T>;

    template<class A, class T, class ... Ts>
    constexpr bool belongs_to<A, typeset<T, Ts ...>> = std::is_same_v<A, T> || belongs_to<A, typeset<Ts ...>>;

    template<class Ts1, class Ts2>
    struct AddStruct;

    template<class ... Ts1, class ... Ts2>
    struct AddStruct<typeset<Ts1 ...>, typeset<Ts2 ...>> {
        using add = typeset<Ts1 ..., Ts2 ...>;
    };

    template<class Ts1, class Ts2>
    using add = typename AddStruct<Ts1, Ts2>::add;

    template<class Ts1, class Ts2>
    struct JoinStruct;

    template<class Ts2>
    struct JoinStruct<typeset<>, Ts2> {
        using join = Ts2;
    };

    template<class T, class ... Ts1, class Ts2>
    struct JoinStruct<typeset<T, Ts1 ...>, Ts2> {
        using next = typename JoinStruct<typeset<Ts1 ...>, Ts2>::join;
        using join = typename std::conditional_t<belongs_to<T, Ts2>, next, add<typeset<T>, next>>;
    };

    template<class Ts1, class Ts2>
    using join = typename JoinStruct<Ts1, Ts2>::join;

    template<class Ts1, class Ts2>
    struct CrossStruct;

    template<class Ts2>
    struct CrossStruct<typeset<>, Ts2> {
        using cross = typeset<>;
    };

    template<class T, class ... Ts1, class Ts2>
    struct CrossStruct<typeset<T, Ts1 ...>, Ts2> {
        using next = typename CrossStruct<typeset<Ts1 ...>, Ts2>::cross;
        using cross = typename std::conditional_t<belongs_to<T, Ts2>, add<typeset<T>, next>, next>;
    };

    template<class Ts1, class Ts2>
    using cross = typename CrossStruct<Ts1, Ts2>::cross;

    template<class Ts1, class Ts2>
    struct SubtractStruct;

    template<class Ts2>
    struct SubtractStruct<typeset<>, Ts2> {
        using subtract = typeset<>;
    };

    template<class T, class ... Ts1, class Ts2>
    struct SubtractStruct<typeset<T, Ts1 ...>, Ts2> {
        using next = typename SubtractStruct<typeset<Ts1 ...>, Ts2>::subtract;
        using subtract = typename std::conditional_t<belongs_to<T, Ts2>, next, add<typeset<T>, next>>;
    };

    template<class Ts1, class Ts2>
    using subtract = typename SubtractStruct<Ts1, Ts2>::subtract;

    template<class Typeset>
    struct VariantOfStruct {
        using variant_of = std::variant<>;
    };

    template<class ... T>
    struct VariantOfStruct<typeset<T ...>> {
        using variant_of = std::variant<T ...>;
    };

    template<class Typeset>
    using variant_of = typename VariantOfStruct<Typeset>::variant_of;
}