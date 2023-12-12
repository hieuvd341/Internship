import requests
from bs4 import BeautifulSoup

# URL ban đầu
url = "http://go.ctf.site:10070/EKO/28"

# Số thứ tự của vị trí X bạn muốn đọc (ví dụ: 2)
position = 0

# Tải trang web
response = requests.get(url)

if response.status_code == 200:
    # Phân tích cú pháp HTML
    soup = BeautifulSoup(response.text, 'html.parser')

    # Tìm thẻ <TD> chứa vị trí X
    td_tags = soup.find_all('td')

    if position < len(td_tags):
        # Lấy nội dung của thẻ <TT> tương ứng
        td_content = td_tags[position].find('tt').get_text()

        # Xây dựng URL mới bằng cách thêm X vào URL ban đầu
        new_url = url + td_content

        # Truy cập URL mới
        new_response = requests.get(new_url)

        if new_response.status_code == 200:
            # Xử lý nội dung của URL mới ở đây
            print(new_response.text)
        else:
            print("Không thể truy cập URL mới")
    else:
        print("Vị trí X không tồn tại trong HTML")
else:
    print("Không thể tải trang web ban đầu")
