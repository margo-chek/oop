rem test.bat "$(TargetPath)"
rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
echo test1
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem При неудачном открытии файла ожидается ненулевой код возврата
echo test2
%PROGRAM% fileNotFound.txt "search line" > nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата (строка найдена)
echo test3
%PROGRAM% tests\test.txt "need" > nul
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата (строка не найдена)
echo test4
%PROGRAM% tests\test.txt "cat" > nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата (исходный и результирующий файлы совпадают)
echo test5
%PROGRAM% tests\inputFile.txt "need" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" tests\resultAfterSearchNeed.txt > nul
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата (исходный и результирующий файлы не совпадают)
echo test6
%PROGRAM% tests\inputFile.txt "hamster" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" tests\resultAfterSearchNeed.txt > nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата (разный регистр строк)
echo test7
%PROGRAM% tests\inputFile.txt "Need" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" tests\resultAfterSearchNeed.txt > nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата (пустой файл)
echo test8
%PROGRAM% tests\emptyFile.txt "search line" > nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата (пустая строка)
echo test9
%PROGRAM% tests\inputFile.txt "" > nul
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1