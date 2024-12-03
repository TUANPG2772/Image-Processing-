import cv2
from PIL import Image

def resize_and_save(image_path, resized_path, binary_file_path):

    img= cv2.imread(image_path)
    resized = cv2.resize(img,(256,256))
    cv2.imwrite(resized_path,resized)
    
    # Open the resized image
    image = Image.open(resized_path)

    # Get the size of the image
    height, width = image.size

    # Save RGB values into a binary file
    with open(binary_file_path, "wb") as file:
        for y in range(height):
            for x in range(width):
                # Get RGB values of each pixel
                r, g, b = image.getpixel((x, y))

                # Write RGB values to the binary file
                file.write(bytes([r, g, b]))

    print(f"Dữ liệu đã được lưu vào {binary_file_path}")

# Example usage:
resize_and_save('back_ground.jpeg', 'back_ground_resigned.jpeg', 'back_ground_raw.dat')
resize_and_save('object1.jpeg', 'object1_resigned.jpeg', 'Object1_raw.dat')
resize_and_save('object2.jpeg', 'object2_resigned.jpeg', 'Object2_raw.dat')


