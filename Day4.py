import numpy as np


def card_winner_check(i_card):  # function to check if an individual card has won
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
    # each item in bingo_cards_marked list is a 5x5 truth table, initialised all False
    bingo_cards_marked.append(np.array([[False]*card_size for i in range(card_size)]))

# initialise list of card totals for all cards, list index corresponds to card number in .txt input
card_total = [np.sum(card) for card in bingo_cards]

# For Part 2, initialise dictionary stating win order index of boards along with bingo number for it
order_of_winning_boards = {}

# now loop through bingo numbers and check for a winner every number
for num in bingo_numbers:  # pass in the numbers in list of bingo numbers
    for ii, card in enumerate(bingo_cards):  # check that number in every bingo card
        # locate row,column of that number in that card
        find = np.where(card == num)
        if find[0].size > 0:  # if result of np.where is not empty (i.e. number found) do the next bit of code
            row = find[0][0]
            column = find[1][0]
            # minus found number from card cumulative sum to get sum of unmarked numbers after card win
            card_total[ii] = card_total[ii] - card[row][column]
            # multidimensional index format: bingo_cards_marked[card ID][card row][card column]
            bingo_cards_marked[ii][row][column] = True
            bingo = card_winner_check(bingo_cards_marked[ii])
            if bingo != 0:  # if bingo == 1 that means the card has won
                order_of_winning_boards.update({ii: num})
                # as the card has now won, no need to do any further operations so can discard by setting to None
                bingo_cards[ii] = []
                bingo_cards_marked[ii] = []

first_win_idx = list(order_of_winning_boards.keys())[0]
first_win_num = order_of_winning_boards[first_win_idx]

last_win_idx = list(order_of_winning_boards.keys())[-1]
last_win_num = order_of_winning_boards[last_win_idx]

# Part 1
print(f"The first winning card has an unmarked number sum of {card_total[first_win_idx]}, "
      f"multiplied by the bingo number of {first_win_num} is {card_total[first_win_idx]*first_win_num}")

# Part 2
print(f"The last winning card has an unmarked number sum of {card_total[last_win_idx]}, "
      f"multiplied by the bingo number of {last_win_num} is {card_total[last_win_idx]*last_win_num}")
