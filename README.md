# PersistentDLLInjector

## Description
PersistentDLLInjector is a C++ Visual Studio project that implements a method for persistent DLL injection into Windows processes. It uses standard Windows APIs to open a process, allocate memory, write the DLL path, and start a remote thread to load the DLL.

🛠️ This tool was created for my personal learning and educational purposes only. It is not intended for malicious or illegal use.

## Note on Evasion
Even when using a known `meterpreter` shellcode, a simple XOR encoding layer is often enough to bypass Windows Defender and similar antivirus solutions. This project includes the ability to load XOR-encoded shellcode and decode it in memory prior to injection.

## Features
- Injects a DLL into a target process for persistent execution
- Uses Windows API for process manipulation
- Built using Visual Studio (x64 Debug configuration)

## File Structure
- `Project7.sln` - Visual Studio solution file
- `DLLInjector.cpp/` - Source code and project files
- `README.md` - This file

