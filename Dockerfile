FROM ubuntu:latest
RUN apt-get update && \
    apt-get install -y g++ cmake
WORKDIR /helloapp
COPY hello.cpp CMakeLists.txt /helloapp/
RUN cmake . && make 
CMD ["/helloapp/Hello"]
