@echo off
rmdir /q /s single_dir_for_windows_kernel                                                                                   1>nul 2>nul
mkdir single_dir_for_windows_kernel                                                                                         1>nul 2>nul

copy /y ..\..\src\libbenchmark_benchmarkinstance\*                            single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_benchmarks_btree_au_readn_writen\*             single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_benchmarkset\*                                 single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_benchmarks_freelist_push1_then_pop1\*          single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_benchmarks_queue_umm_enqueue1_then_dequeue1\*  single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_benchmarksuite\*                               single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_datastructures_btree_au\*                      single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_datastructures_freelist\*                      single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_datastructures_queue_umm\*                     single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_misc\*                                         single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_porting_abstraction_layer\*                    single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_results\*                                      single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_threadset\*                                    single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_topology\*                                     single_dir_for_windows_kernel\                1>nul 2>nul
copy /y ..\..\src\libbenchmark_topology_node\*                                single_dir_for_windows_kernel\                1>nul 2>nul

copy /y ..\..\src\libbenchmark_internal.h                                     single_dir_for_windows_kernel\                1>nul 2>nul
copy /y sources.static                                                        single_dir_for_windows_kernel\sources         1>nul 2>nul

echo Windows kernel static library build directory structure created.
echo (Note the effects of this batch file are idempotent).

