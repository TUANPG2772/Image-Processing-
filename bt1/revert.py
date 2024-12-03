from PIL import Image

# Định nghĩa kích thước của ảnh (thay thế bằng kích thước thực tế)
width = 256
height = 256

# Đọc dữ liệu từ tệp raw_gray.dat
with open("raw_SV2_gray.dat", "rb") as file:
    raw_data = file.read()

# Tạo ảnh xám từ dữ liệu
image = Image.new("L", (width, height))
image.putdata(raw_data)

# Lưu ảnh hoặc hiển thị nó
image.save("SV2_gray.jpeg")

# Đóng tệp
print("Done!")
file.close()
