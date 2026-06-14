# Fonksiyon içindeki değişkenler dışarıyı etkilemez (Yerel Kapsam)
function(filter_existing_files INPUT_LIST_NAME OUTPUT_LIST_NAME)
    set(TEMPORARY_VALID_LIST "")

    foreach(file IN LISTS ${INPUT_LIST_NAME})
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/${file}")
            message(STATUS "Source file verified: src/${file}")
            list(APPEND TEMPORARY_VALID_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/${file}") 
        else()
            message(WARNING "Critical file is missing: src/${file} - Removing from build list!")
        endif()
    endforeach()

    # Oluşturulan temiz listeyi, çağıran ana dosyanın kapsamına (PARENT_SCOPE) aktarır
    # PARENT_SCOPE sayesinde fonksiyonun dışında da kullanılabilir hale gelir
    set(${OUTPUT_LIST_NAME} ${TEMPORARY_VALID_LIST} PARENT_SCOPE)
endfunction()

# Makro içinde yapılan değişiklikler doğrudan çağıran ana dosyayı etkiler
macro(filter_existing_files_macro INPUT_LIST_NAME OUTPUT_LIST_NAME)
    set(TEMPORARY_VALID_LIST "")

    foreach(file IN LISTS ${INPUT_LIST_NAME})
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/${file}")
            message(STATUS "Source file verified: src/${file}")
            list(APPEND TEMPORARY_VALID_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/${file}")
        else()
            message(WARNING "Critical file is missing: src/${file} - Removing from build list!")
        endif()
    endforeach()

    # PARENT_SCOPE kullanmadan doğrudan çıktı değişkenine atama yapıyoruz
    set(${OUTPUT_LIST_NAME} ${TEMPORARY_VALID_LIST})
endmacro()