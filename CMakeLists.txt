cmake_minimum_required(VERSION 3.13)

# Must go before the project() command:
if(NOT DEFINED PROJECT_NAME)
	set(IS_ROOT_PROJECT "YES")
else()
	set(IS_ROOT_PROJECT "NO")
endif()

project(CommandInterpreter LANGUAGES CXX)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
	message(FATAL_ERROR "Targeting 32-bit platforms is not required for this project. Please compile for 64-bit.")
endif()

####################################
# Command Interpreter Library
####################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Source files used by the library.
# You may add any extra files that your implementation uses.
add_library(CommandInterpreter SHARED
	src/Control.cpp
	src/Interpreter.cpp
	src/CommandUtility.cpp
	src/Register.cpp
	src/CommandProcessor.cpp
	src/Commands/EchoCommand.cpp
	src/Commands/CountdownCommand.cpp
	src/Commands/UnrecognisedCommand.cpp
)

# Public interface headers for the library should go in this directory.
target_include_directories(CommandInterpreter PUBLIC include)

# Internal implementation headers and sources should go in this directory.
target_include_directories(CommandInterpreter PRIVATE src)

# This definition is added when building the library, so that public
# library functions may be exported correctly on Windows (see LibExport.h).
target_compile_definitions(CommandInterpreter PRIVATE -DCMDINT_BUILD_PRODUCER)

if(MSVC)
  target_compile_options(CommandInterpreter PRIVATE /W4 /WX)
else()
  target_compile_options(CommandInterpreter PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()


# You may add any extra target properties you wish to this section, eg. to specify
# a target C++ standard. Note that third party libraries or other external code
# may not be used in the project.


####################################
# Sanity Tests
####################################

add_executable(SanityTests
	sanity_tests/Main.cpp
	sanity_tests/TestProcessor.cpp
	sanity_tests/test_implementations/CommandEchoTests.cpp
	sanity_tests/test_implementations/CommandCountdownTests.cpp
	sanity_tests/test_implementations/CommandUnrecognisedTests.cpp
)

target_link_libraries(SanityTests PUBLIC CommandInterpreter)

target_include_directories(SanityTests PRIVATE sanity_tests)

if(MSVC)
  target_compile_options(SanityTests PRIVATE /W4 /WX)
else()
  target_compile_options(SanityTests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

####################################
# Installation
####################################

if(IS_ROOT_PROJECT)
	# If this project is a root project, allow installing the library to a directory.
	# This means that you can specify -DCMAKE_INSTALL_PREFIX=... and run
	# `cmake --build . --target install` to check how your library implementation
	# will be structured for an end user.
	install(TARGETS CommandInterpreter
		ARCHIVE DESTINATION "CommandInterpreter/lib"
		LIBRARY DESTINATION "CommandInterpreter/lib"
		RUNTIME DESTINATION "CommandInterpreter/bin"
	)

	install(DIRECTORY "include/CommandInterpreter"
		DESTINATION "CommandInterpreter/include"
	)

	# The sanity test executable will also be installed alongside the library.
	install(TARGETS SanityTests
		RUNTIME DESTINATION "SanityTests/bin"
	)

	install(IMPORTED_RUNTIME_ARTIFACTS CommandInterpreter
		RUNTIME DESTINATION "SanityTests/bin"
		LIBRARY DESTINATION "SanityTests/lib"
	)
endif()
