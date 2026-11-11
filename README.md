# PersistentDLLInjector

A Windows security lab project written in C++. It explores what code can do when a DLL is loaded, including how it can arrange to run at sign-in and allocate executable memory.

## Source overview

- [DLLInjector.cpp](DLLInjector.cpp) contains the DLL entry point, startup shortcut logic, and an in-memory execution example.
- [Project7.sln](Project7.sln) is the Visual Studio solution.

Review the source in an isolated Windows lab. The project includes code that can change startup settings and execute an embedded payload.
