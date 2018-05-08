//
//  practica5.cpp
//  C++
//
//  Created by Roberto Ariosa Hernández on 10/04/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

string GetBinaryStringFromHexString (string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length (); ++i)
	{
		switch (sHex [i])
		{
			case '0': sReturn.append ("0000"); break;
			case '1': sReturn.append ("0001"); break;
			case '2': sReturn.append ("0010"); break;
			case '3': sReturn.append ("0011"); break;
			case '4': sReturn.append ("0100"); break;
			case '5': sReturn.append ("0101"); break;
			case '6': sReturn.append ("0110"); break;
			case '7': sReturn.append ("0111"); break;
			case '8': sReturn.append ("1000"); break;
			case '9': sReturn.append ("1001"); break;
			case 'a': sReturn.append ("1010"); break;
			case 'b': sReturn.append ("1011"); break;
			case 'c': sReturn.append ("1100"); break;
			case 'd': sReturn.append ("1101"); break;
			case 'e': sReturn.append ("1110"); break;
			case 'f': sReturn.append ("1111"); break;
		}
	}
	return sReturn;
}

//vector<bool, bitset<20>> MD (128);

int main() {
	
	string s;
	while (cin >> s) {
		bitset<32> b (GetBinaryStringFromHexString(s));
		string byteStr = b.to_string();
		bitset<5> byte (byteStr.substr(27,32));
		bitset<27> bloqueM (byteStr.substr(0,27));
		bitset<7> lineaMC (byteStr.substr(20,27));
		bitset<20> tag (byteStr.substr(0,20));
		
		cout << hex << b.to_ulong() << endl;
		cout << "byte: " << hex << byte.to_ulong() << endl;
		cout << "bloqueM: " << hex << bloqueM.to_ulong() << endl;
		cout << "linea MC: " << hex << lineaMC.to_ulong() << endl;
		cout << "tag: " << hex << tag.to_ulong() << endl;
		cout << endl;
	}
}
