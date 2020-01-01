# TCP-File-Transfer
C++ programs to transfer a Text file from server to client using TCP

## Basic Instructions
The CPP files were compiled and ran on Ubuntu [WSL].  

Direction of file Transfer: Server to Client.  
The path of text file to send can be changed in the `file_server.cpp` on line 37.  
  
**NOTE**: The char array `buffer` in `file_client.cpp` is default to 1KB, you may need to increase the file size as per the larger file's size.  

## References for function used in the code...
- Socket Programming basics : https://www.geeksforgeeks.org/socket-programming-cc/

### Socket Program basics
- `inet_pton()` : http://man7.org/linux/man-pages/man3/inet_pton.3.html  
  
- `sockaddr_in` and `in_addr` : https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html  
- `socket()` : http://man7.org/linux/man-pages/man2/socket.2.html  
- `bind()` : http://man7.org/linux/man-pages/man2/bind.2.html  
- `listen()` : http://man7.org/linux/man-pages/man2/listen.2.html  
- `accept()` : http://man7.org/linux/man-pages/man2/accept.2.html  
  
- `read()` : http://man7.org/linux/man-pages/man2/read.2.html  
- `send()` : http://man7.org/linux/man-pages/man2/send.2.html  

### File handling
- Copying whole text to string buffer before transmission  
https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c


Good luck!
