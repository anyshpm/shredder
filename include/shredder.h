#include <string>
#include <list>
#include <wx/dir.h>

int EraseFileContent(const std::string file)
{
	FILE* f;
	long long i;

	f = fopen(file.c_str(), "a+");
	fseek(f, 0, SEEK_END);
	i = ftell(f);
	fclose(f);
	f = fopen(file.c_str(), "w+");

	// overwrite file content by "0"
	// if the cluster size of disk is not multiple of eight, file content may remain in disk.
	while (i > 0)
	{
		fwrite("00000000", 8, 1, f);
		i -= 8;
	}
	fclose(f);

	return wxRemoveFile(file);
}

int DeletePath(const std::string file)
{
	if (wxDirExists(file) == true)
	{
		std::list<std::string> fl;
		fl.push_back(file);
		while (fl.size() > 0)
		{
			wxString fn;
			wxString subfn;
			fn = fl.back();
			wxDir dir(fn);
			bool hasSubFile = false;

			if (dir.GetFirst(&subfn) == true)
			{
				do
				{
					wxString filename = dir.GetNameWithSep() + subfn;
					if (wxDirExists(filename) == true)
					{
						fl.push_back(std::string(filename.c_str()));
						hasSubFile = true;
					}
					else if (wxFileExists(filename) == true)
					{
						EraseFileContent(std::string(filename.c_str()));
					}
				}
				while (dir.GetNext(&subfn) == true);
			}

			if (hasSubFile == false)
			{
				fl.pop_back();
				wxRmdir(fn);
			}
		}
	}
	else if (wxFileExists(file) == true)
	{
		EraseFileContent(file);
	}

	return 0;
}
