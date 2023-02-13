include(FetchContent)

FetchContent_Declare(blst
    GIT_REPOSITORY https://github.com/supranational/blst
)


# FetchContent_MakeAvailable(blst)
FetchContent_GetProperties(blst)
if(NOT blst_POPULATED)
    FetchContent_Populate(blst)
endif()

SET(BLST_LIB_FILE ${blst_SOURCE_DIR}/libblast.a)
add_custom_command(
    OUTPUT ${BLST_LIB_FILE} 
    COMMAND ./build.sh 
    WORKING_DIRECTORY ${blst_SOURCE_DIR}
)
add_custom_target(blst_lib DEPENDS ${BLST_LIB_FILE})
