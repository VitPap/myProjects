#pragma once
#include <map>
#include <vector>

namespace StlAdaptors {

    template<typename integral_>
    concept integral = std::is_integral<integral_>::value;

    template <typename lambda_>
    concept lambda = requires { &lambda_::operator(); };

    template<typename function_>
    concept function = std::is_function_v<std::remove_pointer_t<std::remove_reference_t<function_>>> || lambda<function_>;

    template<typename container_>
    concept container = requires(container_ c) {
        typename container_::value_type;
    };

    template<typename T, typename TFunc>
    auto operator|(const T& data, TFunc func) {
        return func(data);
    }

    template<typename container_>
    concept AssociativeContainer = requires(container_ c) {
        typename container_::mapped_type;
        typename container_::key_type;
    };

    template <container T>
    auto reverse(T data) {
        auto iter = data.rbegin();
        auto end = data.rend();

        T result;

        while(iter != end) {
            result.push_back(*(iter++));
        }

        return result;
    }

    template <container T, integral TCount>
    auto take(T data, TCount n) {
        auto iter = data.begin();
        auto end = data.end();

        TCount cnt = 0;
        T result;

        while(cnt < n && iter != end) {
            cnt++;
            result.push_back(*(iter++));
        }

        return result;
    }

    template <container T, integral TCount>
    auto drop(T range, TCount n) {
        auto iter = range.begin();
        auto end = range.end();

        TCount cnt = 0;
        T result;

        while (iter != end) {
            cnt++;

            if (n < cnt) {
                result.push_back(*iter);
            }

            iter++;
        }

        return result;
    }

    template <container T, function TFunc>
    auto transform(T data, TFunc func) {
        auto iter = data.begin();
        auto end = data.end();

        T result;

        while(iter != end) {
            result.push_back(func(*(iter++)));
        }

        return result;
    }

    template <container T, function TFunc>
    auto filter(T data, TFunc func) {
        auto iter = data.begin();
        auto end = data.end();

        T result;

        while(iter != end) {
            if(func(*iter)) {
                result.push_back(*iter);
            }

            iter++;
        }

        return result;
    }

    template <AssociativeContainer T>
    auto keys(T data) {
        using TKey = std::remove_reference_t<decltype(data)>::key_type;

        std::vector<TKey> result;

        auto iter = data.begin();
        auto end = data.end();

        while (iter != end) {
            result.push_back((*(iter++)).first);
        }

        return result;
    }

    template <AssociativeContainer T>
    auto values(T data) {
        using TValue = std::remove_reference_t<decltype(data)>::mapped_type;
        std::vector<TValue> result;

        auto iter = data.begin();
        auto end = data.end();

        while (iter != end) {
            result.push_back((*(iter++)).second);
        }

        return result;
    }

    template<function TFunc>
    auto filter(TFunc predicate) {
        return [=](auto T) {
            static_assert(container<decltype(T)>, "Invalid type for filter");

            decltype(T) result;
            auto iter = T.begin();
            auto end = T.end();

            while (iter != end) {
                if (predicate(*iter)) {
                    result.push_back(*iter);
                }
                iter++;
            }

            return result;
        };
    }


    template<function TFunc>
    auto transform(TFunc func) {
        return [=](auto T) {
            static_assert(container<decltype(T)>, "Invalid type for transform");

            decltype(T) result;

            auto iter = T.begin();
            auto end = T.end();

            while (iter != end) {
                result.push_back(func(*(iter++)));
            }

            return result;
        };
    }

    template<integral TCount>
    auto take(TCount n) {
        return [=](auto T) {
            static_assert(container<decltype(T)>, "Invalid type for take");

            decltype(T) result;
            auto iter = T.begin();
            auto end = T.end();

            TCount cnt = 0;

            while (cnt < n && iter != end) {
                result.push_back(*(iter++));
                cnt++;
            }

            return result;
        };
    }

    template<integral TCount>
    auto drop(TCount n) {
        return [=](auto T) {
            static_assert(container<decltype(T)>, "Invalid type for drop");

            decltype(T) result;
            TCount cnt = 0;

            auto iter = T.begin();
            auto end = T.end();

            while (iter != end) {
                cnt++;
                if (n < cnt) {
                    result.push_back(*iter);
                }
                iter++;
            }

            return result;
        };
    }

    auto reverse() {
        return [=](auto T) {
            static_assert(container<decltype(T)>, "Invalid type for reverse");
            decltype(T) result;

            auto iter = T.rbegin();
            auto end = T.rend();

            while (iter != end) {
                result.push_back(*(iter++));
            }

            return result;
        };
    }

    auto keys() {
        return [=](auto T) {
            static_assert(AssociativeContainer<decltype(T)>, "Invalid type for keys");
            using TKey = std::remove_reference_t<decltype(T)>::key_type;

            std::vector<TKey> result;

            auto iter = T.begin();
            auto end = T.end();

            while (iter != end) {
                result.push_back((*(iter++)).first);
            }

            return result;
        };
    }

    auto values() {
        return [=](auto T) {
            static_assert(AssociativeContainer<decltype(T)>, "Invalid type for value");

            using TValue = std::remove_reference_t<decltype(T)>::mapped_type;

            std::vector<TValue> result;

            auto iter = T.begin();
            auto end = T.end();

            while (iter != end) {
                result.push_back((*(iter++)).second);
            }

            return result;
        };
    }
}