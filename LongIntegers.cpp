//Made by Anna Kravets, K-22
#include "LongIntegers.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
using namespace std;


LongInt::LongInt(string s, bool sign_) {
	sign = sign_;
	capacity = s.length();
	for (int i = capacity - 1; i >= 0; i--) {
		int x = s.at(i) - 48;
		digits.push_back(x);
	}
}

LongInt::LongInt(const vector<int>& myVec, bool sign_) {
	sign_ = sign;
	capacity = myVec.size();
	for (int i = 0; i < capacity; i++) {
		digits.push_back(myVec[i]);
	}
	int i = digits.size() - 1;
	while (i >= 1 && digits.at(i) == 0) {
		digits.pop_back();
		capacity--;
		i--;
	}
}

LongInt::LongInt(const LongInt& other) {
	*this = other;
}

LongInt::LongInt(LongInt&& other) {
	*this = other;
}


LongInt& LongInt::operator=(const LongInt& other) {
	if (this == &other)
		return *this;
	sign = other.sign;
	capacity = other.capacity;
	digits = {};
	for (int i = 0; i < capacity; i++) {
		this->digits.push_back(other[i]);
	}
	return *this;
}


LongInt& LongInt::operator=(LongInt&& other) {
	if (this == &other)
		return *this;
	sign = other.sign;
	capacity = other.capacity;
	digits = {};
	for (int i = 0; i < capacity; i++) {
		this->digits.push_back(other.digits.at(i));
	}
	return *this;
}


bool LongInt::operator>=(const LongInt& other) const {
	bool ans = true;
	if (capacity > other.capacity)
		ans = true;
	else if (other.capacity > capacity)
		ans = false;
	else {
		int i = capacity - 1;
		while (i >= 0 && digits[i] == other.digits[i]) {
			i--;
		}
		if (i == -1)
			ans = true;
		else if (digits[i] > other.digits[i])
			ans = true;
		else
			ans = false;
	}
	return ans;
}




LongInt LongInt::operator+(const LongInt& other)const {
	if (capacity == 0)
		return other;
	if (other.getCap() == 0)
		return *this;
	if (sign != other.getSign()) {
		LongInt res;
		if (sign) {
			res = *this - other;
		}
		else {
			res = other - *this;
		}
		return res;

	}
	int add = 0;
	int minCap = min(capacity, other.capacity);
	int maxCap = max(capacity, other.capacity);
	vector<int> newDigits;
	for (int i = 0; i < minCap; i++) {
		int x = digits.at(i) + other.digits.at(i) + add;
		newDigits.push_back(x%base);
		add = x / base;
	}
	int pos = minCap;
	while (pos<maxCap) {
		int x;
		if (other.capacity > capacity) {
			x = other.digits.at(pos) + add;
		}
		else {
			x = digits[pos] + add;
		}
		newDigits.push_back(x%base);
		add = x / base;
		pos++;
	}
	if (add > 0)
		newDigits.push_back(add);
	return LongInt(newDigits, this->getSign());
}

//function for ***subtraction***
LongInt func(const LongInt& first, const LongInt& other) {
	int subtr = 0;
	int minCap = min(first.getCap(), other.getCap());
	int maxCap = max(first.getCap(), other.getCap());
	vector<int> newDigits;
	for (int i = 0; i < minCap; i++) {
		int x = first[i] - other[i] - subtr;
		subtr = 0;
		if (x < 0) {
			x += base;
			subtr = 1;
		}
		newDigits.push_back(x);
	}
	int pos = minCap;
	while (pos<maxCap) {
		int x;
		if (other.getCap() > first.getCap()) {
			x = other[pos] - subtr;
		}
		else {
			x = first[pos] - subtr;
		}
		subtr = 0;
		if (x < 0) {
			x += base;
			subtr = 1;
		}
		newDigits.push_back(x);
		pos++;
	}
	return LongInt(newDigits);
}


//we do not care about signs in this operation
//supposing, we just should do
//abs(*this)-abs(other)
//though, the result might be negative
//I mean, we pay no attention to signs of *this or other
//but we do pay attention to the sign of result!!!
LongInt operator-(const LongInt& first, const LongInt& other) {
	LongInt ans;
	if (other.getCap() == 0 || first.getCap() == 0)
		ans = first;
	else if (first >= other)
		ans = func(first, other);
	else {
		ans = func(other, first);
		ans.setSign(false);
	}
	return ans;
}


LongInt LongInt:: operator/(int n) const {
	string newStr = "";
	int add = 0;
	for (int i = capacity - 1; i >= 0; i--) {
		int x = (add + digits[i]) / n;
		if (newStr != "" || x != 0)
			newStr = newStr + to_string(x);
		add = base*(add + digits[i] - x*n);
	}
	return LongInt(newStr, sign);
}

//множення на 1 "цифру" - n
LongInt LongInt::multiply(int n) const {
	if (n == 0 || capacity == 0)
		return LongInt("0");
	vector<int> newDigits;
	int add = 0;
	for (int i = 0; i < capacity; i++) {
		int x = digits.at(i)*n + add;
		newDigits.push_back(x%base);
		add = x / base;
	}
	if (add > 0)
		newDigits.push_back(add);
	return LongInt(newDigits);
}


//дописує в кінці числа x нульових розрядів
//якщо наше число - 0 або порожнє - то зсуву не відбувається!!!!!!
LongInt& LongInt::shift(int x) {
	if (x <= 0)
		return *this;
	if (string(*this) == "0" || capacity == 0) {
		return *this;
	}
	string newStr = string(*this);
	for (int i = 0; i < x; i++) {
		newStr = newStr + "0";
	}
	LongInt result(newStr);
	*this = result;
	return *this;
}

LongInt::operator string() const {
	string str = "";
	//It is good to include the sign
	//but it spoils ssoooo much
	//if (!sign)
	//str = str + "-";
	for (int i = capacity - 1; i >= 0; i--) {
		str = str + to_string(digits.at(i));
	}
	return str;
}

LongInt LongInt::operator *(const LongInt& other) {
	return m->mult(*this, other);
}

int LongInt::getCap() const {
	return capacity;
}

int LongInt::operator[](int i) const {
	return digits.at(i);
}

bool LongInt::getSign() const {
	return sign;
}

void LongInt::setSign(bool s) {
	sign = s;
}