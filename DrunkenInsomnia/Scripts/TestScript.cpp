#include <string>
#include <typeinfo>
#include "BaseScript.h"

class TestScript : public BaseScript
{
public:
	~TestScript() {};
	void Start() = 0;
	void Update() = 0;
	void Oncollision() {};
	void OnDestroy() {};

	std::string ScriptName()
	{
		std::string Result(typeid(*this).name());
		std::size_t pos = Result.find();
		Result = Result.substr(pos + 1);
		return Result;
	}
};
extern "C"
{
__declspec(dllexport) BaseScript * GetScript(){return new TestScript();}
}
