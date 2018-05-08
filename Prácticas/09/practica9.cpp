#include <iostream>
#include <bitset>

// www.binaryconvert.com/

using namespace std;

string ftos32(float f)
{
	union
	{
		float input;	// assumes sizeof(float) == sizeof(int)
		int   output;
	}    data;
	
	data.input = f;
	bitset<sizeof(float) * CHAR_BIT>bits(data.output);
	return bits.to_string();
}

string dtos64(double d)
{
	union
	{
		double input;	// assumes sizeof(double) == sizeof(long)
		long   output;
	}    data;
	
	data.input = d;
	bitset<sizeof(double) * CHAR_BIT>bits(data.output);
	return bits.to_string();
}

float s32tof(string s)
{
	assert(s.length() == 32);
	int n = 0;
	for(int i = 0; i < s.length(); ++i)
	{
		n |= (s[i] - 48) << i;
	}
	float f = *(float *)&n;
	return f;
}

double s64tod(string s)
{
	assert(s.length() == 64);
	unsigned long long x = 0;
	for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		x = (x << 1) + (*it - '0');
	}
	double d;
	memcpy(&d, &x, 8);
	return d;
}

int main()
{
	string s32 = ftos32(4194304.45);
	string s64 = dtos64(4194304.45);
	cout << s32 << endl;
	cout << s64 << endl;
	cout << s32tof(s32) << endl;
	cout << s64tod(s64) << endl;
}
