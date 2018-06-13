#include <fstream>

#include "File.h"

namespace File
{
	void ReadFile(const char *filename, char **data, int *size)
	{
		std::ifstream in(filename, std::ifstream::binary);
		if (in.is_open())
		{
			in.seekg(0, std::ifstream::end);
			*size = static_cast<int>(in.tellg());
			in.seekg(0, std::ifstream::beg);

			*data = new char[*size];
			in.read(*data, *size);
		}
	}
}