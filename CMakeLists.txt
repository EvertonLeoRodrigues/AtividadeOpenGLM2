cmake_minimum_required(VERSION 3.10)
project(MeuProjetoOpenGL LANGUAGES CXX C)

# Forçar uso de GLVND para OpenGL
cmake_policy(SET CMP0072 NEW)

# Definir o padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar pkg-config
find_package(PkgConfig REQUIRED)

# Encontrar OpenGL
find_package(OpenGL REQUIRED)

# Encontrar GLFW3 usando pkg-config
pkg_check_modules(GLFW3 REQUIRED glfw3)
if(NOT GLFW3_FOUND)
    message(FATAL_ERROR "GLFW3 não encontrado. Instale o pacote glfw3-devel.")
endif()

# Configurar GLM manualmente (header-only)
find_path(GLM_INCLUDE_DIRS glm/glm.hpp
    PATHS
    /usr/include
    /usr/local/include
    /usr/include/glm
)
if(NOT GLM_INCLUDE_DIRS)
    message(FATAL_ERROR "GLM não encontrado. Verifique se o pacote glm-devel está instalado.")
endif()

# Configurar GLAD (estático, incluído no projeto)
set(GLAD_SRC src/glad.c)
set(GLAD_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)

# set(RESOURCES_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/assets)


# Listar meus executaveis do src
set(EXERCISES
    main
)

# Cria os executaveis
foreach(EXERCISE ${EXERCISES})
    #Extrai o nome do arquivo sem o diretório para o executável
    get_filename_component(EXE_NAME ${EXERCISE} NAME)

    #Adiciona o executável usando o nome do arquivo como nome do executável
    add_executable(${EXE_NAME} src/${EXERCISE}.cpp ${GLAD_SRC})

    #Configura as bibliotecas e include dirs para o executável

    # Linkar bibliotecas
    target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL ${GLFW3_LIBRARIES} dl)
    
    # Incluir diretórios de cabeçalhos
    target_include_directories(${EXE_NAME} PRIVATE ${GLM_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS})
endforeach()


# Copiar shaders para o diretório de build
file(COPY ${CMAKE_SOURCE_DIR}/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/shaders/)

## Copiar resources para o diretório de build
# file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets/)

add_custom_target(copy_shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
    COMMENT "copy shaders to build diractory"
)

add_dependencies(main copy_shaders)
