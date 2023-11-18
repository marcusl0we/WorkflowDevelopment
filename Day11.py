import numpy as np

f = open("Day11.txt")
data = f.readlines()

# reformat to proper list of integer matrix rows
data = [list(x.strip()) for x in data]
data = [list(map(int, x)) for x in data]  # convert strings to int

# Part 1
grid = np.array(data)  # turn to numpy array
dimensions = grid.shape  # get dimensions of map
grid_size = dimensions[0] * dimensions[1]  # for part 2
dimensions = [dimensions[0]-1, dimensions[1]-1]  # turn dimensions into index limits


def flash_stepper(n, _grid):
    num_flashes = 0
    full_grid_flash = False  # for part 2
    for i in range(n):  # main loop to execute for n number of steps
        pre_flash = np.where(_grid >= 9)  # returns a tuple with two lists, x and y coordinates
        _grid = _grid + 1
        if len(pre_flash[1]) == 0:  # means none ready to flash in this step so continue
            continue
        else:
            # turn coordinate list to easier to compare format
            pre_flash = [[pre_flash[0][x], pre_flash[1][x]] for x in range(len(pre_flash[1]))]

            # flash the octopuses that are ready to be flashed
            octo_flash(pre_flash, _grid)

            # add list of pre_flash to a list that tells us which ones have already flashed and can't flash again
            do_not_flash_again = pre_flash

            # check adjacent flash causing an unintended flash
            until_no_flash = True
            while until_no_flash:
                unint_flash = np.where(_grid >= 10)
                if len(unint_flash[1]) != 0:  # this means there are still existing octos to be flashed
                    # turn coordinate list to easier to compare format
                    unint_flash = [[unint_flash[0][x], unint_flash[1][x]] for x in range(len(unint_flash[1]))]

                    # only add extra flash if unintentional flash not already flashed in pre flash by comparing
                    extra_flash = [unint_flash[x] for x in range(len(unint_flash)) if not unint_flash[x] in do_not_flash_again]
                    octo_flash(extra_flash, _grid)
                    do_not_flash_again.extend(extra_flash)

                    # still need to make sure flashed octos at each step are returned to value of 0 so do this again
                    for k in range(len(do_not_flash_again)):
                        reset_x = do_not_flash_again[k][0]
                        reset_y = do_not_flash_again[k][1]
                        _grid[reset_x][reset_y] = 0  # reset each octopus to zero every time an original octo flashes
                else:
                    until_no_flash = False

        flashed = np.where(_grid == 0)  # find if any have flashed
        num_flashes += len(flashed[1])  # add to number of flashes if there are

        # for part 2
        if len(flashed[1]) == grid_size:  # check if the whole grid has flashed
            full_grid_flash = i + 1  # turn python index to step number

    return num_flashes, full_grid_flash, _grid


def octo_flash(flash, _grid):
    for j in range(len(flash)):  # loop over each octopus ready to flash
        flash_loc_x = flash[j][0]
        flash_loc_y = flash[j][1]

        # check edge cases
        if flash_loc_x == 0 and flash_loc_y == 0:  # top left position edge case
            _grid[flash_loc_x][flash_loc_y + 1] += 1  # number to the right
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1  # number to the bottom right
            _grid[flash_loc_x + 1][flash_loc_y] += 1  # number below

        elif flash_loc_x == 0 and flash_loc_y == dimensions[1]:  # top right position edge case
            _grid[flash_loc_x][flash_loc_y - 1] += 1  # number to the left
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1  # number to the bottom left
            _grid[flash_loc_x + 1][flash_loc_y] += 1  # number below

        elif flash_loc_x == dimensions[0] and flash_loc_y == 0:  # bottom left position edge case
            _grid[flash_loc_x - 1][flash_loc_y] += 1  # number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1  # number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1  # number to the right

        elif flash_loc_x == dimensions[0] and flash_loc_y == dimensions[1]:  # bottom right position edge case
            _grid[flash_loc_x - 1][flash_loc_y] += 1  # number above
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1  # number to the top left
            _grid[flash_loc_x][flash_loc_y - 1] += 1  # number to the left

        elif flash_loc_x == 0 and flash_loc_y in range(1, dimensions[1]):
            _grid[flash_loc_x][flash_loc_y - 1] += 1  # number to the left
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1  # number to the bottom left
            _grid[flash_loc_x + 1][flash_loc_y] += 1  # number below
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1  # number to the bottom right
            _grid[flash_loc_x][flash_loc_y + 1] += 1  # number to the right

        elif flash_loc_x == dimensions[0] and flash_loc_y in range(1, dimensions[1]):
            _grid[flash_loc_x][flash_loc_y - 1] += 1  # number to the left
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1  # number to the top left
            _grid[flash_loc_x - 1][flash_loc_y] += 1  # number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1  # number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1  # number to the right

        elif flash_loc_x in range(1, dimensions[0]) and flash_loc_y == 0:
            _grid[flash_loc_x - 1][flash_loc_y] += 1  # number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1  # number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1  # number to the right
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1  # number to the bottom right
            _grid[flash_loc_x + 1][flash_loc_y] += 1  # number below

        elif flash_loc_x in range(1, dimensions[0]) and flash_loc_y == dimensions[1]:
            _grid[flash_loc_x - 1][flash_loc_y] += 1  # number above
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1  # number to the top left
            _grid[flash_loc_x][flash_loc_y - 1] += 1  # number to the left
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1  # number to the bottom left
            _grid[flash_loc_x + 1][flash_loc_y] += 1  # number below

        else:
            _grid[flash_loc_x - 1][flash_loc_y] += 1  # number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1  # number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1  # number to the right
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1  # number to the bottom right
            _grid[flash_loc_x + 1][flash_loc_y] += 1  # number below
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1  # number to the bottom left
            _grid[flash_loc_x][flash_loc_y - 1] += 1  # number to the left
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1  # number to the top left

        for k in range(len(flash)):  # loop over each octopus ready to flash
            reset_x = flash[k][0]
            reset_y = flash[k][1]
            _grid[reset_x][reset_y] = 0  # reset each octopus to zero every time an original octo flashes

number_of_steps = 100
number_of_flashes, full_flash, grid_at_end = flash_stepper(number_of_steps, grid)

print(f"The number of flashes after {number_of_steps} steps are: {number_of_flashes}")


# Part 2
increment_steps = 10
while not full_flash:
    number_of_flashes, full_flash, grid_at_end = flash_stepper(increment_steps, grid_at_end)
    if not full_flash:
        number_of_steps += increment_steps
step_no = number_of_steps + full_flash
print(f"The first time the full grid flashed simultaneously was at step {step_no}")
