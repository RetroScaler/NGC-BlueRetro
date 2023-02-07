@echo off
rmdir /q /s single_dir_for_windows_kernel                                                              1>nul 2>nul
mkdir single_dir_for_windows_kernel                                                                    1>nul 2>nul

copy /y ..\..\src\libshared_ansi\*                       single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libshared_memory\*                     single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libshared_misc\*                       single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libshared_porting_abstraction_layer\*  single_dir_for_windows_kernel\                1>nul 2>nul

copy /y ..\..\src\libshared_internal.h                   single_dir_for_windows_kernel\                1>nul 2>nul
copy /y sources.static                                   single_dir_for_windows_kernel\sources         1>nul 2>nul

echo Windows kernel static library build directory structure created.
echo (Note the effects of this batch file are idempotent).

