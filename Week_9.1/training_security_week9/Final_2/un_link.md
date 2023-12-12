# Cơ chế unlink() trong heap exploit
- Phần này nói khá rõ trong heap3 rồi. ở đây chỉ lấy ví dụ thôi




## Ví dụ đối với final two
**Đây là chunk thứ nhất:**
![Alt text](image-2.png)
- `0x89 = 137=136+1` biểu thị cho chunk này rộng 136 bit. bit 1 để biểu thị chunk ở trước chunk này đang được sử dụng. Hoặc chunk này là chunk đầu tiên.


**Chunk thứ hai**
![Alt text](image-3.png)
khi chạy tiếp chương trình sẽ hiểu khối màu vàng là size của chunk tiếp theo. Do khối màu vàng này có giá trị là -4 nên chunk này sẽ là khối màu xanh lá.
![Alt text](image-5.png)
**Phần xanh dương là chunk còn lại**
![Alt text](image-6.png)

Lúc này nó sẽ thực hiện cơ chế unlink để ghi địa chỉ của shellcode vào bên trong got
![Alt text](image-7.png)

vậy cơ bản thì nó sẽ hoạt động như thế này
![Alt text](image-8.png)
![Alt text](image-9.png)

# Reference
- https://github.com/ennorehling/dlmalloc/blob/master/malloc.c