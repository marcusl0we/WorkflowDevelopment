f = open("Day7.txt")
data = f.readlines()

# Part 3 - refactor the two lines of code added to solve Part 2 into a solution that gives both Part 1 and 2 at once
crab_positions = [int(x.strip()) for x in data[0].split(',')]
# crab_positions = [16, 1, 2, 0, 4, 2, 7, 1, 2, 14]

max_crab_pos = max(crab_positions)

move_cost_dict = {}

for pos_under_test in range(max_crab_pos+1):  # positions to move to from 0 to max_crab_pos
    fuel_usage_lin = 0  # initialise the fuel that will be used for linear fuel usage model
    fuel_usage_exp = 0  # initialise the fuel that will be used for non-linear fuel usage model
    for crab in crab_positions:  # each crab is in a certain position
        fuel_usage = abs(crab - pos_under_test)
        fuel_usage_lin += fuel_usage
        fuel_usage_exp += int((fuel_usage * (fuel_usage + 1))/2)  # nth term expression for addition factorial
    move_cost_dict[pos_under_test] = [fuel_usage_lin, fuel_usage_exp]

# list comprehension to get first value of list for each dict key
linear = [move_cost_dict[x][0] for x in range(len(move_cost_dict))]
lowest_fuel_usage_lin = min(linear)
lowest_cost_pos_lin = linear.index(lowest_fuel_usage_lin)  # index of list comprehension will equal dict key

# list comprehension to get second value of list for each dict key
exp = [move_cost_dict[x][1] for x in range(len(move_cost_dict))]
lowest_fuel_usage_exp = min(exp)
lowest_cost_pos_exp = exp.index(lowest_fuel_usage_exp)  # index of list comprehension will equal dict key

print(f"The lowest fuel cost move using a linear fuel usage model is to position {lowest_cost_pos_lin} "
      f"which costs {lowest_fuel_usage_lin} fuel")
print(f"The lowest fuel cost move using an addition factorial fuel usage model is to position {lowest_cost_pos_exp} "
      f"which costs {lowest_fuel_usage_exp} fuel")


# # Part 1
# crab_positions = [int(x.strip()) for x in data[0].split(',')]
# # crab_positions = [16, 1, 2, 0, 4, 2, 7, 1, 2, 14]
#
# max_crab_pos = max(crab_positions)
#
# move_cost_dict = {}
#
# for pos_under_test in range(max_crab_pos+1):  # positions to move to from 0 to max_crab_pos
#     fuel_usage = 0  # initialise the fuel that will be used
#     for crab in crab_positions:  # each crab is in a certain position
#         fuel_usage += abs(crab - pos_under_test)
#     move_cost_dict[pos_under_test] = fuel_usage
#
# lowest_cost_pos = min(move_cost_dict, key=move_cost_dict.get)
# lowest_fuel_usage = move_cost_dict[lowest_cost_pos]
#
# print(f"The lowest fuel cost move using a linear fuel usage model is to position {lowest_cost_pos} "
#       f"which costs {lowest_fuel_usage} fuel")
#
#
# # Part 2
# crab_positions = [int(x.strip()) for x in data[0].split(',')]
# # crab_positions = [16, 1, 2, 0, 4, 2, 7, 1, 2, 14]
#
# max_crab_pos = max(crab_positions)
#
# move_cost_dict = {}
#
# for pos_under_test in range(max_crab_pos+1):  # positions to move to from 0 to max_crab_pos
#     fuel_usage_exp = 0  # initialise the fuel that will be used
#     for crab in crab_positions:  # each crab is in a certain position
#         fuel_usage = abs(crab - pos_under_test)
#         fuel_usage_exp += int((fuel_usage * (fuel_usage + 1))/2)  # nth term expression for addition factorial
#     move_cost_dict[pos_under_test] = fuel_usage_exp
#
# lowest_cost_pos = min(move_cost_dict, key=move_cost_dict.get)
# lowest_fuel_usage = move_cost_dict[lowest_cost_pos]
#
# print(f"The lowest fuel cost move using an addition factorial fuel usage model is to position {lowest_cost_pos} "
#       f"which costs {lowest_fuel_usage} fuel")
