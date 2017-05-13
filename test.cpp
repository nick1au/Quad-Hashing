#include "cmpt_error.h"
#include "Bigram.h"
//#include "Bigram_base.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // STL SORT


int main(){
	Bigram b;
	Bigram_key obj2, obj1, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10;
	string test = "Nick";
	for (int i = 0; i < 2; i++){
	obj1.first = "Nick";
	obj1.second = "L";

	b.put(obj1, 20);

	obj2.first = "Apple";
	obj2.second = "O";

	b.put(obj2, 20);

	obj3.first = "Lisa";
	obj3.second = "Y";

	b.put(obj3, 8);

	obj4.first = "Devin";
	obj4.second = "Y";

	b.put(obj4, 8);

	obj5.first = "Zoe";
	obj5.second = "P";

	b.put(obj5, 23);

	obj6.first = "Evan";
	obj6.second = "M";

	b.put(obj6, 28);

	obj7.first = "Ava";
	obj7.second = "L";

	b.put(obj7, 12);
	obj8.first = "Ben";
	obj8.second = "A";

	b.put(obj8, 28);

	obj9.first = "Inde";
	obj9.second = "A";

	b.put(obj9, 28);

	obj10.first = "KLklsdfkajds";
	obj10.second = "A";

	b.put(obj10, 20);

	obj10.first = "";
	obj10.second = "Z";

	b.put(obj10, 1);
}
	//b.remove(obj);
	//cout << endl << b.contains(obj);
	//obj.first = "Nick";
	//obj.second = "L";

	//b.put(obj, 12);

	cout << "BEGIN CONTAIN"<<endl << b.contains(obj1);
	cout << endl << b.contains(obj2);

	cout << endl << b.contains(obj3);
	cout << endl << b.contains(obj4);
	cout << endl << b.contains(obj5);
	cout << endl << b.contains(obj6);
	cout << endl << b.contains(obj7);
	cout << endl << b.contains(obj8);
	cout << endl << b.contains(obj9);
	cout << endl << b.contains(obj10);

	//b.remove(obj1);

	cout << endl << endl<<b.value_of(obj6);
	cout << endl << "min = "<<(b.min()).first << " ";
	//cout << endl << "MAX INDEX" << b.
	cout << endl << "max = "<<(b.max()).first << " ";
	//b.find_first_str(test, obj.first);

	//obj.first = "MOO";
	//obj.second = "Q";

	//b.put(obj, 13);

	std::cout << std::endl << "SIZE = " << b.size();
	std::cout << std::endl << "cAP  = " << b.capacity();
	std::cout << std::endl << "LF  = " << b.load_factor();

	//vector<int> asb;
	//asb.push_back(13);
	//asb.push_back(15);
	//int asb[5];
	//asb[0] = 15;
	//std::cout << asb.size() << " " << asb.capacity();
//	Bigram_base b_b;
	return 0;
}

