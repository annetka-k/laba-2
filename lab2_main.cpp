//Made by Anna Kravets, K-22
#include "LongIntegers.h"
#include <iostream>
#include <iomanip>
using namespace std;


int main(){
	try {
		string s1, s2;
		cout<<"Testing MULTER\n";
		cout << "a="; cin >> s1;
		cout << "b="; cin >> s2;
		LongInt a(s1), b(s2), c;
		LongInt::m = new UsualMulter;
		c = b*a;
		cout << string(c) << endl;
		LongInt::m = new  KaratsubaMulter;
		c = b * a;
		cout << string(c) << endl;
		LongInt::m = new Toom3Multer;
		c = b*a;
		cout << string(c) << endl;
		LongInt::m = new StrassenMulter;
		c = b*a;
		cout << string(c) << endl;
		cout << "\nTesting DIVISION\n";
		cout << "Enter 2 numbers\n"; cin >> s1 >> s2;
		a = LongInt(s1); b = LongInt(s2);
		cout << "1/a=" << string(a.inverse()) << endl;
		cout << "1/b=" << string(b.inverse()) << endl;
		cout << "a/b=" << string(a / b) << endl;
		cout << "\nTesting if PRIME\n" << "N=";
		int n; cin >> n;
		cout << left;
		cout <<setw(18)<< "Lehmann: "<<setw(9)<<n;
		if (LehmannTest(n))
			cout <<setw(28)<<" is probably prime";
		else cout << setw(28) <<" is composite";
		cout <<endl<< setw(18)<<"Rabin-Miller: " << setw(9) << n;
		if (RabinMillerTest(n))
			cout << setw(28) <<" is probably prime";
		else cout << setw(28) <<" is composite";
		cout <<endl<<setw(18)<< "Solovay-Strassen: " << setw(9) << n;
		if (SolovayStrassenTest(n))
			cout << setw(28) <<" is probably prime";
		else cout << setw(28) <<" is composite";
		cout <<"\n\n";
	}
	catch (...) {
		cout << "Sorry, smthng is wrong(((!((\n";
	}
    return 0;
}