hex_string = "15712E21722F271D36721D362A711D107134713031711D712c25732C717130732c7B1D3572302E26636363"

# Chuyển chuỗi hex thành list các byte
hex_bytes = bytes.fromhex(hex_string)

# XOR từng byte với 42
result_bytes = bytes([byte ^ 0x42 for byte in hex_bytes])

# Chuyển kết quả thành chuỗi ASCII
result_ascii = result_bytes.decode("ascii")

print(result_ascii)

