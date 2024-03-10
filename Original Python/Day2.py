import copy


def get_positional_data_from_instructions(instructions: list, part2: bool):
    horizontal_pos = 0
    depth_pos = 0
    aim = 0
    il = copy.deepcopy(instructions)
    for line in il:
        line = line.strip().split()
        if line[0] == 'forward':
            horizontal_pos += int(line[-1])
            if part2:
                depth_pos += aim * int(line[-1])
        elif line[0] == 'down':
            if part2:
                aim += int(line[-1])
            else:
                depth_pos += int(line[-1])
        elif line[0] == 'up':
            if part2:
                aim -= int(line[-1])
            else:
                depth_pos -= int(line[-1])
    return horizontal_pos, depth_pos, aim


f = open("..\Personal txt Inputs\Day2.txt")
instruction_list = f.readlines()

# Part 1
h_pos, d_pos, a = get_positional_data_from_instructions(instruction_list, False)
print(f"The Part 1 horizontal position is: {h_pos}")
print(f"The Part 1 depth position is: {d_pos}")
print(f"These numbers multiplied is: {h_pos * d_pos}\n")

# Part 2
h_pos, d_pos, a = get_positional_data_from_instructions(instruction_list, True)
print(f"The Part 2 horizontal position is: {h_pos}")
print(f"The Part 2 depth position is: {d_pos}")
print(f"These numbers multiplied is: {h_pos * d_pos}\n")
