FROM ubuntu:latest
RUN apt-get update && \
    apt-get install -y g++ cmake
WORKDIR /EchoServer
COPY LinServer.cpp CMakeLists.txt /EchoServer/
RUN cmake . && make
EXPOSE 81
CMD ["/EchoServer/Linserver"]
