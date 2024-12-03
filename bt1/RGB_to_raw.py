import cv2
from PIL import Image
import numpy as np

img= cv2.imread('SV2.jpeg')
cv2.imshow('Noi dung anh',img)
cv2.waitKey()

resized = cv2.resize(img,(256,256))
cv2.imshow('Noi dung anh',resized)
cv2.waitKey()
cv2.imwrite('resized.jpeg',resized)
#

# Đọc hình ảnh
image = Image.open("resized.jpeg")
    # Trích xuất giá trị R, G, B
height, width = image.size
    # Lưu giá trị R, G, B vào tệp nhị phân raw.dat
with open("raw_SV2.dat", "wb") as file:
    for y in range(height):
        for x in range(width):
            r, g, b = image.getpixel((x, y))
            file.write(bytes([r, g, b]))
print("Dữ liệu đã được lưu vào raw.dat")
