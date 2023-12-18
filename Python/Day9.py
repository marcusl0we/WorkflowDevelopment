import numpy as np

f = open("..\Personal txt Inputs\Day9.txt")
data = f.readlines()

# format data into a numpy array
data = [x.strip() for x in data]
for i, row in enumerate(data):
    data[i] = [char for char in row]
    data[i] = [int(x) for x in data[i]]
grid = np.array(data)

dimensions = grid.shape  # get dimensions of map

risk_level_sum = 0  # initialise sum
lowest_points = []  # for part 2
for i in range(dimensions[0]):
    for j in range(dimensions[1]):
        _above = 100  # set numbers as high numbers if point doesn't exist e.g. beyond edge of map
        _below = 100
        _left = 100
        _right = 100

        if not (i == 0):  # check the number above the point
            _above = grid[i - 1][j]
        if not (i == dimensions[0] - 1):  # then check the number below the point
            _below = grid[i + 1][j]
        if not (j == 0):  # then check the number to left of point
            _left = grid[i][j - 1]
        if not (j == dimensions[1] - 1):  # then check number to right of point
            _right = grid[i][j + 1]

        num_under_test = grid[i][j]

        if num_under_test < _above and \
                num_under_test < _below and \
                num_under_test < _left and \
                num_under_test < _right:
            risk_level_sum += num_under_test + 1
            lowest_points.append([i, j])  # make a list of lowest points for part 2

print(f"The sum of the risk levels are: {risk_level_sum}")


# Part 2 - had to take inspiration from other solutions to figure out the confusing af recursive function

def basin_search_from_point(x, y):
    basin_add = 0  # set number to add to be zero for if point is already 9, or marked as 100 and checked
    if grid[x][y] == 100 or grid[x][y] == 9:
        return basin_add  # return zero to add and check next point
    grid[x][y] = 100  # if number isn't high point or marked 100 as point checked, mark it as point checked
    basin_add += 1  # add one to the number of points converted to checked
    if not (x == 0):  # check the number above the point
        basin_add += basin_search_from_point(x - 1, y)  # if number is marked as 100 or is 9, will add 0 to basin size
    if not (x == dimensions[0] - 1):  # then check the number below the point
        basin_add += basin_search_from_point(x + 1, y)
    if not (y == 0):  # then check the number to left of point
        basin_add += basin_search_from_point(x, y - 1)
    if not (y == dimensions[1] - 1):  # then check number to right of point
        basin_add += basin_search_from_point(x, y + 1)
    return basin_add  # should return the cumulative addition from all the recursive calls


sizes = []
for point in lowest_points:
    _x, _y = point[0], point[1]
    sizes.append(basin_search_from_point(_x, _y))
sizes.sort(reverse=True)

print(f"The multiplication of the three largest basins are: {sizes[0] * sizes[1] * sizes[2]}")


# Example data 2nd basin run through
#
# # 2199943210
# # 3987894921
# # 9856789892
# # 8767896789
# # 9899965678
#
# # 219994321+
# # 398789492+
# # 985678989+  first checks below, recursive function causes it to jump to next one below again and again to here
# # 8767896789  where finally it returns all surrounding as add 0
# # 9899965678
#
# # 219994321+
# # 39878949++  then it jumps back to a previous recursive function where it hasn't been able to check all around it
# # 985678989+
# # 8767896789
# # 9899965678
#
# # 21999432++  which continues recursively until it hits next point where all surrounding points returns add 0
# # 39878949++
# # 985678989+
# # 8767896789
# # 9899965678
#
# # 2199943+++
# # 39878949++
# # 985678989+
# # 8767896789
# # 9899965678
#
# # 219994++++
# # 39878949++
# # 985678989+
# # 8767896789
# # 9899965678
#
# # 219994++++  here again it jumps back out to previous recursive function to check all around
# # 398789+9++
# # 985678989+
# # 8767896789
# # 9899965678
#
# # 21999+++++  and continues to this point until it jumps out of everything with a cumulative add from original point
# # 398789+9++
# # 985678989+
# # 8767896789
# # 9899965678

# # Part 2 - old attempts at recursive function to mark grid as searched and added to basin size
#
# def basin_search_from_point(row, column):
#
#     gridcopy = copy.deepcopy(grid)
#     extra_points_2_search = []
#     gridcopy[row][column] = 100
#     _above = 100
#     _below = 100
#     _left = 100
#     _right = 100
#
#     if not (row == 0):
#         _above = gridcopy[row - 1][column]
#     if not (row == dimensions[0] - 1):
#         _below = gridcopy[row + 1][column]
#     if not (column == 0):
#         _left = gridcopy[row][column - 1]
#     if not (column == dimensions[1] - 1):
#         _right = gridcopy[row][column + 1]
#
#     if _above < 9:
#         extra_points_2_search.append([row - 1, column])
#         gridcopy[row - 1][column] = 100
#     if _below < 9:
#         extra_points_2_search.append([row + 1, column])
#         gridcopy[row + 1][column] = 100
#     if _left < 9:
#         extra_points_2_search.append([row, column - 1])
#         gridcopy[row][column - 1] = 100
#     if _right < 9:
#         extra_points_2_search.append([row, column + 1])
#         gridcopy[row][column + 1] = 100
#
#     return
#
#
# for i in range(dimensions[0]):
#     for j in range(dimensions[1]):
#
#         above = 100
#         below = 100
#         left = 100
#         right = 100
#
#         if not (i == 0):
#             above = grid[i - 1][j]
#         if not (i == dimensions[0] - 1):
#             below = grid[i + 1][j]
#         if not (j == 0):
#             left = grid[i][j - 1]
#         if not (j == dimensions[1] - 1):
#             right = grid[i][j + 1]
#
#         num_under_test = grid[i][j]
#
#         if num_under_test < above and \
#                 num_under_test < below and \
#                 num_under_test < left and \
#                 num_under_test < right:
#             extra_points_to_search = basin_search_from_point(i, j)
#             if not len(extra_points_to_search) == 0:
#                 for k in range(len(extra_points_to_search)):
#                     i = extra_points_to_search[k][0]
#                     j = extra_points_to_search[k][1]
#                     extra_points_to_search = basin_search_from_point(i, j)
