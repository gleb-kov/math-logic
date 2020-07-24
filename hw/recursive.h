#ifndef RECURSIVE_RECURSIVE_H
#define RECURSIVE_RECURSIVE_H

#include <type_traits>
#include <cstdio>
#include <cassert>
#include "typelist.h"

namespace recursive {
    using ull = uint64_t;
}

namespace recursive::utils {
    template<typename T>
    constexpr bool is_natural = std::is_integral_v<T> && std::is_unsigned_v<T>;
}

namespace recursive::primitives {
    using namespace recursive::utils;

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct Z {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            return 0;
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct N {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            return x[0] + 1;
        }
    };

    template<size_t n, size_t k, typename T, typename = std::enable_if_t<is_natural<T>>>
    struct U {
        static ull compute(std::vector<T> x) {
            assert(x.size() == n);
            return x[k - 1];
        }
    };

    template<typename T, class f, class ...A>
    struct S;

    template<typename T, class f, class ...Args>
    struct S<T, f, TypeList<Args...>> {
        static ull compute(std::vector<T> x) {
            using G = TypeList<Args...>;
            ull ss = Length<G>::value;
            std::vector<ull> gtmp;
            for (size_t i = 0; i < ss; i++) {
                const unsigned int h = i;
                gtmp.push_back(TypeAt<0, G>::type::compute(x));
                using G = typename G::Tail;
            }
            return f::compute(gtmp);
        }
    };

    template<class f, class g1, typename T, typename = std::enable_if_t<is_natural<T>>>
    struct S1 {
        static ull compute(std::vector<T> x) {
            return f::compute({g1::compute(x)});
        }
    };

    template<class f, class g1, class g2, typename T, typename = std::enable_if_t<is_natural<T>>>
    struct S2 {
        static ull compute(std::vector<T> x) {
            return f::compute({g1::compute(x), g2::compute(x)});
        }
    };

    template<class f, class g1, class g2, class g3, typename T, typename = std::enable_if_t<is_natural<T>>>
    struct S3 {
        static ull compute(std::vector<T> x) {
            return f::compute({g1::compute(x), g2::compute(x), g3::compute(x)});
        }
    };

    template<class f, class g, typename T, typename = std::enable_if_t<is_natural<T>>>
    struct R {
        static ull compute(std::vector<T> x, T y) {
            if (y == 0) {
                return f::compute(x);
            }

            T z = R<f, g, T>::compute(x, y - 1);
            x.push_back(y - 1);
            x.push_back(z);
            return g::compute(x);
        }
    };

    template<class f, typename T, typename = std::enable_if_t<is_natural<T>>>
    struct M {
        static ull compute(std::vector<T> x) {
            x.push_back(0);
            while (f::compute(x) != 0) {
                x.back()++;
            }
            return x.back();
        }
    };
}

namespace recursive::operations {
    using namespace recursive::primitives;

    template<typename T, size_t n, typename = std::enable_if_t<is_natural<T>>>
    struct zero {
        static ull compute(std::vector<T> x) {
            static_assert(n > 0);
            assert(x.size() == n);
            return S1<Z<T>, U<n, 1, T>, T>::compute(x);
        }
    };

    template<typename T, size_t n, typename = std::enable_if_t<is_natural<T>>>
    struct one {
        static ull compute(std::vector<T> x) {
            static_assert(n > 0);
            assert(x.size() == n);
            return S1<S1<N<T>, Z<T>, T>, U<n, 1, T>, T>::compute(x);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct is_equal {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            return x[0] == x[1];
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct add {
        struct helper {
            static ull compute(std::vector<T> x) {
                assert(x.size() == 2);
                return x[0] + x[1];
            }
        };

        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            return S2<helper, U<2, 1, T>, U<2, 2, T>, T>::compute(x);
        }

        [[deprecated("WTF")]] static ull old(std::vector<T> x) {
            assert(x.size() == 2);
            using f = U<1, 1, T>;
            using g = S1<N<T>, U<3, 3, T>, T>;
            return R<f, g, T>::compute({x[0]}, x[1]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct mul {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = Z<T>;
            using g = S2<add<T>, U<3, 1, T>, U<3, 3, T>, T>;
            return R<f, g, T>::compute({x[0]}, x[1]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct bounded_sub1 {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using f = Z<T>;
            using g = U<3, 2, T>;
            return R<f, g, T>::compute({x[0]}, x[0]); // first arg is useless
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct bounded_sub {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = U<1, 1, T>;
            using g = S1<bounded_sub1<T>, U<3, 3, T>, T>;
            return R<f, g, T>::compute({x[0]}, x[1]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct less {
        // compare x[0] with 1 ... x[1] - 1
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = Z<T>;
            using stage = S2<is_equal<T>, U<3, 1, T>, U<3, 2, T>, T>;
            using g = S2<add<T>, stage, U<3, 3, T>, T>;
            return R<f, g, T>::compute({x[0]}, x[1]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct ifelse {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 3);
            using cond = U<3, 1, T>;
            using rcond = S2<bounded_sub<T>, one<T, 3>, cond, T>;

            return S2<add<T>,
                    S2<mul<T>, cond, U<3, 2, T>, T>,
                    S2<mul<T>, rcond, U<3, 3, T>, T>, T>::compute(x);
        }
    };

    template<size_t k, typename T, class F, typename = std::enable_if_t<is_natural<T>>>
    struct firstyy {
        template<size_t d>
        struct helper {
            static auto compute() {
                if constexpr (d == 1) return TypeList<U<k+2, d, T>>();
                else return Append<decltype(helper<d - 1>::compute()), U<k+2, d,T>>::type();
            }
        };

        static ull compute(std::vector<T> x) {
            assert(x.size() == k + 1);
            using f = U<k + 1, k + 1, T>; // return n

            using picker = typename Append<decltype(helper<k>::compute()), TypeList<U<k + 3,k + 2, T>>>::type;

            using cur = S<T, F, picker>;
            using verdict = S2<is_equal<T>, zero<T, k + 3>, cur, T>;
            using already = S2<is_equal<T>, U<k + 3, k + 3, T>, U<k + 3, k + 1, T>, T>; // tail of recursion == n

            // if !verdict
            using minstep = S3<ifelse<T>, already, U<k + 3, k + 2, T>, U<k + 3, k + 3,T>, T>;

            using g = S3<ifelse<T>, verdict, U<k + 3, k + 3, T>, minstep, T>;
            return R<f,g,T>::compute(x, x.back());
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct div {
        struct helper {
            // if x[0] >= x[1]*x[2] return x[2] (div times)
            // else return x[4] (verdict for less multipliers);
            static ull compute(std::vector<T> x) {
                assert(x.size() == 4);
                using step_mul = S1<N<T>, U<4, 3, T>, T>;
                using stage = S2<mul<T>, U<4, 2, T>, step_mul, T>;
                using verdict = S2<less<T>, U<4, 1, T>, stage, T>;
                return S3<ifelse<T>, verdict, U<4, 4, T>, step_mul, T>::compute(x);
            }
        };

        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = S3<ifelse<T>, less<T>, zero<T, 2>, one<T, 2>, T>;
            using g = helper;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct modulo {
        struct helper {
            // return (x[0] < x[1] ? x[0] : x[0] - x[1]);
            static ull compute(std::vector<T> x) {
                assert(x.size() == 2);
                using sub_lhs = S3<ifelse<T>, less<T>, zero<T, 2>, U<2, 2, T>, T>;
                return S2<bounded_sub<T>, U<2, 1, T>, sub_lhs, T>::compute(x);
            }
        };

        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = helper;
            using g = S2<helper, U<4, 4, T>, U<4, 2, T>, T>;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct pow {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = one<T, 1>;
            using g = S2<mul<T>, U<3, 1, T>, U<3, 3, T>, T>;
            return R<f, g, T>::compute({x[0]}, x[1]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct kth_bit {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using two = S1<N<T>, one<T, 2>, T>;

            using mask = S2<pow<T>, two, U<2, 2, T>, T>;
            using mask2 = S2<mul<T>, mask, two, T>;
            using suffix = S2<modulo<T>, U<2, 1, T>, mask2, T>;
            using rev = S2<less<T>, suffix, mask, T>;
            return S3<ifelse<T>, rev, zero<T, 2>, one<T, 2>, T>::compute(x);
        }
    };

    template<typename T, ull bits = 10, typename = std::enable_if_t<is_natural<T>>>
    struct bitwise_and {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = zero<T, 2>;
            using two = S1<N<T>, one<T, 4>, T>;

            using cur_bit1 = S2<kth_bit<T>, U<4, 1, T>, U<4, 3, T>, T>;
            using cur_bit2 = S2<kth_bit<T>, U<4, 2, T>, U<4, 3, T>, T>;
            using cur_bit = S2<mul<T>, cur_bit1, cur_bit2, T>;
            using mask_addend = S2<pow<T>, two, U<4, 3, T>, T>;
            using addend = S3<ifelse<T>, cur_bit, mask_addend, zero<T, 4>, T>;
            using g = S2<add<T>, U<4, 4, T>, addend, T>;
            return R<f, g, T>::compute(x, bits);
        }
    };

    template<typename T, ull bits = 10, typename = std::enable_if_t<is_natural<T>>>
    struct bitwise_xor {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = zero<T, 2>;
            using two = S1<N<T>, one<T, 4>, T>;

            using cur_bit1 = S2<kth_bit<T>, U<4, 1, T>, U<4, 3, T>, T>;
            using cur_bit2 = S2<kth_bit<T>, U<4, 2, T>, U<4, 3, T>, T>;
            using cur_bit = S2<is_equal<T>, cur_bit1, cur_bit2, T>;
            using mask_addend = S2<pow<T>, two, U<4, 3, T>, T>;
            using addend = S3<ifelse<T>, cur_bit, zero<T, 4>, mask_addend, T>;
            using g = S2<add<T>, U<4, 4, T>, addend, T>;
            return R<f, g, T>::compute(x, bits);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct plog {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using f = zero<T, 2>;

            using possible_k = S1<N<T>, U<4, 4, T>, T>;

            // 0 < n%(p**cur_step)
            using mod = S2<less<T>, zero<T, 4>,
                    S2<modulo<T>, U<4, 1, T>,
                            S2<pow<T>, U<4, 2, T>, possible_k, T>, T>, T>;

            using g = S3<ifelse<T>, mod, U<4, 4, T>, possible_k, T>;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct factorial {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using f = one<T, 1>;
            using g_helper = S1<N<T>, U<3, 2, T>, T>;  // pick (y-1)
            using g = S2<mul<T>, g_helper, U<3, 3, T>, T>;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct produce_pair {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using two = S1<N<T>, one<T, 2>, T>;
            using three = S1<N<T>, two, T>;
            return S2<mul<T>,
                    S2<pow<T>, two, U<2, 1, T>, T>,
                    S2<pow<T>, three, U<2, 2, T>, T>, T>::compute(x);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct pi_left {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using two = S1<N<T>, one<T, 1>, T>;
            return S2<plog<T>, U<1, 1, T>, two, T>::compute(x);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct pi_right {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using two = S1<N<T>, one<T, 1>, T>;
            using three = S1<N<T>, two, T>;
            return S2<plog<T>, U<1, 1, T>, three, T>::compute(x);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct is_prime {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using f = S2<less<T>, one<T, 1>, U<1, 1, T>, T>;
            using cur = S2<less<T>, zero<T, 3>,
                    S2<modulo<T>, U<3, 1, T>, U<3, 2, T>, T>, T>;
            using cur1 = S2<is_equal<T>, one<T, 3>, U<3, 2, T>, T>;
            using verdict = S2<add<T>, cur, cur1, T>;

            using g = S3<ifelse<T>, verdict, U<3, 3, T>, zero<T, 3>, T>;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct next_prime {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using f = U<1, 1, T>;

            using cur = S2<add<T>, U<3, 1, T>, U<3, 2, T>, T>;
            using curpr = S1<is_prime<T>, cur, T>;
            using was = S2<is_equal<T>, U<3, 1, T>, U<3, 3, T>, T>;
            using verdict = S2<mul<T>, curpr, was, T>;
            using g = S3<ifelse<T>, verdict, cur, U<3, 3, T>, T>;
            return R<f, g, T>::compute(x, x[0]);  // there's prime between k and 2*k
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct kth_prime {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using two = S1<N<T>, one<T, 1>, T>;
            using f = two;
            using g = S1<next_prime<T>, U<3, 3, T>, T>;
            return R<f, g, T>::compute(x, x[0]);  // first arg is useless
        }
    };
}

#endif //RECURSIVE_RECURSIVE_H
