# Cplusplus-Program

## Run C++ Programs

_Note:_ when developing these programs I used using Linux Ubuntu 22.04 LTS

the vscode configuration assumes that you have g++ installed on your machine
and that it is located in the `/usr/bin/g++` directory

given if your on windows you'd likely have to change the configuration to where every cygwin is installed on your machine
or if you using vscode `CTRL + SHIFT + P` and type in `C/C++: Edit Configurations (UI)` and change the `compilerPath` to where your g++ is located if possible.

## How to run C++ Programs

```bash
g++ <name-of-file>.cpp -o <name-of-output-file> && ./<name-of-output-file>
```

Example:

```bash
g++ Clock.cpp -o Clock && ./Clock
```

I've added Configuration in the .vscode folder, however, I can't guarantee that it will work on those machines that are not running Linux Ubuntu 22.04 LTS
