def countWays(coins, m, N):
    # Khởi tạo mảng dp
    dp = [0 for _ in range(N + 1)]
 
    # Có một cách để tạo ra 0 VNĐ, đó là không sử dụng đồng nào
    dp[0] = 1
 
    # Duyệt qua các mệnh giá tiền
    for i in range(m):
        # Cập nhật các giá trị lớn hơn hoặc bằng mệnh giá hiện tại
        for j in range(coins[i], N + 1, 1000):
            dp[j] += dp[j - coins[i]]
    return dp[N]

# Mệnh giá tiền
coins = [1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000]
m = len(coins)

# Số tiền cần tạo
N = 1000000

print("Số cách để tạo ra", N, "VNĐ là", countWays(coins, m, N))
