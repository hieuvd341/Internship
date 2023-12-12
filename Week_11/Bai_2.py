def curious_number_sum(limit):
    curious_numbers = []
    for num in range(1, limit):
        origin_num = num
        ans = 0
        while(num > 0):
            ans+=pow(num%10, 5)
            num = num//10
        if ans == origin_num:
            curious_numbers.append(ans)
            print(f"Curious number found: {ans}")
    return curious_numbers

limit = 100000000
result = curious_number_sum(limit)

print("Curious numbers:", result)
print("Sum:", sum(result))
