#pragma once
#include <string>
#include <typeinfo>

class BaseScript
{
public:
	virtual ~BaseScript() {};
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Oncollision() {};
	virtual void OnDestroy() {};

	std::string ScriptName() 
	{
		std::string Result(typeid(*this).name());
		std::size_t pos = Result.find(" ");
		Result = Result.substr(pos + 1);
		return Result;
	}
};