f = open("..\Personal txt Inputs\Day6.txt")
data = f.readlines()

# PART 1
# reformat first line of .txt to proper list of integers
lanternfish_timers = [int(x.strip()) for x in data[0].split(',')]

num_days = 80  # number of days to run for

day = 0  # initialise the day to start on
num_fish_to_add = 0  # initialise the number of fish to append to list at very start

while day <= num_days:

    if num_fish_to_add != 0:
        add_fish = [8 for i in range(num_fish_to_add)]
        lanternfish_timers.extend(add_fish)
    num_fish_to_add = 0  # reset the number of fish to add before next loop
    for i in range(len(lanternfish_timers)):
        if lanternfish_timers[i] == 0:
            lanternfish_timers[i] = 6
            num_fish_to_add += 1
            continue
        lanternfish_timers[i] -= 1

    day += 1

print(f"The number of fish after {num_days} days using the inefficient method is {len(lanternfish_timers)}")


# PART 2
# if we try to reuse a singular list like in part 1 but with num_days = 256 it takes too long to run

# reset lanternfish list
# lanternfish_timers = [3, 4, 3, 1, 2]
lanternfish_timers = [int(x.strip()) for x in data[0].split(',')]

num_days = 256  # number of days to run for

day = 1  # initialise the day to start on

lanternfish_dict = {}

# NEED TO REMEMBER TO ADD NO OF FISH WE START WITH AT END

while day <= num_days:

    num_fish_to_add = 0  # reset the number of new fish to add each day

    if not(day in lanternfish_dict):  # if dictionary key does NOT exist
        lanternfish_dict[day] = 0  # then initialise that key to be zero to be added to later

    for i in range(len(lanternfish_timers)):  # loop to check ONLY the original fishes
        if lanternfish_timers[i] == 0:
            lanternfish_timers[i] = 6
            num_fish_to_add += 1
            continue
        lanternfish_timers[i] -= 1

    # for each day, add the number of new fish that appeared that day due to the original fishes
    lanternfish_dict[day] += num_fish_to_add

    # this loop creates future day's dictionary keys for the number of new fish that we know will be added that day due
    # to previous fish
    if lanternfish_dict[day] != 0:
        exponential_add = lanternfish_dict[day]  # number of new fish to add will be at least original offspring, + new
        # newly added fish(es) from above will produce new fish in 8+1 days time
        future_days = day + 9
        if not(future_days in lanternfish_dict):  # if dictionary key does NOT exist
            lanternfish_dict[future_days] = 0  # then initialise that key to be zero
        lanternfish_dict[future_days] += exponential_add  # and then add the number of new fish to that day
        while future_days <= num_days:
            future_days += 7  # then the fish will produce a new one every 7 days
            if not (future_days in lanternfish_dict):  # if dictionary key does NOT exist
                lanternfish_dict[future_days] = 0  # then initialise that key to be zero
            lanternfish_dict[future_days] += exponential_add  # and then add the number of new fish to that day

    day += 1

numfish = 0
for i in range(1, num_days + 1):
    numfish += lanternfish_dict[i]

print(f"The number of fish after {num_days} days using the more efficient method is {numfish+len(lanternfish_timers)}")
