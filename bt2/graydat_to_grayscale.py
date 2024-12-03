from PIL import Image

width = 256
height = 256

# Đọc dữ liệu từ tệp raw_gray.dat
with open("output.dat", "rb") as file:
    raw_data = file.read()

# Tạo ảnh xám từ dữ liệu
image = Image.new("L", (width, height))
image.putdata(raw_data)

# Lưu ảnh
image.save("edge_image.jpeg")

# Đóng tệp

file.close()
print("Done!")
