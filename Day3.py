import copy


def useful_data_out_for_position(bin_list, position):
    """
    Function that takes a list of binary numbers and gets some useful data out for a certain position
    :param bin_list: string list of binary numbers
    :param position: requested position of binary number to look at
    :returns:
        zeros - number of zeros in that position
        ones - number of ones in that position
        z_list - sublist of binary numbers with a zero in the requested position
        o_list - sublist of binary numbers with a one in the requested position
    """
    zeros = 0
    ones = 0
    z_list = list()
    o_list = list()
    for x in bin_list:
        x = x.strip()
        if x[position] == '0':
            zeros += 1
            z_list.append(x)
        elif x[position] == '1':
            ones += 1
            o_list.append(x)
    return zeros, ones, z_list, o_list


# Part 1
f = open("Day3.txt")
binary_list = f.readlines()
num_bits = 12

# create a dictionary to contain bit info data
bit_info = {}
for i in range(1, num_bits + 1):
    # dictionary format - the key is bit position, and the list data is [number of zeros, number of ones]
    bit_info["bit{0}".format(i)] = [0, 0]

# populate data dictionary using function
for j in range(num_bits):
    data = useful_data_out_for_position(binary_list, j)
    bit_info["bit{0}".format(j + 1)][0] = data[0]
    bit_info["bit{0}".format(j + 1)][1] = data[1]

# read the information in data dictionary to decode data
gamma_rate = ''
for k in range(1, num_bits + 1):
    if bit_info["bit{0}".format(k)][0] > bit_info["bit{0}".format(k)][1]:
        gamma_rate += '0'
    else:
        gamma_rate += '1'
gamma_rate_dec = int(gamma_rate, 2)
print(f"The gamma rate: binary = {gamma_rate}, decimal = {gamma_rate_dec}")

# flip bits from gamma rate for epsilon rate and convert to decimal
epsilon_rate = ''.join(['1' if i == '0' else '0' for i in gamma_rate])
epsilon_rate_dec = int(epsilon_rate, 2)
print(f"The epsilon rate: binary = {epsilon_rate}, decimal = {epsilon_rate_dec}")

# multiply two rates in binary and get binary number output
power_consumption = bin(gamma_rate_dec * epsilon_rate_dec)
power_consumption_dec = gamma_rate_dec * epsilon_rate_dec
print(f"The power consumption: binary = {power_consumption}, decimal = {power_consumption_dec}\n")


# Part 2
# use the function to loop over a filtered list until the filtered list becomes one value for oxygen generator rating
filtered_list = copy.deepcopy(binary_list)
m = 0
while len(filtered_list) != 1:
    num_zeros, num_ones, zeros_list, ones_list = useful_data_out_for_position(filtered_list, m)
    if num_zeros > num_ones:
        filtered_list = zeros_list
        m += 1
    elif num_ones > num_zeros:
        filtered_list = ones_list
        m += 1
    elif num_ones == num_zeros:
        filtered_list = ones_list
        m += 1
oxygen_generator_rating = filtered_list[0]  # filtered_list should only contain one value now
oxygen_generator_rating_dec = int(oxygen_generator_rating, 2)
print(f"The oxygen generator rating: binary = {oxygen_generator_rating}, decimal = {oxygen_generator_rating_dec}")

# use the function to loop over a filtered list until the filtered list becomes one value for c02 scrubber rating
# essentially same code as above but switch the list that gets assigned to filtered list
filtered_list = copy.deepcopy(binary_list)
m = 0
while len(filtered_list) != 1:
    num_zeros, num_ones, zeros_list, ones_list = useful_data_out_for_position(filtered_list, m)
    if num_zeros > num_ones:
        filtered_list = ones_list  # switch what list we assign for c02 scrubber rating
        m += 1
    elif num_ones > num_zeros:
        filtered_list = zeros_list  # switch what list we assign for c02 scrubber rating
        m += 1
    elif num_ones == num_zeros:
        filtered_list = zeros_list  # switch what list we assign for c02 scrubber rating
        m += 1
c02_scrubber_rating = filtered_list[0]  # filtered_list should only contain one value now
c02_scrubber_rating_dec = int(c02_scrubber_rating, 2)
print(f"The c02 scrubber rating: binary = {c02_scrubber_rating}, decimal = {c02_scrubber_rating_dec}")

life_support_rating = bin(oxygen_generator_rating_dec * c02_scrubber_rating_dec)
life_support_rating_dec = oxygen_generator_rating_dec * c02_scrubber_rating_dec
print(f"The life support rating: binary = {life_support_rating}, decimal = {life_support_rating_dec}")
