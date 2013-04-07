; picprepv0.8.nsi
;
; this is the script for the first install of picprep. nothing fancy
; at this point we'll do cooler stuff later ;-)

;--------------------------------

; The name of the installer
Name "picrep v0.9.0 - Myndkryme Laboratories"

; The file to write
OutFile "picprepv090.exe"

; The default installation directory
InstallDir $PROGRAMFILES\picprep

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File ..\debug\picprep.exe
  File ..\debug\freeimage.dll
  File ..\docs\picprep-usermanual.html
  File ..\docs\freeimage-license.txt
  File ..\docs\picprep-changelog.txt
  
SectionEnd ; end the section