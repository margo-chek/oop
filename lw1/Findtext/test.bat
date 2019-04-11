rem test.bat "$(TargetPath)"
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
echo test1
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ��������� �������� ����� ��������� ��������� ��� ��������
echo test2
%PROGRAM% fileNotFound.txt "search line" > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� �������� (������ �������)
echo test3
%PROGRAM% tests\test.txt "need" > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� �������� (������ �� �������)
echo test4
%PROGRAM% tests\test.txt "cat" > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� �������� (�������� � �������������� ����� ���������)
echo test5
%PROGRAM% tests\inputFile.txt "need" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" tests\resultAfterSearchNeed.txt > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (�������� � �������������� ����� �� ���������)
echo test6
%PROGRAM% tests\inputFile.txt "hamster" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" tests\resultAfterSearchNeed.txt > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (������ ������� �����)
echo test7
%PROGRAM% tests\inputFile.txt "Need" > "%TEMP%\result.txt" 
fc.exe "%TEMP%\result.txt" tests\resultAfterSearchNeed.txt > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (������ ����)
echo test8
%PROGRAM% tests\emptyFile.txt "search line" > nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� �������� (������ ������)
echo test9
%PROGRAM% tests\inputFile.txt "" > nul
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1