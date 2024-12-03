from PIL import Image

width = 256
height = 256

###########################doc
#with open("convolved_bin.dat", "rb") as file:
with open("doc_bin.dat", "rb") as file:
    binary_data = file.read(8 * 1024)

# Tạo ảnh nhị phân từ dữ liệu
image = Image.new("1", (width, height))

# Chuyển đổi dữ liệu byte thành danh sách bit (0 hoặc 1)
bits = []
for byte in binary_data:
    for i in range(8):
        bit_value = (byte >> (7 - i)) & 1
        bits.append(bit_value)

if len(bits) < width * height:
    bits += [0] * (width * height - len(bits))
elif len(bits) > width * height:
    bits = bits[:width * height]

# Cập nhật ảnh với danh sách bit
image.putdata(bits)

# Lưu ảnh nhị phân
image.save("doc.jpeg")

# Đóng tệp
#print("Done!")
file.close()

#####################################################ngang

#with open("convolved_bin.dat", "rb") as file:
with open("ngang_bin.dat", "rb") as file:
    binary_data = file.read(8 * 1024)

# Tạo ảnh nhị phân từ dữ liệu
image = Image.new("1", (width, height))

# Chuyển đổi dữ liệu byte thành danh sách bit (0 hoặc 1)
bits = []
for byte in binary_data:
    for i in range(8):
        bit_value = (byte >> (7 - i)) & 1
        bits.append(bit_value)

if len(bits) < width * height:
    bits += [0] * (width * height - len(bits))
elif len(bits) > width * height:
    bits = bits[:width * height]

# Cập nhật ảnh với danh sách bit
image.putdata(bits)

# Lưu ảnh nhị phân
image.save("ngang.jpeg")

# Đóng tệp

file.close()

##############################cheo1

#with open("convolved_bin.dat", "rb") as file:
with open("cheo1_bin.dat", "rb") as file:
    binary_data = file.read(8 * 1024)

# Tạo ảnh nhị phân từ dữ liệu
image = Image.new("1", (width, height))

# Chuyển đổi dữ liệu byte thành danh sách bit (0 hoặc 1)
bits = []
for byte in binary_data:
    for i in range(8):
        bit_value = (byte >> (7 - i)) & 1
        bits.append(bit_value)

if len(bits) < width * height:
    bits += [0] * (width * height - len(bits))
elif len(bits) > width * height:
    bits = bits[:width * height]

# Cập nhật ảnh với danh sách bit
image.putdata(bits)

# Lưu ảnh nhị phân
image.save("cheo1.jpeg")

# Đóng tệp
#print("Done!")
file.close()

#############################cheo2

#with open("convolved_bin.dat", "rb") as file:
with open("cheo2_bin.dat", "rb") as file:
    binary_data = file.read(8 * 1024)

# Tạo ảnh nhị phân từ dữ liệu
image = Image.new("1", (width, height))

# Chuyển đổi dữ liệu byte thành danh sách bit (0 hoặc 1)
bits = []
for byte in binary_data:
    for i in range(8):
        bit_value = (byte >> (7 - i)) & 1
        bits.append(bit_value)

if len(bits) < width * height:
    bits += [0] * (width * height - len(bits))
elif len(bits) > width * height:
    bits = bits[:width * height]

# Cập nhật ảnh với danh sách bit
image.putdata(bits)

# Lưu ảnh nhị phân
image.save("cheo2.jpeg")

# Đóng tệp
#print("Done!")
file.close()

print("Done!")

