@echo off

set Option=%1

setlocal enabledelayedexpansion
IF "%Option%"=="-h" (
    echo    -n { New Solution Name }
    echo    -b { Solution Name } { Test Input File Name } { Argument Keyword } { Answer Keyword }
) ELSE IF "%Option%"=="-n" (
    set SolutionName=%2
    if not exist !SolutionName!.cpp (
        copy Origin.const !SolutionName!.cpp
    )
    code !SolutionName!.cpp
) ELSE IF "%Option%"=="-b" (
    set SolutionName=%2
    "C:\Program Files\CMake\bin\cmake.EXE" -D TestName:STRING=!SolutionName! -B "c:/Users/sinsi/Desktop/CodingTest/build"
    "C:\Program Files\CMake\bin\cmake.EXE" --build "c:/Users/sinsi/Desktop/CodingTest/build" --config Debug --target ALL_BUILD -j 6

    set True="True"
    set False="False"
    set IsParam=True

    set TestInputFileName=%3
    set Argument=%4
    set Answer=%5
    set "Status="
    set "allLines="
    for /f "tokens=* delims=" %%a in (!TestInputFileName!.ini) do (
        set "Variable=%%a"

        IF "!Variable!"=="!Argument!" (
            set "Status=!Argument!"
        ) ELSE IF "!Variable!"=="!Answer!" (
            set "Status=!Answer!"
        ) ELSE (
            IF "!Status!"=="!Argument!" (
                set "allLines=!allLines! %%a"
            ) ELSE IF "!Status!"=="!Answer!" (
                @echo on
                echo Result
                ( echo !allLines! | .\build\Debug\CodingTest.exe )
                echo.
                echo Answer
                echo %%a
                echo.
                set "allLines="
                @echo off
            ) Else (
                @echo on
                echo Status is error
                @echo off
            )
        )
    )
)
endlocal