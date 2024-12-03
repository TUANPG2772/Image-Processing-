from PIL import Image
import numpy as np
import cv2

#img= cv2.imread('lena_gray.jpeg')
img= cv2.imread('lena_gray.jpeg')
cv2.imshow('Noi dung anh',img)
cv2.waitKey()

resized = cv2.resize(img,(256,256))
cv2.imshow('Noi dung anh',resized)
cv2.waitKey()
cv2.imwrite('resized.jpeg',resized)

# Load the grayscale image
image = Image.open("resized.jpeg")

# Convert the image to a NumPy array
image_data = np.array(image)

# Ensure that the image is in grayscale (2D array)
if len(image_data.shape) == 3 and image_data.shape[2] == 3:
    image_data = image_data[:, :, 0]

# Save the binary data to a file
with open("gray.dat", "wb") as f:
    f.write(image_data.tobytes())

print("Done!")
