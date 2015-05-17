del *.obj

masm grafica.asm
masm tempo.asm
masm mouse.asm
masm main.asm
masm myfun.asm

del MAIN.exe
link grafica.obj myfun.obj tempo.obj mouse.obj main.obj,main.exe,,,,
del *.obj main.map

pause

