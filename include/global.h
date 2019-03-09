
#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

namespace wiz {
	template <typename T> /// x is 10진수..
	inline T pos_1(const T x, const int base = 10) // 1�리 �계산
	{
		if (x >= 0) { return x % base; }// x - ( x / 10 ) * 10; }
		else { return (x / base) * base - x; }
		// -( x - ( (x/10) * 10 ) )
	}
	template <typename T> /// T <- char, int, long, long long...
	std::string toStr(const T x);
}


template <typename T> /// T <- char, int, long, long long...
std::string wiz::toStr(const T x) /// chk!!
{
	const int base = 10;
	if (base < 2 || base > 16) { return "base is not valid"; }
	T i = x;

	const int INT_SIZE = sizeof(T) << 3; ///*8
	char* temp = new char[INT_SIZE + 1 + 1]; /// 1 nullptr, 1 minus
	std::string tempString;
	int k;
	bool isMinus = (i < 0);
	temp[INT_SIZE + 1] = '\0'; ///문자�시..

	for (k = INT_SIZE; k >= 1; k--) {
		T val = pos_1<T>(i, base); /// 0 ~ base-1
		/// number to ['0'~'9'] or ['A'~'F']
		if (val < 10) { temp[k] = val + '0'; }
		else { temp[k] = val - 10 + 'A'; }

		i /= base;

		if (0 == i) { // �자.
			k--;
			break;
		}
	}

	if (isMinus) {
		temp[k] = '-';
		tempString = std::string(temp + k);//
	}
	else {
		tempString = std::string(temp + k + 1); //
	}
	delete[] temp;

	return tempString;
}
#endif
