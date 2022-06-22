#include <type_traits>
#include <iterator>
#include <utility>
#include <concepts>
#include <iostream>


// bool型の定数式でコンセプトを定義できるため、
// 型特性としてすでに用意されている定数式をラップしてコンセプトを定義できる
template <class T>
concept Integral = std::is_integral_v<T>;
//std::is_integral_v<T>; Tが整数値？

// 2つ以上のテンプレートパラメータをとるコンセプトも定義できる
template <class T, class U>
concept EqualityComparable = requires (T a, U b) {
	{a == b} -> std::convertible_to<bool>; // 式の戻り値型も制約できる (直接の戻り値型は指定できない)
	//std::convertible_to　変換可能？
};

// 戻り値型の要求には、直接の型だけでなくコンセプトも指定できる
template <class T, class U>
concept Addable = requires (T a, U b) {
	// 加算の結果として、型Tと型Uの共通の型が返ること
	{a + b} -> std::common_with<T>;
	//std::common_with<T> どちらの型からも変換可能な共通の型
};

// セミコロン区切りで複数の要求を列挙できる
template <class T>
concept SequenceContainer = requires (T c) {
	typename T::size_type; // 型Tがメンバ型としてsize_typeを持っていること
	{c.size()} -> std::convertible_to<typename T::size_type>;     // 型Tのオブジェクトに対して特定のメンバ関数が呼び出せることを要求
	{std::size(c)} -> std::convertible_to<typename T::size_type>; // 非メンバ関数の呼び出しも要求できる

	typename T::value_type;
	c.push_back(std::declval<typename T::value_type>());
	//std::declval 指定した型の値を取る
};

//「 型Tがintから構築できること」を要求する制約
template <class T>
	requires std::constructible_from<T, int>&& std::move_constructible<T>
T make_from_int(int x) {
	return T(x);
}

// 数値型(整数or浮動小数点数)を判定するコンセプト
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

// プライマリ関数テンプレート
void twice(auto) {
	std::cout << "*" << std::endl;
}

// 数値型に対して優先される関数テンプレート
void twice(Number auto x) {
	std::cout << (x * 2) << std::endl;
}

// 符号なし整数型に対して最優先される関数テンプレート
void twice(std::unsigned_integral auto x) {
	std::cout << (x * 2) << "u" << std::endl;
}

bool equal(std::integral auto a, std::integral auto b) {
	return a == b;
}

bool equal(std::floating_point auto a, std::floating_point auto b) {
	using T = std::common_type_t<decltype(a), decltype(b)>;
	return std::abs(a - b) <= std::numeric_limits<T>::epsilon();
}

// 変数テンプレートを、整数型か浮動小数点数型かで特殊化する。
template <class T>
constexpr T pi;

template <std::floating_point T>
constexpr T pi<T> = static_cast<T>(3.141592653589793);

template <std::integral T>
constexpr T pi<T> = static_cast<T>(3);