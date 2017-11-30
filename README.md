# TcpLoggerClient
In order to be able to build the TCPClient Logger please:
- install cmake package on your ubuntu machine
  sudo apt-get install cmake
- mkdir build && cd build
- cmake ../
- make
Now, you have compiled successfully your binary, to run it just start your server before
and then run within command line:
TcpLoggerClient host port
where: "host" is the IP address of your TCp Logger Server
       "port" is the TCP port used for transfering logs
For example:
TcpLoggerClient 192.168.0.1 5555
