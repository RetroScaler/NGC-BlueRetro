@echo off
rmdir /q /s single_dir_for_windows_kernel                                                               1>nul 2>nul
mkdir single_dir_for_windows_kernel                                                                     1>nul 2>nul

copy /y ..\..\src\libtest_misc\*                          single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libtest_porting_abstraction_layer\*     single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libtest_results\*                       single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libtest_test\*                          single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libtest_tests\*                         single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libtest_testsuite\*                     single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libtest_threadset\*                     single_dir_for_windows_kernel\                1>nul 2>nul

copy /y ..\..\src\libtest_internal.h                      single_dir_for_windows_kernel\                1>nul 2>nul
copy /y driver_entry_renamed_to_avoid_compiler_warning.c  single_dir_for_windows_kernel\driver_entry.c  1>nul 2>nul
copy /y sources.dynamic                                   single_dir_for_windows_kernel\sources         1>nul 2>nul

echo Windows kernel dynamic library build directory structure created.
echo (Note the effects of this batch file are idempotent).

