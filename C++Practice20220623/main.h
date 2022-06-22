#include <type_traits>
#include <iterator>
#include <utility>
#include <concepts>
#include <iostream>


// bool�^�̒萔���ŃR���Z�v�g���`�ł��邽�߁A
// �^�����Ƃ��Ă��łɗp�ӂ���Ă���萔�������b�v���ăR���Z�v�g���`�ł���
template <class T>
concept Integral = std::is_integral_v<T>;
//std::is_integral_v<T>; T�������l�H

// 2�ȏ�̃e���v���[�g�p�����[�^���Ƃ�R���Z�v�g����`�ł���
template <class T, class U>
concept EqualityComparable = requires (T a, U b) {
	{a == b} -> std::convertible_to<bool>; // ���̖߂�l�^������ł��� (���ڂ̖߂�l�^�͎w��ł��Ȃ�)
	//std::convertible_to�@�ϊ��\�H
};

// �߂�l�^�̗v���ɂ́A���ڂ̌^�����łȂ��R���Z�v�g���w��ł���
template <class T, class U>
concept Addable = requires (T a, U b) {
	// ���Z�̌��ʂƂ��āA�^T�ƌ^U�̋��ʂ̌^���Ԃ邱��
	{a + b} -> std::common_with<T>;
	//std::common_with<T> �ǂ���̌^������ϊ��\�ȋ��ʂ̌^
};

// �Z�~�R������؂�ŕ����̗v����񋓂ł���
template <class T>
concept SequenceContainer = requires (T c) {
	typename T::size_type; // �^T�������o�^�Ƃ���size_type�������Ă��邱��
	{c.size()} -> std::convertible_to<typename T::size_type>;     // �^T�̃I�u�W�F�N�g�ɑ΂��ē���̃����o�֐����Ăяo���邱�Ƃ�v��
	{std::size(c)} -> std::convertible_to<typename T::size_type>; // �񃁃��o�֐��̌Ăяo�����v���ł���

	typename T::value_type;
	c.push_back(std::declval<typename T::value_type>());
	//std::declval �w�肵���^�̒l�����
};

//�u �^T��int����\�z�ł��邱�Ɓv��v�����鐧��
template <class T>
	requires std::constructible_from<T, int>&& std::move_constructible<T>
T make_from_int(int x) {
	return T(x);
}

// ���l�^(����or���������_��)�𔻒肷��R���Z�v�g
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

// �v���C�}���֐��e���v���[�g
void twice(auto) {
	std::cout << "*" << std::endl;
}

// ���l�^�ɑ΂��ėD�悳���֐��e���v���[�g
void twice(Number auto x) {
	std::cout << (x * 2) << std::endl;
}

// �����Ȃ������^�ɑ΂��čŗD�悳���֐��e���v���[�g
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

// �ϐ��e���v���[�g���A�����^�����������_���^���œ��ꉻ����B
template <class T>
constexpr T pi;

template <std::floating_point T>
constexpr T pi<T> = static_cast<T>(3.141592653589793);

template <std::integral T>
constexpr T pi<T> = static_cast<T>(3);