#ifndef RECURSIVE_ACKERMANN_H
#define RECURSIVE_ACKERMANN_H

#include <iostream>
#include <vector>
#include <cassert>

using ull = uint64_t;
using namespace std;

namespace ack_utils {
    // не вектора, а геделевы нумерации..
    using gnum = vector<ull>;

    void print(gnum x) {
        for (ull t : x) {
            cout << t << ' ';
        }
        cout << '\n';
    }

    ull is_prime(ull num) {
        for (ull i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return (num > 1);
    }

    // умеем считать только A(0, n). только такой стек считаем валидным.
    ull validate_ackermann(vector <ull> st) {
        return (ull)(st.size() == 2 && st[0] == 0);
    }
}

namespace ackermann {
    using namespace ack_utils;

    vector <ull> godel_to_list(ull num) {
        if (num == 1) return {0};

        vector <ull> result;
        ull p = 2;
        while (num > 1) {
            if (is_prime(p)) {
                ull cnt = 0;
                while (num % p == 0) {
                    cnt++;
                    num /= p;
                }
                result.push_back(cnt);
            }
            p++;
            while (!is_prime(p)) {
                p++;
            }
        }

        return result;
    }

    ull expected_branch(vector <ull> x) {
        assert(x.size() == 2);
        ull br1 = (x[0] == 0) * 1;
        ull br2 = (x[0] > 0 && x[1] == 0) * 2;
        ull br3 = (x[0] > 0 && x[1] > 0) * 3;
        return br1 + br2 + br3;
    }

    // применяем операции, пока все валидно.
    // если применить операцию нельзя - возвращаем {}
    vector <ull> apply_operations(vector <ull> mn, vector <ull> ops) {
        assert(mn.size() == 2);

        // optimization: if ops.back() != 0 return {}

        // когда выполняем операцию, думаем что делаем сразу 3 варианта, а потом U<3, ops[i]>
        // затем валидируем, была ли корректной эта операция

        for (ull depth = 0; depth < ops.size(); depth++) {
            ull prev = mn[mn.size() - 2];
            ull last = mn[mn.size() - 1];
            ull needed = expected_branch({prev, last});

            mn.erase(--mn.end());
            mn.erase(--mn.end());

            switch (ops[depth]) {
                case 1: {
                    mn.push_back(last + 1);
                    break;
                }
                case 2: {
                    mn.push_back(prev - 1);
                    mn.push_back(1);
                    break;
                }
                case 3: {
                    mn.push_back(prev - 1);
                    mn.push_back(prev);
                    mn.push_back(last - 1);
                    break;
                }
                default:
                    return {};
            }

            if (ops[depth] != needed) {
                return {};
            }

            if (mn.size() < 2) {
                return {};
            }
        }
        return mn;
    }

    vector <ull> apply_operations(vector <ull> mn, ull num) {
        return apply_operations(mn, godel_to_list(num));
    }

    ull eval_ackermann(vector <ull> st) {
        assert(validate_ackermann(st) == 1);
        return st.back() + 1;
    }

    // увеличиваем y, пока не встретим валидную последовательность операций и результирующий стек рекурсии
    ull mu_minimize(vector <ull> x, bool verbose) {
        ull y = 0;
        while (true) {
            if (verbose && y % 1000 == 0) {
                cout << "CHECK " << y << '\n';
            }
            if (validate_ackermann(apply_operations(x, y))) {
                return y;
            }
            y++;
        }
    }

    vector <ull> solve(vector <ull> test, bool verbose = false) {
        assert(test.size() == 2);
        ull y = mu_minimize(test, verbose);
        ull x = eval_ackermann(apply_operations(test, y));
        return {x, y};
    }
}

namespace ackermann2 {
    using namespace ack_utils;

    ull expected_branch(gnum x) {
        assert(x.size() == 2);
        ull br1 = (x[0] == 0) * 1;
        ull br2 = (x[0] > 0 && x[1] == 0) * 2;
        ull br3 = (x[0] > 0 && x[1] > 0) * 3;
        return br1 + br2 + br3;
    }

    ull eval_ackermann(gnum st) {
        assert(validate_ackermann(st) == 1);
        return st.back() + 1;
    }

    gnum iter(gnum x) {
        if (x.size() < 2) return {};

        ull prev = x[x.size() - 2];  // заменяем на безопасные рекурсивные операции tail и тп.
        ull last = x[x.size() - 1];
        x.erase(--x.end());  // безопасно делим
        x.erase(--x.end());

        ull needed = expected_branch({prev, last});
        // когда выполняем операцию, думаем что делаем сразу 3 варианта (через разные функции),
        // а потом U<3, needed>
        switch (needed) {
            case 1: {
                x.push_back(last + 1);
                break;
            }
            case 2: {
                x.push_back(prev - 1);
                x.push_back(1);
                break;
            }
            case 3: {
                x.push_back(prev - 1);
                x.push_back(prev);
                x.push_back(last - 1);
                break;
            }
            default:
                return {};
        }
        return x;
    }

    gnum recur(gnum x, ull depth) {
        // f
        if (depth == 0) {
            return x;
        }

        // g
        return iter(recur(x, depth - 1));
    }

    ull mu_minimize(gnum x, bool verbose) {
        ull y = 0;
        while (true) {
            if (verbose && y % 1000 == 0) {
                cout << "CHECK " << y << '\n';
            }
            gnum calc = recur(x, y);
            if (calc.size() == 2 && calc[0] == 0) {
                return y;
            }
            y++;
        }
    }

    gnum solve(gnum test, bool verbose = false) {
        assert(test.size() == 2);
        ull y = mu_minimize(test, verbose);
        ull x = eval_ackermann(recur(test, y));
        return {x, y};
    }
}

#endif //RECURSIVE_ACKERMANN_H
