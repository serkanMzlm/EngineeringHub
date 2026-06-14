macro(run_dependency_queue_check)
    message(STATUS "--- Starting Dynamic Dependency Queue Checks ---")

    # Kontrol edilmesi gereken bağımlılıkların dinamik listesi (Kuyruk)
    set(DEPENDENCY_QUEUE "ZLIB" "Threads")

    # Listenin güncel uzunluğunu alır
    list(LENGTH DEPENDENCY_QUEUE QUEUE_LENGTH)

    # Liste tamamen boşalana kadar döngü çalışmaya devam eder
    while(QUEUE_LENGTH GREATER 0)
        
        # Listenin ilk elemanını (0. indeks) alır
        list(GET DEPENDENCY_QUEUE 0 CURRENT_DEP)
        
        message(STATUS "[Dependency Check] Investigating system for: ${CURRENT_DEP}...")
        
        # Sistemi sessizce tarar (QUIET parametresi hata loglarını gizler)
        find_package(${CURRENT_DEP} QUIET)
        
        if(${CURRENT_DEP}_FOUND)
            message(STATUS "[Dependency Check] SUCCESS: ${CURRENT_DEP} found on system.")
        else()
            message(WARNING "[Dependency Check] FAILED: ${CURRENT_DEP} is missing!")
        endif()
        
        # İşi biten ilk elemanı listeden sileriz (Kuyruğu ilerletme / Pop işlemi)
        list(REMOVE_AT DEPENDENCY_QUEUE 0)
        
        # Listenin yeni uzunluğunu güncelleriz, liste boşaldığında döngü kendiliğinden biter
        list(LENGTH DEPENDENCY_QUEUE QUEUE_LENGTH)
        
    endwhile()

    message(STATUS "--- All Dynamic Queue Checks Completed ---")
endmacro()