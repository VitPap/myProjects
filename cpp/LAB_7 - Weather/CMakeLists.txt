# CMakeList.txt: проект CMake для labwork7; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
 )
FetchContent_MakeAvailable(ftxui)
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
project("labwork7")

# Добавьте источник в исполняемый файл этого проекта.
add_executable(labwork7 "labwork7.cpp" "labwork7.h" "City.cpp" "WeatherData.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET labwork7 PROPERTY CXX_STANDARD 17)
endif()

target_link_libraries(labwork7 PRIVATE cpr::cpr)
target_link_libraries(labwork7 PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(labwork7 PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.