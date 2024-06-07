@echo off
setlocal enabledelayedexpansion

REM Compilar el programa
g++ -o main.exe main.cpp HashOpenID.cpp HashOpenUsername.cpp

REM Verificar si la compilación fue exitosa
if %errorlevel% neq 0 (
    echo Error durante la compilación.
    exit /b %errorlevel%
)

REM Número de iteraciones y valores de n
set iterations=20
set n_values=1000 5000 10000 15000 20000 21070

REM Ejecutar el programa múltiples veces
set experiment_number=1

for /l %%i in (1, 1, %iterations%) do (
    for %%n in (%n_values%) do (
        echo Ejecutando con n=%%n, iteracion %%i, experimento !experiment_number!
        main.exe %%n !experiment_number!
        set /a experiment_number+=1
    )
)

echo Todas las ejecuciones se completaron.