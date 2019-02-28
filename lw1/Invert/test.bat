rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
echo test1
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem При неудачном открытии файла ожидается ненулевой код возврата
echo test2
%PROGRAM% fileNotFound.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата(пустой файл)
echo test3
%PROGRAM% test-data\emptyFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата(некорректные данные в файле)
echo test4
%PROGRAM% test-data\matrixErr1.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата(некорректные данные в файле)
echo test5
%PROGRAM% test-data\matrixErr2.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается ненулевой код возврата(определитель = 0)
echo test6
%PROGRAM% test-data\matrixErr3.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата(исходный и результирующий файлы совпадают)
echo test7
%PROGRAM% test-data\matrix1.txt> "%TEMP%\invertedMatrixResult.txt" 
fc.exe "%TEMP%\invertedMatrixResult.txt" test-data\invertedMatrix.txt > nul
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата(исходный и результирующий файлы не совпадают)
echo test8
%PROGRAM% test-data\matrix1.txt> "%TEMP%\invertedMatrixResult.txt" 
fc.exe "%TEMP%\invertedMatrixResult.txt" test-data\invertedMatrixErr.txt > nul
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1











rem При запуске с корректными параметрами ожидается ненулевой код возврата(выходной файл не найден)
echo test5
%PROGRAM% pack test-data\inputFile.txt test-data\fileNotFound.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(входной файл пустой, файл на выходе должен быть пустым)
echo test6
%PROGRAM% pack test-data\emptyInputFile.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\emptyInputFile.txt > nul
if ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(Длина последовательности одинаковых символов = 255)
echo test7
%PROGRAM% pack test-data\input_A_255.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\output_A_255.bin > nul
if ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(Длина последовательности одинаковых символов = 256)
echo test8
%PROGRAM% pack test-data\input_b_256.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\output_b_256.bin > nul
if ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(Длина последовательности одинаковых символов = 257)
echo test9
%PROGRAM% pack test-data\input_m_257.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\output_m_257.bin > nul
if ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(нечетная длина запакованного файла)
echo test10
%PROGRAM% unpack test-data\inputFileOddLength.txt test-data\outputFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(в запакованном файле есть кол-во символов = 0)
echo test11
%PROGRAM% unpack test-data\inputFileWithCountCharNull.bin test-data\outputFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с корректными параметрами ожидается нулевой код возврата(фактический и ожидаемый результат совпадают)
rem echo test12
rem %PROGRAM% pack test-data\inputFile.txt test-data\outputFile.txt >nul
rem %PROGRAM% unpack test-data\outputFile.txt "%TEMP%\decompressionFile.txt" >nul
rem fc.exe test-data\inputFile.txt "%TEMP%\decompressionFile.txt" > nul
rem if ERRORLEVEL 1 goto err
