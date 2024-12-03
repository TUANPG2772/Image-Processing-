import numpy as np
from scipy.fftpack import dct, idct

def apply_dct(matrix):
    return dct(dct(matrix, axis=0, norm='ortho'), axis=1, norm='ortho')

def apply_idct(matrix):
    return idct(idct(matrix, axis=0, norm='ortho'), axis=1, norm='ortho')

# Example usage:
matrix = np.array([
          [139, 144, 149, 153, 155, 155, 155, 155],
          [144, 151, 153, 156, 159, 156, 156, 156],
          [150, 155, 160, 163, 158, 156, 156, 156],
          [159, 161, 162, 160, 160, 159, 159, 159],
          [159, 160, 161, 162, 162, 155, 155, 155],
          [161, 161, 161, 161, 160, 157, 157, 157],
          [162, 162, 161, 163, 162, 157, 157, 157],
          [162, 162, 161, 161, 163, 158, 158, 158 ]])

matrix1 = np.zeros_like(matrix)
for i in range(len(matrix)):
    for j in range(len(matrix[i])):
        matrix1[i][j] = matrix[i][j] - 128

quantization_table = np.array([[16, 11, 10, 16, 24, 40, 51, 61],
                               [12, 12, 14, 19, 26, 58, 60, 55],
                               [14, 13, 16, 24, 40, 57, 69, 56],
                               [14, 17, 22, 29, 51, 87, 80, 62],
                               [18, 22, 37, 56, 68, 109, 103, 77],
                               [24, 35, 55, 64, 81, 104, 113, 92],
                               [49, 64, 78, 87, 103, 121, 120, 101],
                               [72, 92, 95, 98, 112, 100, 103, 99]])

dct_result = apply_dct(matrix1)

luong_tu = dct_result / quantization_table

phan_luong_tu = np.round(luong_tu) * quantization_table

khoi_phuc = apply_idct(phan_luong_tu)

for i in range(len(khoi_phuc)):
    for j in range(len(khoi_phuc[i])):
        khoi_phuc[i][j] = np.round(khoi_phuc[i][j]) + 128

#idct_result = apply_idct(dct_result)

print("Original matrix:")
print(matrix)
print("\nDCT result:")
print(dct_result)
print("\nLuong_tu result:")
print(np.round(luong_tu))
print("\nPhan_luong_tu result:")
print(np.round(phan_luong_tu))

print("\nKhoi phuc result:")
print(khoi_phuc)
