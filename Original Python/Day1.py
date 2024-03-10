def number_of_increasing_values(val_list: list) -> int:
    num_increased = 0  # initialise counter
    for idx in range(len(val_list)):  # counts from 0 up to (len(val_list)-1)
        if type(val_list[idx]) != int:  # check that list value isn't already an int
            val_list[idx] = int(val_list[idx][0:-1])  # if it isn't an int we remove the \n from file and cast to int
        if (idx >= 1) and (val_list[idx] > val_list[idx - 1]):  # compare value to previous one starting from 2nd item
            num_increased += 1  # increment counter
    return num_increased


# Part 1
f = open("..\Personal txt Inputs\Day1.txt")
valuesList = f.readlines()
numIncreased = number_of_increasing_values(valuesList)
print(f"The number of measurements larger than the previous for the raw data are: {numIncreased}")

# Part 2
windowSize = 3
movSum = []
for i in range(windowSize,len(valuesList)+1):  # counts from 3 up to 2000
    movSum.append(sum(valuesList[i-windowSize:i]))
numIncreased = number_of_increasing_values(movSum)
print(f"The number of measurements larger than the previous for the averaged data is: {numIncreased}")
