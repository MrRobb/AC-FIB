#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define N_ASOC (INT_MAX / 64)
#define CACHE_SIZE_BYTES INT_MAX
#define CACHE_SIZE_LINES (INT_MAX / 64)
#define LINE_SIZE_BYTES 64

using namespace std;

bool is_miss(vector<int>& asoc, int lineaMC)
{
	auto it = find(asoc.begin(), asoc.end(), lineaMC);
	if (it == asoc.end()) {
		if (asoc.size() >= N_ASOC)
			asoc.erase(asoc.begin());
		asoc.push_back(lineaMC);
		return true;
	}
	else {
		asoc.erase(it);
		asoc.push_back(lineaMC);
		return false;
	}
}

int main()
{
	assert(LINE_SIZE_BYTES * CACHE_SIZE_LINES == CACHE_SIZE_BYTES);
	for (int limite = 1; limite <= 32; limite++)
	{
		int fallos = 0;
		vector<vector<int>> cache (CACHE_SIZE_LINES, vector<int> (0));
		cout << "Limite = " << limite;

		for (int i=0, j=0; j < 256*1000; j++)
		{
			if ((j % limite) == 0) i=0;
			// cout << "Acceso a: v[" << i << "]" << endl;
			int lineaMC = i / LINE_SIZE_BYTES;
			auto& asoc = cache[lineaMC % CACHE_SIZE_LINES];
			fallos += is_miss(asoc, lineaMC);
			i = i + CACHE_SIZE_BYTES;
		}

		for (auto& linea : cache) {
			if (linea.size() > N_ASOC) {
				cout << "ERROR" << endl;
			}
		}

		cout << " -> Fallos: " << fallos << endl;
	}
}
