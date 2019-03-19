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
%PROGRAM% fileNotFound.txt "search line" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� �������� (������ �������)
echo test3
%PROGRAM% test-data\test.txt "need" > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� �������� (������ �� �������)
echo test4
%PROGRAM% test-data\test.txt "cat" > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� �������� (�������� � �������������� ����� ���������)
echo test5
%PROGRAM% test-data\inputFile.txt "need" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" test-data\resultAfterSearchNeed.txt > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (�������� � �������������� ����� �� ���������)
echo test6
%PROGRAM% test-data\inputFile.txt "hamster" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" test-data\resultAfterSearchNeed.txt > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (������ ������� �����)
echo test7
%PROGRAM% test-data\inputFile.txt "Need" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" test-data\resultAfterSearchNeed.txt > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (������ ����)
echo test8
%PROGRAM% test-data\emptyFile.txt "search line" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (������ ������)
echo test9
%PROGRAM% test-data\inputFile.txt "" >nul
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1