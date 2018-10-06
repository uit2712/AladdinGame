#include <list>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <d3dx9.h>
#include <Shlwapi.h>
#include <vector>

using namespace std;

namespace Memory
{
	template <class T> void SafeDelete(T& t);

	template <class T> void SafeDeleteArr(T& t);

	template <class T> void SafeRelease(T& t);
}

namespace ReadMyFile
{
	std::vector<string> ReadAllLine(string path);
}