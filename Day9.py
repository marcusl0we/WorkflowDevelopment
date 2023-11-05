import numpy as np

f = open("Day9.txt")
data = f.readlines()

# format data into a numpy array
data = [x.strip() for x in data]
for i, row in enumerate(data):
    data[i] = [char for char in row]
    data[i] = [int(x) for x in data[i]]
grid = np.array(data)

dimensions = grid.shape

risk_level_sum = 0
for i in range(dimensions[0]):
    for j in range(dimensions[1]):
        _above = 100
        _below = 100
        _left = 100
        _right = 100

        if not (i == 0):
            _above = grid[i - 1][j]
        if not (i == dimensions[0] - 1):
            _below = grid[i + 1][j]
        if not (j == 0):
            _left = grid[i][j - 1]
        if not (j == dimensions[1] - 1):
            _right = grid[i][j + 1]

        num_under_test = grid[i][j]

        if num_under_test < _above and \
                num_under_test < _below and \
                num_under_test < _left and \
                num_under_test < _right:
            risk_level_sum += num_under_test + 1


print(f"The sum of the risk levels are: {risk_level_sum}")
