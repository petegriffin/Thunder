set(TEST_RUNNER_NAME "WPEFramework_test_core")

add_executable(${TEST_RUNNER_NAME}
   ../IPTestAdministrator.cpp
   test_rpc.cpp
<<<<<<< HEAD
   test_jsonparser.cpp
=======
   test_time.cpp
>>>>>>> 546a80f... [Tests] Implemented testcases corresponding to Time.
#   test_sharedbuffer.cpp
)

target_link_libraries(${TEST_RUNNER_NAME} 
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    WPEFrameworkCore
    WPEFrameworkTracing
    WPEFrameworkProtocols
)

