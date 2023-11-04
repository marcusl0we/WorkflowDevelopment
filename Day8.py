import itertools

f = open("Day8.txt") 
data = f.readlines()

# Part 1
# 0 abcefg  6
# 1 cf      2
# 2 acdeg   5
# 3 acdfg   5
# 4 bcdf    4
# 5 abdfg   5
# 6 abdefg  6
# 7 acf     3
# 8 abcdefg 7
# 9 abcdfg  6

# convert data to format we want
segments = [x.strip().split() for x in data]

# only get last 4 elements in each line
output = [x[11:] for x in segments]

# flatten everything to do _one loop over to count
output = list(itertools.chain.from_iterable(output))

num_unique_uses = list(filter(lambda x: len(x)==2 or len(x)==4 or len(x)==3 or len(x)==7, output))

print(f"The number of times the digits 1,4,7 and 8 appear are {len(num_unique_uses)}")

# Part 2
# LETTERED DIAGRAM:
#   AAAA
#  B    C
#  B    C
#   DDDD
#  E    F
#  E    F
#   GGGG

def input_decipher(input_under_test):
    """
    The aim for this algorithm is to get a set for each number from zero to nine, of mixed up letters from the
    conventional 7 segment display, that will display that number.
    """
    # first, deduce the unique char length numbers
    for inp in input_under_test:
        if len(inp) == 2:  # unique length of 2 is trying to output one
            _one = set([char for char in inp])  # convert string to set of char
            break
    for inp in input_under_test:
        if len(inp) == 3:  # unique length of 3 is trying to output seven
            _seven = set([char for char in inp])  # convert string to set of char
            diff = list(_seven.difference(_one))  # create a list from the singular char difference to be sub-scriptable
            seg_A_confirmed = diff[0]  # we know this segment difference is segment A in the diagram
            break
    for inp in input_under_test:
        if len(inp) == 4:  # unique length of 4 is trying to output four
            _four = set([char for char in inp])  # convert string to set of char
            break
    for inp in input_under_test:
        if len(inp) == 7:  # unique length of 7 is trying to output eight
            _eight = set([char for char in inp])  # convert string to set of char
            # use the segment difference between numbers eight and four to get options for segment E and G
            diff = _eight.difference(_four)
            diff.remove(seg_A_confirmed)  # remove a confirmed segment we already know is true to refine options
            diff = list(diff)  # turn into a list to become sub-scriptable to fine tune options for segment E and G
            seg_E_opt1 = diff[0]
            seg_E_opt2 = diff[1]
            seg_G_opt1 = diff[0]
            seg_G_opt2 = diff[1]
            break

    # now we can further deduce segment options for numbers that use 5 segments
    possible_235 = []  # numbers that use 5 segments are two, three and five
    for inp in input_under_test:
        if len(inp) == 5:  # this is trying to output either two, three and five
            possible_235.append(set([char for char in inp]))

    for x in possible_235:  # now loop over those numbers and do a difference to known numbers to deduce more numbers
        diff = x.difference(_one)
        # we know a difference of 3 segments between five seg numbers and two seg number has to make that number a three
        if len(diff) == 3:
            _three = x
            possible_235.remove(_three)
            break

    # the two remaining numbers of two and five in possible_235 can be better compared to segments of four
    for x in possible_235:
        diff = x.difference(_four)
        diff.remove(seg_A_confirmed)
        if len(diff) == 2:
            _two = x
            possible_235.remove(_two)
    _five = possible_235[0]  # last one has to be segments for five

    # now we use newly found number of three to compare against other known numbers to confirm previous segment options
    diff = _three.difference(_four)
    diff.remove(seg_A_confirmed)  # narrow down known segments to better match unknown segments
    diff = list(diff)  # make the set sub-scriptable
    seg_G_confirmed = diff[0]  # now we can confirm the options we had for segments E and G
    if seg_G_confirmed == seg_G_opt1:
        seg_E_confirmed = seg_E_opt2
    elif seg_G_confirmed == seg_G_opt2:
        seg_E_confirmed = seg_E_opt1

    # finally deduce numbers for 6 segment numbers
    possible_069 = []
    for inp in input_under_test:
        if len(inp) == 6:  # this is trying to output either zero, six, or nine
            possible_069.append(set([char for char in inp]))
    for x in possible_069:
        diff = x.difference(_five)
        if len(diff) == 2:  # number of segments difference of 2 when compared to number five has to be number zero
            _zero = x
            continue
        elif len(diff) == 1:  # otherwise number of segments difference of 1 could be either six or nine
            diff = list(diff)
            if diff[0] == seg_E_confirmed:  # use the confirmed letter for segment E found earlier to confirm which
                _six = x
            else:
                _nine = x
    return _zero, _one, _two, _three, _four, _five, _six, _seven, _eight, _nine


# get the input and display outputs from the correctly formatted data
seg_input = [x[0:10] for x in segments]
seg_output = [x[11:] for x in segments]

displays = []  # initialise the list of display output numbers to sum later
for i, inp_under_test in enumerate(seg_input):
    zero, one, two, three, four, five, six, seven, eight, nine = input_decipher(inp_under_test)  # use function
    disp_str = ''  # initialise the individual display number as a string to cast to int later
    for out in seg_output[i]:
        out = set([char for char in out])  # convert to set to compare against deciphered number sets
        if out == zero:
            disp_str += '0'
        elif out == one:
            disp_str += '1'
        elif out == two:
            disp_str += '2'
        elif out == three:
            disp_str += '3'
        elif out == four:
            disp_str += '4'
        elif out == five:
            disp_str += '5'
        elif out == six:
            disp_str += '6'
        elif out == seven:
            disp_str += '7'
        elif out == eight:
            disp_str += '8'
        elif out == nine:
            disp_str += '9'
    disp_num = int(disp_str)
    displays.append(disp_num)

print(f"Total of each of the deciphered four number display outputs is: {sum(displays)}")
