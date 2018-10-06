#include "Util.h"

std::vector<string> ReadMyFile::ReadAllLine(string path)
{
	std::vector<string> lines;
	string line;

	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			lines.push_back(line);

		myfile.close();
	}

	return lines;
}

template <class T> void Memory::SafeDelete(T& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

template <class T> void Memory::SafeDeleteArr(T& t)
{
	if (t)
	{
		delete[] t;
		t = nullptr;
	}
}

template <class T> void Memory::SafeRelease(T& t)
{
	if (t)
	{
		t->Release();
		t = nullptr;
	}
}