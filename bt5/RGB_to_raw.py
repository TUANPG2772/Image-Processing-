# tu hinh RGB xuat ra file raw.dat cac gia tri R, G, B

import cv2
from PIL import Image
import numpy as np

img= cv2.imread('lena.jpeg')
cv2.imshow('Lena',img)
cv2.waitKey()

resized = cv2.resize(img,(256,256))
cv2.imshow('Lena',resized)
cv2.waitKey()
cv2.imwrite('resized.jpeg',resized)
#

# Đọc hình ảnh
image = Image.open("resized.jpeg")
    # Trích xuất giá trị R, G, B
height, width = image.size
    # Lưu giá trị R, G, B vào tệp nhị phân raw.dat
with open("lena_raw.dat", "wb") as file:
    for y in range(height):
        for x in range(width):
            r, g, b = image.getpixel((x, y))
            file.write(bytes([r, g, b]))
print("Dữ liệu đã được lưu vào raw.dat")
