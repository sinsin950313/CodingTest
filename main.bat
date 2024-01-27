@echo off

set Argument=-Arg-
set Answer=-Ans-

set Option=%1

setlocal enabledelayedexpansion
IF "%Option%"=="-h" (
    echo    # Make Sure cmake already registered to path
    echo    # Without extension
    echo    -n { New Solution Name }                        = New
    echo    -b  { Solution Name }                           = Build
    echo    -d  { Solution Name } { Debuging Sample Order } = Set Debug Mode, { Debug Sample Order } is integer.
    echo    -r  { Solution Name }                           = Run Every Samples
    echo        { Test Input File Name }.ini : Write Arguments after %Argument% and Answers after %Answer%
) ELSE IF "%Option%"=="-n" (
    set SolutionName=%2
    if not exist !SolutionName!.cpp (
        mkdir !SolutionName!
        copy .\Origin\Origin.cpp .\!SolutionName!\!SolutionName!.cpp
        copy .\Origin\Origin.ini .\!SolutionName!\!SolutionName!.ini
    )
    cmake -D TestName:STRING=!SolutionName! -B "%cd%/build"
    code . .\!SolutionName!\!SolutionName!.cpp .\!SolutionName!\!SolutionName!.ini
) ELSE IF "%Option%"=="-b" (
    set SolutionName=%2
    cmake -D TestName:STRING=!SolutionName! -B "%cd%/build"
    cmake --build "%cd%/build" --config Debug --target ALL_BUILD -j 6
) ELSE IF "%Option%"=="-d" (
    set SolutionName=%2
    set SampleOrder=%3
    SettingModifier.exe .\.vscode\settings.json .\!SolutionName!\!SolutionName!.ini !SampleOrder!
    cmake -D TestName:STRING=!SolutionName! -B "%cd%/build"
    cmake --build "%cd%/build" --config Debug --target ALL_BUILD -j 6
) ELSE IF "%Option%"=="-r" (
    set SolutionName=%2
    set True="True"
    set False="False"

    set IsParam=True
    set "Status="
    set "allLines="
    for /f "tokens=* delims=" %%a in (.\!SolutionName!\!SolutionName!.ini) do (
        set "Variable=%%a"

        IF "!Variable!"=="%Argument%" (
            set "Status=%Argument%"
        ) ELSE IF "!Variable!"=="%Answer%" (
            set "Status=%Answer%"
            @echo on
            echo.
            echo Result
            .\build\Debug\CodingTest.exe !allLines!
            echo.
            set "allLines="
            echo Answer
            echo off
        ) ELSE (
            IF "!Status!"=="%Argument%" (
                set "allLines=!allLines! %%a"
            ) ELSE IF "!Status!"=="%Answer%" (
                @echo on
                echo        %%a
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