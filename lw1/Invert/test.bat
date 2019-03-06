rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
rem ��������� ��������� ����������
%PROGRAM%  > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 2 ���������
%PROGRAM% test\matrix.in test\matrix.out > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� �������� �����
%PROGRAM% test\not_exist.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\file_not_exists.out
if ERRORLEVEL 1 goto err

rem ��������� ����������� ������� � ������
%PROGRAM% test\matrix_not_number.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� ������ 3x2
%PROGRAM% test\matrix_3x2.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� ������ 2x3
%PROGRAM% test\matrix_2x3.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� - ������ ����
%PROGRAM% test\matrix_empty.in > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ 	
rem %PROGRAM% test\matrix.in > %TEMP%\output.txt
rem if ERRORLEVEL 1 goto err
rem fc.exe %TEMP%\output.txt test\matrix.out
rem if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� ������� ������������ 	
%PROGRAM% test\matrix_det0.in > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test\matrix_det0.out
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1