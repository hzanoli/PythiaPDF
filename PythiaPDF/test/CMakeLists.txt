include(FetchContent)

FetchContent_Declare(
  GoogleTest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           v1.10.x 
)

FetchContent_MakeAvailable(GoogleTest)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_pdfplot test_base/test_pdfplot.cc)
target_link_libraries(test_pdfplot PUBLIC gtest_main ROOT::Hist ROOT::RIO pythiapdf_base)
add_test(NAME test_pdfplot COMMAND test_pdfplot)