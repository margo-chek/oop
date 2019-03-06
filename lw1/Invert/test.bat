rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem проверяем отутствие аргументов
%PROGRAM%  > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем 2 аргумента
%PROGRAM% tests\matrix.in tests\matrix.out > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем отсутствие входного файла
%PROGRAM% tests\not_exist.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\file_not_exist.out
if ERRORLEVEL 1 goto err

rem проверяем посторонние символы в числах
%PROGRAM% tests\matrix_not_number.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем нехватку данных 3x2
%PROGRAM% tests\matrix_3x2.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем нехватку данных 2x3
%PROGRAM% tests\matrix_2x3.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем нехватку - пустой файл
%PROGRAM% tests\matrix_empty.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу 	
%PROGRAM% tests\matrix.in > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\matrix.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу при нулевом определителе 	
%PROGRAM% tests\matrix_det0.in > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\matrix_det0.out
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1