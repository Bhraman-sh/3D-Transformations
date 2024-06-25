@echo off

REM Compile the C program using GCC
g++ -o my_program.exe main.c src/transformations.c -Iinclude -IGraphics-Library -LGraphics-Library -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

REM Check if the compilation was successful
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)

REM Run the compiled program
my_program.exe
pause
