FROM ubuntu:latest
RUN apt-get update && \
    apt-get install -y g++ cmake
WORKDIR /CalcSer
COPY CalcServer.cpp CMakeLists.txt /CalcSer/
RUN cmake .
RUN make
EXPOSE 81
CMD ["/CalcSer/CalcServ"]
