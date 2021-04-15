add_library(pythiapdf_base 
            STATIC 
            include/pythiapdf_base/pdfplot.h 
            src/pdfplot.cc 
            include/pythiapdf_base/particle.h)

target_include_directories(pythiapdf_base
        PUBLIC $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_options(pythiapdf_base
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)

target_link_libraries(pythiapdf_base PUBLIC ROOT::Hist ${PYTHIA8_LIBRARIES})

install(TARGETS pythiapdf_base 
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include)
install()