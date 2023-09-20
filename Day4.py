import numpy as np


def card_winner_check(i_card):
    for idx in range(len(i_card)):
        if all(i_card[idx]):  # check the individual card row for bingo
            return 1
        elif all([x[idx] for x in i_card]):  # check the individual card column for bingo
            return 1
    return 0


f = open("Day4.txt")
data = f.readlines()

# reformat first line of .txt to proper list of integers
bingo_numbers = [int(x.strip()) for x in data[0].split(',')]

# reformat matrices in .txt to proper list of integer matrix rows
data = [x.strip().split() for x in data[2:] if x != '\n']
data = [list(map(int, x)) for x in data]  # convert strings to int

# reformat matrix rows to proper list of full matrices
# also initialise truth matrices for marking numbers as they happen
card_size = 5
bingo_cards = []
bingo_cards_marked = []
for i in range(0, len(data), card_size):
    # each item in bingo_cards list is a 5x5 card
    bingo_cards.append(np.array(data[i:i + card_size]))
    # each item in bingo_cards_marked list is a 5x5 truth table
    bingo_cards_marked.append(np.array([[False]*card_size for i in range(card_size)]))

# initialise list of card totals for all cards
card_total = [np.cumsum(card)[-1] for card in bingo_cards]

# initialise list for win order of boards for part 2
order_of_winning_boards = []

# Number extraction format: bingo_cards[card][row][column]
# now loop through bingo numbers and check for a winner every number (very messy nested loop but oh well lol)
for num in bingo_numbers:  # pass in the first number to check against every card
    for ii, card in enumerate(bingo_cards):
        find = np.where(card == num)
        if find[0].size > 0:  # if result of find is not empty do the next bit of code
            row = find[0][0]
            column = find[1][0]
            card_total[ii] = card_total[ii] - card[row][column]
            bingo_cards_marked[ii][row][column] = True
            bingo = card_winner_check(bingo_cards_marked[ii])
            if bingo != 0:
                order_of_winning_boards.append(ii)
                # 
                # print(f"The first winning card has an unmarked number sum of {card_total[ii]}, "
                #       f"multiplied by the bingo number of {num} is {card_total[ii]*num}")
                # break
    else:
        continue
    break

# 
# print(f"The first winning card has an unmarked number sum of {card_total[ii]}, "
#       f"multiplied by the bingo number of {num} is {card_total[ii]*num}")
# break
