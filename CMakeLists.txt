set (PROJECT_NAME
    attache
)

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} \
    -Wall \
    -Werror \
    -std=c99"
)

###

project(${PROJECT_NAME})

set (SOURCES
    src/main.c
    src/tokenizer/token.c
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

###

project(${PROJECT_NAME}-test)

set (SOURCES-TEST
    test/main.c
    src/tokenizer/token.c
)

add_executable(${PROJECT_NAME}
    ${SOURCES-TEST}
)
