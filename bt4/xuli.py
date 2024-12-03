import numpy as np 

# Tạo ma trận 8x8 và gán giá trị mong muốn

matrix = np.array([
          [139, 144, 149, 153, 155, 155, 155, 155],
          [144, 151, 153, 156, 159, 156, 156, 156],
          [150, 155, 160, 163, 158, 156, 156, 156],
          [159, 161, 162, 160, 160, 159, 159, 159],
          [159, 160, 161, 162, 162, 155, 155, 155],
          [161, 161, 161, 161, 160, 157, 157, 157],
          [162, 162, 161, 163, 162, 157, 157, 157],
          [162, 162, 161, 161, 163, 158, 158, 158 ]])

# Trừ giá trị 128 từng phần tử của ma trận
matrix1 = np.zeros_like(matrix)
for i in range(len(matrix)):
    for j in range(len(matrix[i])):
        matrix1[i][j] = matrix[i][j] - 128

def forward_dct(matrix):
    result = np.zeros_like(matrix, dtype=float)
    rows, cols = matrix.shape

    for u in range(rows):
        for v in range(cols):
            cu = 1.0 / np.sqrt(2) if u == 0 else 1.0
            cv = 1.0 / np.sqrt(2) if v == 0 else 1.0

            sum_val = 0.0
            for x in range(rows):
                for y in range(cols):
                    sum_val += matrix[x, y] * np.cos((2 * x + 1) * u * np.pi / (2 * rows)) * np.cos((2 * y + 1) * v * np.pi / (2 * cols))

            result[u, v] = 0.25 * cu * cv * sum_val

    return np.round(result,1)

def quantize(coefficients, quantization_table):
    return np.round(coefficients / quantization_table)

def dequantize(quantized_coefficients, quantization_table):
    return quantized_coefficients * quantization_table

def inverse_dct(coefficients):
    result = np.zeros_like(coefficients, dtype=float)
    rows, cols = coefficients.shape

    for x in range(rows):
        for y in range(cols):
            sum_val = 0.0
            for u in range(rows):
                for v in range(cols):
                    cu = 1.0 / np.sqrt(2) if u == 0 else 1.0
                    cv = 1.0 / np.sqrt(2) if v == 0 else 1.0

                    sum_val += cu * cv * coefficients[u, v] * np.cos((2 * x + 1) * u * np.pi / (2 * rows)) * np.cos((2 * y + 1) * v * np.pi / (2 * cols))

            result[x, y] = 0.25 * sum_val + 128

    return np.round(result)

# Example usage:
source_image = matrix1
quantization_table = np.array([[16, 11, 10, 16, 24, 40, 51, 61],
                               [12, 12, 14, 19, 26, 58, 60, 55],
                               [14, 13, 16, 24, 40, 57, 69, 56],
                               [14, 17, 22, 29, 51, 87, 80, 62],
                               [18, 22, 37, 56, 68, 109, 103, 77],
                               [24, 35, 55, 64, 81, 104, 113, 92],
                               [49, 64, 78, 87, 103, 121, 120, 101],
                               [72, 92, 95, 98, 112, 100, 103, 99]])

# Forward DCT
dct_coefficients = forward_dct(source_image)
# Quantization
quantized_coefficients = quantize(dct_coefficients, quantization_table)

# Dequantization
dequantized_coefficients = dequantize(quantized_coefficients, quantization_table)

# Inverse DCT
reconstructed_image = inverse_dct(dequantized_coefficients)

# Display results
print("Source Image:")
print(matrix)
print("\nDCT Coefficients:")

for row in dct_coefficients:
    for element in row:
        print("[",element,end=" ]  ")
    print()

print("\nQuantized Coefficients:")
print(quantized_coefficients)
print("\nDequantized Coefficients:")
print(dequantized_coefficients)
print("\nReconstructed Image:")
print(reconstructed_image)
