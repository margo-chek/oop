rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ��������� ����������
%PROGRAM%  > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 2 ���������
%PROGRAM% tests\matrix.in tests\matrix.out > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� �������� �����
%PROGRAM% tests\not_exist.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\file_not_exist.out
if ERRORLEVEL 1 goto err

rem ��������� ����������� ������� � ������
%PROGRAM% tests\matrix_not_number.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� ������ 3x2
%PROGRAM% tests\matrix_3x2.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� ������ 2x3
%PROGRAM% tests\matrix_2x3.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� - ������ ����
%PROGRAM% tests\matrix_empty.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ 	
%PROGRAM% tests\matrix.in > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\matrix.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� ������� ������������ 	
%PROGRAM% tests\matrix_det0.in > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt tests\matrix_det0.out
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1