add_library(${PROJECT_NAME} 
    bls12_381.c 
    c_kzg_alloc.c 
    das_extension.c 
    fft_common.c 
    fft_fr.c 
    fft_g1.c 
    fk20_proofs.c 
    kzg_proofs.c 
    poly.c 
    recover.c 
    utility.c 
    zero_poly.c
)

add_dependencies(${PROJECT_NAME} blst_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${BLST_LIB_FILE})
target_include_directories(${PROJECT_NAME} PRIVATE ${blst_SOURCE_DIR}/bindings/)
