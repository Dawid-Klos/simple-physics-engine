project(tests)
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests_main  tests_main.cc tests_vector.cpp tests_particle.cpp tests_detector.cpp tests_resolver.cpp)
target_link_libraries(
        tests_main
        GTest::gtest_main
        sfml-system
        sfml-window
        sfml-graphics
)

include(GoogleTest)
gtest_discover_tests(tests_main)