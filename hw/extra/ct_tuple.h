#ifndef RECURSIVE_CT_TUPLE_H
#define RECURSIVE_CT_TUPLE_H

// compile time ull-list
namespace ct_tuple {
    using ull = uint64_t;

    template<ull ... A>
    struct tuple;

    template<>
    struct tuple<> {};

    using nil = tuple<>;

    template<ull a, ull ... V>
    struct tuple<a, V...> {
        static const ull head = a;
        using tail = tuple<V...>;
    };

    template<ull a>
    struct tuple<a> {
        static const ull head = a;
        using tail = nil;
    };

    template<typename T, typename = void>
    struct is_nil : std::true_type {};

    template<typename T>
    struct is_nil<T, decltype(std::declval<T>().head, void())> : std::false_type {};

    template<ull a, typename Ts>
    struct cons;

    template<ull a, ull ... Ts>
    struct cons<a, tuple<Ts...>> {
        using type = tuple<a, Ts...>;
    };

    template<typename TT, size_t k>
    uint64_t kth() {
        static_assert(!is_nil<TT>::value);

        if constexpr (k == 1) {
            return TT::head;
        } else {
            return kth<typename TT::tail, k - 1>();
        }
    }

    template<typename TT>
    struct head {
        static const ull value = TT::head;
    };

    /*template<>
    struct head<tuple<>> {
        using value = nil;
    };*/

    template<typename...TT>
    struct tail;

    /*template<>
    struct tail<> {
        using value = nil;
    };*/

    template<ull a, ull ... V>
    struct tail<tuple<a, V...>> {
        static const ull value = tail<tuple<V...>>::value;
    };

    template<ull a>
    struct tail<tuple<a>> {
        static const ull value = tuple<a>::head;
    };

    template<typename TT>
    struct length {
        static const size_t value = 1 + length<typename TT::tail>::value;
    };

    template<>
    struct length<tuple<>> {
        static const size_t value = 0;
    };

    // operator @
    template<typename TypeListOne, typename TypeListTwo>
    struct conc2;

    template<ull... TypesOne, ull... TypesTwo>
    struct conc2<tuple<TypesOne...>, tuple<TypesTwo...>> {
        using type = tuple<TypesOne..., TypesTwo...>;
    };
}

#endif //RECURSIVE_CT_TUPLE_H
