aux_source_directory(SOFA/src SRC_LIST_1)
aux_source_directory(minIni/src SRC_LIST_2)

add_library(SOFA ${SRC_LIST_1})
add_library(minIni ${SRC_LIST_2})