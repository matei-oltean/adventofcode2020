# adventofcode2020

C++ solutions for the [Advent of Code 2020](https://adventofcode.com/2020).

## Build and Run

### Windows

Using MinGW:

```powershell
mkdir builds
cd builds
cmake -G "MinGW Makefiles" ..
mingw32-make.exe
```

Then run the executable that you need:

```powershell
cat ..\dayxx\input | .\dayxx\dayxx.exe
```

### Linux

```bash
mkdir builds && cd builds
cmake ..
make
```

Then run the executable that you need:

`cat ..\dayxx\input | .\dayxx\dayxx` or `./dayxx/dayxx < ../dayxx/input`