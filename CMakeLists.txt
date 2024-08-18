cmake_minimum_required(VERSION 3.23.1 FATAL_ERROR)

set(PROJECT_NAME CPP-to-ASM-translator)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
   	src/AssemblerGenerator.h
   	src/AssemblerGenerator.cpp
   	src/Enums.h
   	src/LexicalAnalyzer.h
   	src/LexicalAnalyzer.cpp
   	src/Parser.h
   	src/Parser.cpp
   	src/ParseTable.h
   	src/ParseTable.cpp
   	src/ParseTableElement.h
   	src/ParseTableElement.cpp
   	src/StaticTable.h
   	src/DynamicTable.h
   	src/Token.h
   	src/Token.cpp
   	src/Translator.h
   	src/Translator.cpp
   	src/TemplateStaticTable.h
   	src/TemplateDynamicTable.h
	src/Identifier.h
	src/Identifier.cpp
	src/Literal.h
	src/Literal.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)