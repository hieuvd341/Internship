def calculate(to_write, written):
    to_write += 0x100
    written %= 0x100
    padding = (to_write - written) % 0x100
    if padding < 10:
        padding += 0x100
    return padding

print(calculate(0x44, 0x58+16))
print(calculate(0x55, 0x58+16+220)) 
print(calculate(0x02, 0x58+16+220+17))
print(calculate(0x01, 0x58+16+220+17+173))