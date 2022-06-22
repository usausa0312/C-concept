#include"main.h"

#include <string>
#include <vector>
#include <cassert>
#include <map>
#include <list>

int main() {

	static_assert(Integral<int>);//true
	static_assert(Integral<unsigned int>);//true
	static_assert(Integral<char>);//true
	//static_assert(Integral<float>);//false

	static_assert(EqualityComparable<int, int>);//true

	static_assert(Addable<std::string, char>);//true
	//static_assert(Addable<std::vector<int>, std::vector<double >>);//false

	static_assert(SequenceContainer<std::vector<int>>);//true
	static_assert(SequenceContainer<std::list<int>>);//true
	//static_assert(SequenceContainer<std::map<int,double>>);//false


	int a = make_from_int<int>(3);//true,int(3)が代入
	std::vector<int> b = make_from_int<std::vector<int>>(3);// true,vector<int>(3)が代入　メモリ確保となる

	assert(a == 3);
	//assert(a == 0);error
	assert(b.size() == 3);
	//assert(b.size() == 0);error

	//twice関数の優先順位が付けられる
	twice(int(3));
	twice(std::string("AAA"));
	twice(unsigned int(20));

	assert(equal(1, 1));
	assert(equal((0.1+0.2),0.3));// 等しいとみなされる。計算誤差によって 0.30000000000000004のような値になるが


	std::cout << pi<float> << std::endl;
	std::cout << pi<int> << std::endl;

	return 1;
}