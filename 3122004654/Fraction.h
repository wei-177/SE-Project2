#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;
typedef long long ll;
const int operatorLimit = 3; //������Ҫ���Ե�����ʽ���������
int numLimit, countLimit;//����̨����:���ִ�С���ƣ������ʽ����
class Fraction {
private:
	ll numerator, denominator;//�üٷ����洢
	void reduction() {//ͨ��
		if (denominator == 0) return;//��ĸΪ�����ʧ��
		ll numsign = 1, densign = 1;
		if (numerator < 0 && denominator < 0)
			numerator *= -1, denominator *= -1;
		else if (numerator < 0) {
			numsign *= -1;	numerator *= -1;
		}
		else if (denominator < 0) {
			densign *= -1;  denominator *= -1;
		}
		ll gcd = numerator, tmp, tmpdenominator = denominator;
		while (tmpdenominator != 0) {//������gcd,�������:gcd(0,x) = x
			tmp = gcd;
			gcd = tmpdenominator;
			tmpdenominator = tmp % tmpdenominator;
		}
		numerator /= gcd; denominator /= gcd;
		numerator *= numsign; denominator *= densign;
	}
public:
	Fraction() {//�޲ι����ʼ��ȫ0
		numerator = 0; denominator = 0;
	}
	Fraction(ll tmpnumerator, ll tmpdenominator) {//�вι���
		numerator = tmpnumerator; denominator = tmpdenominator;
		reduction();
	}
	Fraction(const Fraction& x) {//��������
		numerator = x.numerator; denominator = x.denominator;
	}
	void random_init() {
		denominator = rand() % numLimit + 1;//[1 ~ 10]
		numerator = rand() % (denominator * numLimit) + 1;//����/��ĸ (0 ~ 10]
		reduction();
	}
	bool error_check() {
		return denominator == 0;
	}
	string write() {
		if (error_check()) return "NaN";//������
		string ans;
		ll de = numerator / denominator, tmp = numerator - de * denominator;
		if (numerator >= denominator) {
			ans += to_string(de);
		}
		if (de == 0 && tmp == 0) {
			ans += "0";
		}
		else if (de != 0 && tmp != 0) {
			ans += "'" + to_string(tmp) + '/' + to_string(denominator);
		}
		else if (de == 0 && tmp != 0) {
			ans += to_string(tmp) + '/' + to_string(denominator);
		}
		return ans;
	}
	Fraction operator +(Fraction x) {
		Fraction ans;
		ans.denominator = denominator * x.denominator;
		ans.numerator = numerator * x.denominator + x.numerator * denominator;
		ans.reduction();
		return ans;
	}
	Fraction operator -(Fraction x) {
		Fraction ans;
		ans.denominator = denominator * x.denominator;
		ans.numerator = numerator * x.denominator - x.numerator * denominator;
		ans.reduction();
		return ans;
	}
	Fraction operator *(Fraction x) {
		Fraction ans;
		ans.numerator = numerator * x.numerator;
		ans.denominator = denominator * x.denominator;
		ans.reduction();
		return ans;
	}
	Fraction operator /(Fraction x) {
		Fraction ans;
		ans.numerator = numerator * x.denominator;
		ans.denominator = denominator * x.numerator;
		ans.reduction();
		return ans;
	}
	bool operator <(Fraction x) {
		return numerator * x.denominator < x.numerator* denominator;
	}
	bool operator <(ll x) {
		return numerator < x* denominator;
	}
};

Fraction autoCal(Fraction x, string op, Fraction y) {
	if (op == "+") return x + y;
	else if (op == "-") return x - y;
	else if (op == "*") return x * y;
	else if (op == "��") return x / y;
	else return Fraction();//���������,���ؿշ�����
}

