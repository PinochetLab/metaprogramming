#pragma once

#include <iostream>
#include <cstddef>
#include <type_traits>

namespace cls03 {

    template<typename S, typename T>
    class is_streamable
    {
        template<typename SS, typename TT>
        static auto test(int)
            -> decltype(std::declval<SS&>() << std::declval<TT>(), std::true_type());
        template<typename, typename>
        static auto test(...) -> std::false_type;
    public:
        static const bool value = decltype(test<S, T>(0))::value;
    };

    template<class T>
    constexpr bool is_printable = true;

    template<class T>
    constexpr bool is_complete = true;


    template<class T, std::enable_if_t<
        std::is_integral_v<T>
        , bool> = true>
    void pretty_printer(std::ostream& ost, const T& t) {
        ost << typeid(t).name() << t;
    }

    template<class T, std::enable_if_t<
        std::is_floating_point_v<T>
        , bool> = true>
    void pretty_printer(std::ofstream& ost, const T& t) {
        ost << typeid(t).name() << std::fixed << t;
    }

    template<class T, std::enable_if_t<
        std::is_constructible_v<T, std::ostream&> && !(std::is_integral_v<T> || std::is_floating_point_v<T>)
        , bool> = true>
    void pretty_printer(std::ofstream& ost, const T& t) {
        ost << "some printable " << t;
    }

    template<class T, std::enable_if_t<
        std::is_trivial_v<T> && !std::is_constructible_v<T, std::ostream&>
        , bool> = true>
    void pretty_printer(std::ofstream& ost, const T& t) {
        size_t size = sizeof(t);
        ost << size << " bytes ";
        char* bytes = new char[sizeof(t)];
        for (size_t i = 0; i < size; i++) {
            ost << bytes[t];
        }
    }

    template<class T, std::enable_if_t<
        std::is_standard_layout_v<T> && !std::is_trivial_v<T>
        , bool> = true>
    void pretty_printer(std::ofstream& ost, const T& t) {
        ost << "some " << sizeof(t) << " bytes";
    }
}