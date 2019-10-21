// CompilerInterface.h
#include <string>

namespace CompilerInterface {

	class __declspec(dllexport) Compiler
	{
	public:
		Compiler() {};
		~Compiler() {};
	//D:\\Desktop\\Repositories\\ECS\\DrunkenInsomnia\\Bin\\VsDevCmd.bat", "cl / D_USRDLL / D_WINDLL D : \\Desktop\\Repositories\\ECS\\DrunkenInsomnia\\Scripts\\TestScript.cpp / MT / link / DLL / OUT:Bin\\TestScript.dll
		static void Compile(std::string a_BatchFile, std::string a_ScriptPath);
	};
}
