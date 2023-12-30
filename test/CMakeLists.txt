add_executable(
  lexer
  lexer.cpp
)
target_link_libraries(
  lexer
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lexer)