#include "Leitor.h"


Leitor::Leitor()
{
}


Leitor::~Leitor()
{
}

void Leitor::LerImagemPasta(vector<Mat>& retorno, string pasta)
{
	vector<string> file = GetAllFilesNamesWithinFolder(pasta);
	for (unsigned i = 0; i < file.size(); i++)
	{
		string caminhoCompleto = pasta + "/" + file.at(i);

		Mat image = imread(caminhoCompleto.c_str());
		if (!image.data)
		{
			IplImage* img = cvLoadImage(caminhoCompleto.c_str());
			image = Mat(img);
		}
		if (image.data)
			retorno.push_back(image);
		caminhoCompleto.clear();
	}
}

vector<string> Leitor::GetAllFilesNamesWithinFolder(string folder)
{
	vector<string> names;
	char search_path[200];
	sprintf(search_path, "%s/*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}