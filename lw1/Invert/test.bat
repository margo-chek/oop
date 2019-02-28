rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
echo test1
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ��������� �������� ����� ��������� ��������� ��� ��������
echo test2
%PROGRAM% fileNotFound.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������ ����)
echo test3
%PROGRAM% test-data\emptyFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������������ ������ � �����)
echo test4
%PROGRAM% test-data\matrixErr1.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������������ ������ � �����)
echo test5
%PROGRAM% test-data\matrixErr2.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������������ = 0)
echo test6
%PROGRAM% test-data\matrixErr3.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(�������� � �������������� ����� ���������)
echo test7
%PROGRAM% test-data\matrix1.txt> "%TEMP%\invertedMatrixResult.txt" 
fc.exe "%TEMP%\invertedMatrixResult.txt" test-data\invertedMatrix.txt > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(�������� � �������������� ����� �� ���������)
echo test8
%PROGRAM% test-data\matrix1.txt> "%TEMP%\invertedMatrixResult.txt" 
fc.exe "%TEMP%\invertedMatrixResult.txt" test-data\invertedMatrixErr.txt > nul
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1











rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(�������� ���� �� ������)
echo test5
%PROGRAM% pack test-data\inputFile.txt test-data\fileNotFound.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(������� ���� ������, ���� �� ������ ������ ���� ������)
echo test6
%PROGRAM% pack test-data\emptyInputFile.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\emptyInputFile.txt > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(����� ������������������ ���������� �������� = 255)
echo test7
%PROGRAM% pack test-data\input_A_255.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\output_A_255.bin > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(����� ������������������ ���������� �������� = 256)
echo test8
%PROGRAM% pack test-data\input_b_256.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\output_b_256.bin > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(����� ������������������ ���������� �������� = 257)
echo test9
%PROGRAM% pack test-data\input_m_257.txt test-data\outputFile.txt >nul
fc.exe test-data\outputFile.txt test-data\output_m_257.bin > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(�������� ����� ������������� �����)
echo test10
%PROGRAM% unpack test-data\inputFileOddLength.txt test-data\outputFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(� ������������ ����� ���� ���-�� �������� = 0)
echo test11
%PROGRAM% unpack test-data\inputFileWithCountCharNull.bin test-data\outputFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(����������� � ��������� ��������� ���������)
rem echo test12
rem %PROGRAM% pack test-data\inputFile.txt test-data\outputFile.txt >nul
rem %PROGRAM% unpack test-data\outputFile.txt "%TEMP%\decompressionFile.txt" >nul
rem fc.exe test-data\inputFile.txt "%TEMP%\decompressionFile.txt" > nul
rem if ERRORLEVEL 1 goto err
