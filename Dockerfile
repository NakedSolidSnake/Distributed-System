FROM debian

MAINTAINER Cristiano Silva de Souza, cristianosstec@gmail.com

ENV PATH=$PATH:/server/build/bin

RUN apt-get update -y
RUN apt-get install build-essential -y
RUN apt-get install git -y
RUN apt-get install systemd -y
RUN apt-get install libsystemd-dev -y
RUN apt-get install cmake -y
RUN apt-get install libjson-c-dev -y
RUN apt-get install default-libmysqlclient-dev -y

#install middleware
RUN git clone https://github.com/NakedSolidSnake/middleware.git
RUN cd middleware && mkdir build && cd build && cmake .. && make && make install && ldconfig

# install central server
COPY ./server /server
RUN cd server && mkdir build && cd build && cmake .. && make && make install

EXPOSE 1234/udp

ENTRYPOINT ["centralserver"]