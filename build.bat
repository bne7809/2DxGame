@echo off

set MSRCS=src\main.cpp src\remcrt.cpp
set CFlags=/DUNICODE /D_UNICODE /Iinclude /W3 /WX /Gy /GR- /EHs- /EHc- /D_HAS_EXCEPTIONS=0 /GS- /Gs9999999
set LFlags=/NODEFAULTLIB /STACK:0x100000,0x100000 /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /INCREMENTAL:NO
set LLibs=kernel32.lib user32.lib d3d11.lib d3dcompiler.lib ole32.lib windowscodecs.lib

fxc /T vs_5_0 /E main /Fo shader_out\anim_sprite_vs.cso shader\anim_sprite.hlsl
fxc /T ps_5_0 /E main /Fo shader_out\def_tex_sample_ps.cso shader\def_tex_sample.hlsl

fxc /T vs_5_0 /E main /Fo shader_out\def_vs.cso shader\def_vs.hlsl
fxc /T ps_5_0 /E main /Fo shader_out\def_ps.cso shader\def_ps.hlsl

cl %MSRCS% %CFlags% /Zi /DEBUG /Foobj\ /Fe:dxgame.exe /link %LFlags% %LLibs%

@echo on
