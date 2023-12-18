f = open("..\Personal txt Inputs\Day10.txt")
data = f.readlines()

data = [x.strip() for x in data]

# Part 1
corrupted_dict = {}  # dict to store which lines are corrupted and what exception was

# loop to process all lines
for j, line in enumerate(data):  # get a line from all lines
    line_processed = False
    while not line_processed:  # loop to process individual line down to error/incomplete
        for i, char in enumerate(line):  # get individual character in each line
            if char == ')' and line[i-1] != '(':  # check mismatched segment
                corrupted_dict[j] = char  # add mismatch to dict and what line it was
                line_processed = True  # break while loop to go to next line
                break  # break for loop
            elif char == ')' and line[i-1] == '(':  # if segment is complete/valid remove it from line
                line = line[0:i-1] + line[i+1:]  # remove segment
                break  # break for loop to restart from line check from beginning

            if char == ']' and line[i-1] != '[':
                corrupted_dict[j] = char
                line_processed = True
                break
            elif char == ']' and line[i-1] == '[':
                line = line[0:i-1] + line[i+1:]
                break

            if char == '}' and line[i-1] != '{':
                corrupted_dict[j] = char
                line_processed = True
                break
            elif char == '}' and line[i-1] == '{':
                line = line[0:i-1] + line[i+1:]
                break

            if char == '>' and line[i-1] != '<':
                corrupted_dict[j] = char
                line_processed = True
                break
            elif char == '>' and line[i-1] == '<':
                line = line[0:i-1] + line[i+1:]
                break

        if ')' in line or ']' in line or '}' in line or '>' in line:  # check if line is incomplete after each removal
            continue  # continue removing segments until line is confirmed incomplete or is invalid
        else:  # otherwise if none of those are in the line we can move on to next line
            data[j] = line  # for part 2, turn original line to incomplete line
            line_processed = True  # break while loop to move to next

# now use the dictionary to calculate score
syntax_error_score = 0
for key in corrupted_dict:
    if corrupted_dict[key] == ')':
        syntax_error_score += 3
    if corrupted_dict[key] == ']':
        syntax_error_score += 57
    if corrupted_dict[key] == '}':
        syntax_error_score += 1197
    if corrupted_dict[key] == '>':
        syntax_error_score += 25137
    data[key] = ''  # for part 2, discard the invalid lines

print(f"The total syntax error score is: {syntax_error_score}")

# Part 2
to_complete_lines = []  # initialise list to store strings that would complete incomplete lines

# first complete all the incomplete lines
for j, line in enumerate(data):
    if line == '':
        continue
    else:
        string = ''
        for i in range(len(line)-1, -1, -1):  # loop over incomplete string from end to start
            if line[i] == '(':
                string += ')'
            elif line[i] == '{':
                string += '}'
            elif line[i] == '[':
                string += ']'
            elif line[i] == '<':
                string += '>'
        to_complete_lines.append(string)

# then calculate the score for each string that would complete a line
scores = []
for string in to_complete_lines:
    score = 0
    for char in string:
        score = score * 5
        if char == ')':
            score += 1
        if char == ']':
            score += 2
        if char == '}':
            score += 3
        if char == '>':
            score += 4
    scores.append(score)

scores.sort()
middle = int((len(scores) + 1)/2)

print(f"The middle score is: {scores[middle-1]}")
