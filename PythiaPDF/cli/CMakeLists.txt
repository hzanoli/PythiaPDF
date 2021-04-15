add_executable(pythiapdf src/cli.cc)

target_link_libraries(pythiapdf PUBLIC pythiapdf_base Boost::program_options)

install(TARGETS pythiapdf DESTINATION bin)
