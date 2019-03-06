rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
rem проверяем отутствие аргументов
%PROGRAM%  > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем 2 аргумента
%PROGRAM% test\matrix.in test\matrix.out > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем отсутствие входного файла
%PROGRAM% test\not_exist.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\file_not_exists.out
if ERRORLEVEL 1 goto err

rem проверяем посторонние символы в числах
%PROGRAM% test\matrix_not_number.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем нехватку данных 3x2
%PROGRAM% test\matrix_3x2.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем нехватку данных 2x3
%PROGRAM% test\matrix_2x3.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем нехватку - пустой файл
%PROGRAM% test\matrix_empty.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу 	
rem %PROGRAM% test\matrix.in > %TEMP%\output.txt
rem if ERRORLEVEL 1 goto err
rem fc.exe %TEMP%\output.txt test\matrix.out
rem if ERRORLEVEL 1 goto err

rem проверяем правильную работу при нулевом определителе 	
%PROGRAM% test\matrix_det0.in > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\matrix_det0.out
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1