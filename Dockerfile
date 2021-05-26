FROM fedora:35

RUN yum install -y  \
    automake-1.16.2 \ 
    boost-devel-1.75.0 \
    cmake-3.19.7 \
    gcc-11.0.1 \
    gcc-c++-11.0.1 \ 
    git-2.31.1 \
    lhapdf-devel-6.3.0 \
    make-4.3 \ 
    pythia8-8.3.03 \
    pythia8-devel-8.3.03 \
    pythia8-lhapdf-8.3.03 \
    python3-lhapdf-6.3.0 \
    python3-root-6.22.08 \
    root-6.22.08 \
    rsync-3.2.3 \
    && yum clean all \
    && rm -rf /var/cache/yum

RUN lhapdf install CT14nnloIC

COPY PythiaPDF /PythiaPDF

RUN cmake -H/PythiaPDF -B/PythiaPDF/build \
    && cmake --build /PythiaPDF/build --target install

RUN chmod a+x /PythiaPDF/scripts/entrypoint.py

ENTRYPOINT ["./PythiaPDF/scripts/entrypoint.py"]
