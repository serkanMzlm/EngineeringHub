# CMake'in dahili sistem kontrol modüllerini yükleriz
include(CheckIncludeFile)
include(CheckSymbolExists)

message(STATUS "--- Starting System Environment Checks ---")

# 1. İşletim Sistemi Kontrolü
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Target OS: Linux detected.")
    add_definitions(-DSYSTEM="Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Target OS: Windows detected.")
    add_definitions(-DSYSTEM="Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Target OS: macOS (Darwin) detected.")
    add_definitions(-DSYSTEM="macOS")
else()
    message(WARNING "Target OS: Unknown operating system (${CMAKE_SYSTEM_NAME}).")
endif()

# 2. Kritik Başlık Dosyası (Header) Kontrolleri
# stdio.h dosyasının sistemde var olup olmadığını kontrol eder ve sonucu HAVE_STDIO_H değişkenine atar
check_include_file("stdio.h" HAVE_STDIO_H)
check_include_file("pthread.h" HAVE_PTHREAD_H)

# 3. Sonuçların Değerlendirilmesi ve Hata Yönetimi
if(NOT HAVE_STDIO_H)
    # Standart C kütüphanesi yoksa derlemeyi zorunlu olarak durdururuz
    message(FATAL_ERROR "System Check Failed: Standard C library header (stdio.h) not found!")
else()
    message(STATUS "System Check Passed: stdio.h is available.")
endif()

if(NOT HAVE_PTHREAD_H)
    # Pthread yoksa uyarı veririz ama derlemeyi tamamen durdurmayabiliriz (isteğe bağlı)
    message(WARNING "System Check Warning: pthread.h not found. Multi-threading features might be disabled.")
else()
    message(STATUS "System Check Passed: pthread.h is available.")
endif()

message(STATUS "--- System Environment Checks Completed ---")