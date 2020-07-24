#ifndef RECURSIVE_GODEL_H
#define RECURSIVE_GODEL_H

#include "recursive.h"

namespace godel {
    using namespace recursive;
    using namespace recursive::operations;

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct nil {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 0);
            return 0;
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct head {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using two = S1<N<T>, one<T, 1>, T>;
            return S2<plog<T>, U<1, 1, T>, two, T>::compute(x);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct cons {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);

            using f = one<T, 1>;

            using prev_k = S1<kth_prime<T>, U<3, 2, T>, T>;
            using k = S1<next_prime<T>, prev_k, T>;
            using ln = S2<plog<T>, U<3, 1, T>, prev_k, T>;
            using remul = S2<pow<T>, k, ln, T>;
            using g = S2<mul<T>, remul, U<3, 3, T>, T>;

            using two = S1<N<T>, one<T, 2>, T>;
            using h = S2<pow<T>, two, U<2, 1, T>, T>;

            ull lhs = h::compute(x);
            ull rhs = R<f, g, T>::compute({x[1]}, x[1]);
            return mul<T>::compute({lhs, rhs});
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct tail {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using f = zero<T, 1>;

            using k = S1<kth_prime<T>, U<3, 2, T>, T>;
            using step = S2<is_equal<T>, zero<T, 3>, S2<modulo<T>, U<3, 1, T>, k, T>, T>;
            using elem = S2<plog<T>, U<3, 1, T>, k, T>;
            using g = S3<ifelse<T>, step, elem, U<3, 3, T>, T>;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct kth {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);
            using kp = S1<kth_prime<T>, U<2, 2, T>, T>;
            return S2<plog<T>, U<2, 1, T>, kp, T>::compute(x);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct len {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 1);
            using f = S2<less<T>, zero<T, 1>, U<1, 1, T>, T>;
            using k = S1<kth_prime<T>, S1<bounded_sub1<T>, U<3, 2, T>, T>, T>;
            using step = S2<is_equal<T>, zero<T, 3>, S2<modulo<T>, U<3, 1, T>, k, T>, T>;
            using g = S3<ifelse<T>, step, U<3, 2, T>, U<3, 3, T>, T>;
            return R<f, g, T>::compute(x, x[0]);
        }
    };

    template<typename T, typename = std::enable_if_t<is_natural<T>>>
    struct concatenate {
        static ull compute(std::vector<T> x) {
            assert(x.size() == 2);

            using f = one<T, 2>;

            using prev_k = S1<kth_prime<T>, U<4, 3, T>, T>;
            using k = S1<kth_prime<T>, S2<add<T>, U<4, 3, T>, U<4, 2, T>, T>, T>;
            using ln = S2<plog<T>, U<4, 1, T>, prev_k, T>;
            using remul = S2<pow<T>, k, ln, T>;
            using g = S2<mul<T>, remul, U<4, 4, T>, T>;

            ull llen = S1<len<ull>, U<2, 1, T>, T>::compute(x);
            ull lhs = S3<ifelse<T>,
                    S2<is_equal<T>, zero<T, 2>, U<2, 1, T>, T>,
                    S2<less<T>, zero<T, 2>, U<2, 2, T>, T>,
                    U<2, 1, T>, T>::compute(x);

            ull rhs = R<f, g, T>::compute({x[1], llen}, x[1]);

            return mul<T>::compute({lhs, rhs});
        }
    };
}

#endif //RECURSIVE_GODEL_H
