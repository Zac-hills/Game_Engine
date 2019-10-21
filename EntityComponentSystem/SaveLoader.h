#ifndef __SAVE_LOADER_H__
#define __SAVE_LOADER_H__

class SaveLoader
{
private:
	SaveLoader();
	~SaveLoader();
public:
	void Save(const char *FileName);
	void Load(const char *FilePath);
	static SaveLoader &getSaveLoader();

};


#endif