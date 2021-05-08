# IOT Server

## Compile directly
Read the dependencies to run this project

### Compiling
```bash
$ mkdir build && cd build
$ cmake .. && make
```

### Run Server
```bash
$ bin/centralserver
```

### Test Server
Send any message using netcat 
```bash
$ nc -u 127.0.0.1 1234
```
# Running through docker

## Getting image
```bash
$ sudo docker pull solidcris/iot_server
```

## Running image
```bash
$ sudo docker run -dit -p 1234:1234/udp --name iot solidcris/iot_server
```

## Getting the output log
```bash
$ sudo docker logs iot -f
```
