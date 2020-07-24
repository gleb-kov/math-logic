#ifndef RECURSIVE_TYPELIST_H
#define RECURSIVE_TYPELIST_H

namespace internal {
struct Void
{
};
} // internal

template<typename ...Args>
struct TypeList
{
    typedef internal::Void Head;
    typedef internal::Void Tail;
};

typedef TypeList<> EmptyTypeList;

template<typename H, typename ...T>
struct TypeList<H, T...>
{
    typedef H Head;
    typedef TypeList<T...> Tail;
};

template<typename TL>
struct IsEmpty : std::true_type
{
};

template<>
struct IsEmpty<TypeList<internal::Void, internal::Void>> :
    std::true_type
{
};

template<typename ...Args>
struct IsEmpty<TypeList<Args...>> :
    std::integral_constant<bool,
        std::is_same<typename TypeList<Args...>::Head, internal::Void>::value &&
        IsEmpty<typename TypeList<Args...>::Tail>::value>
{
};

template<typename TL>
struct Length :
    std::integral_constant<unsigned int, 0>
{
};

template<typename ...Args>
struct Length<TypeList<Args...>> :
    std::integral_constant<unsigned int,
        IsEmpty<TypeList<Args...>>::value
            ? 0
            : 1 + Length<typename TypeList<Args...>::Tail>::value>
{
};

template<unsigned int N, typename TL>
struct TypeAt
{
    typedef internal::Void type;
};

template<typename ...Args>
struct TypeAt<0, TypeList<Args...>>
{
    typedef typename TypeList<Args...>::Head type;
};

template<unsigned int N, typename ...Args>
struct TypeAt<N, TypeList<Args...>>
{
    static_assert(N < Length<TypeList<Args...>>::value, "N is too big");

    typedef typename TypeAt<N - 1, typename TypeList<Args...>::Tail>::type type;
};

template<typename TOrTL2, typename TL>
struct Append
{
};

template<typename T, typename ...Args>
struct Append<T, TypeList<Args...>>
{
    typedef TypeList<Args..., T> type;
};

template<typename ...Args1, typename ...Args2>
struct Append<TypeList<Args1...>, TypeList<Args2...>>
{
    typedef TypeList<Args2..., Args1...> type;
};

template<typename T, typename TL>
struct Add
{
};

template<typename T, typename ...Args>
struct Add<T, TypeList<Args...>>
{
	typedef TypeList<Args..., T> type;
};

// Пустой список
std::ostream& operator<<(std::ostream& ostr, EmptyTypeList)
{
	ostr << "{}";
	return ostr;
}

template<typename TL>
void PrintTypeListHelper(TL, std::ostream& ostr)
{
}

template<typename T>
void PrintTypeListHead(T, std::ostream& ostr)
{
	ostr << typeid(T).name();
}

template<typename ...Args>
void PrintTypeListHead(TypeList<Args...> tl, std::ostream& ostr)
{
	ostr << tl;
}

template<typename Head, typename ...Args>
void PrintTypeListHelper(TypeList<Head, Args...>, std::ostream& ostr)
{
	PrintTypeListHead(Head(), ostr);
	if(!IsEmpty<TypeList<Args...>>::value)
	{
		ostr << ' ';
		PrintTypeListHelper<Args...>(TypeList<Args...>(), ostr);
	}
}

template<typename ...Args>
std::ostream& operator<<(std::ostream& ostr, TypeList<Args...> tl)
{
	ostr << '{';
	PrintTypeListHelper(tl, ostr);
	ostr << '}';
	return ostr;
}

#endif //RECURSIVE_TYPELIST_H
