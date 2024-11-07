@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by GP_TERM.HPJ. >"hlp\GP_Term.hm"
echo. >>"hlp\GP_Term.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\GP_Term.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\GP_Term.hm"
echo. >>"hlp\GP_Term.hm"
echo // Prompts (IDP_*) >>"hlp\GP_Term.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\GP_Term.hm"
echo. >>"hlp\GP_Term.hm"
echo // Resources (IDR_*) >>"hlp\GP_Term.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\GP_Term.hm"
echo. >>"hlp\GP_Term.hm"
echo // Dialogs (IDD_*) >>"hlp\GP_Term.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\GP_Term.hm"
echo. >>"hlp\GP_Term.hm"
echo // Frame Controls (IDW_*) >>"hlp\GP_Term.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\GP_Term.hm"
REM -- Make help for Project GP_TERM


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\GP_Term.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\GP_Term.hlp" goto :Error
if not exist "hlp\GP_Term.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\GP_Term.hlp" Debug
if exist Debug\nul copy "hlp\GP_Term.cnt" Debug
if exist Release\nul copy "hlp\GP_Term.hlp" Release
if exist Release\nul copy "hlp\GP_Term.cnt" Release
echo.
goto :done

:Error
echo hlp\GP_Term.hpj(1) : error: Problem encountered creating help file

:done
echo.
