# exe-infector
CLI written in C++ to embed an exe inside another exe.

New exe file is produced with the same icon as the original file, which contains the original file and the potentially malicious payload as resources, which are both unpacked and launched when the file is opened.

* The “malicious” payload: currently, this can be an exe file or any other suitable format.
* This is for educational purposes only; use at your own risk

**Compile:**
```bash
g++ -o ExeInfector.exe main.cpp utils.cpp RCData.cpp copyIcon.cpp -mwindows -static
```

**Compile(if linux ):**
```bash
x86_64-w64-mingw32-g++ -o ExeInfector.exe main.cpp utils.cpp RCData.cpp copyIcon.cpp -mwindows -static
```

**Start(use wine, if you use Linux):**
```bash
ExeInfector.exe pack original.exe embedded.exe result.exe
```
