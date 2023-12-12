def factorial(n):
    ans = 1
    for i in range(1, n+1):
        ans = ans*i
    return ans

def curious_number_sum(limit):
    curious_numbers = []
    for num in range(1, limit):
        origin_num = num
        ans = 0
        while(num > 0):
            ans +=factorial(num % 10)
            num = num//10
        if ans == origin_num:
            curious_numbers.append(ans)
            print(f"Curious number found: {ans}")
    return curious_numbers

limit = 1000000
result = curious_number_sum(limit)

print("Curious numbers:", result)
print("Sum:", sum(result))
