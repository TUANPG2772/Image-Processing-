from PIL import Image
import array
import cv2
import numpy as np

# Kích thước ảnh
width = 256
height = 256

# Đọc dữ liệu từ file raw.dat
with open("YCbCr_to_RGB.dat", "rb") as file:
    # Đọc dữ liệu dưới dạng mảng unsigned byte
    data = array.array("B", file.read())

# Tạo ảnh từ dữ liệu RGB
image = Image.frombytes("RGB", (width, height), data.tobytes())

# Hiển thị ảnh
image.show()
