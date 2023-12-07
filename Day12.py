import networkx as nx
import matplotlib.pyplot as plt
from collections import deque


# Function for adding one to the count if there is a found path in graph
def count_paths(path, print_output=True):
    if print_output:
        for i in range(len(path)):  # convert list to more readable print output
            print(path[i], end=" ")
        print()
    return 1


# Function to check if current vertex is already present in path, according to rules
def cave_not_been_visited(x: str, path, Part_1_or_2):
    if Part_1_or_2 == 'Part 1':  # do the conditions for part 1
        if x.isupper():  # if cave is uppercase, we can visit it multiple times so always return True
            return True
        if x.islower():  # if cave is lowercase, we can't visit it multiple times
            for i in range(len(path)):  # so then check if it is already on path by looping through path
                if path[i] == x:
                    return False  # return False as cave HAS been visited
            return True
    if Part_1_or_2 == 'Part 2':  # do the conditions for part 2
        if x.isupper():  # if cave is uppercase, we can visit it multiple times so always return True
            return True
        if x.islower():
            if x == 'start' or x == 'end':  # same conditions as before for star and end caves
                for i in range(len(path)):
                    if path[i] == x:
                        return False
                return True

            # Use a dict to keep track of how many times a node appears in path
            nodes_so_far = list(set(path))  # get unique nodes used so far on path to use as keys
            node_on_path_occurrences = {element: 0 for element in nodes_so_far}  # initialise each key to zero
            if x not in nodes_so_far:  # add dict key if node under test hasn't appeared yet and set to zero
                node_on_path_occurrences[x] = 0
            for i in range(len(path)):
                node_on_path_occurrences[path[i]] += 1  # count how many times each node appears on path, update dict

            # Flag to tell us whether any small cave has been visited twice already - this can only happen once
            small_cave_twice_once = False
            for key, value in node_on_path_occurrences.items():
                if key.islower() and value >= 2 and key != 'start' and key != 'end':  # visited twice already check
                    small_cave_twice_once = True

            # Check the occurrences of node under test using dict
            if node_on_path_occurrences[x] == 0:
                return True  # if visit counter is zero it hasn't appeared at all yet so can return True
            if node_on_path_occurrences[x] >= 1:  # if visit counter is one or bigger it has been visited before on path
                if small_cave_twice_once:  # so then check if another small cave has already been visited twice
                    return False  # if there already has been a second visit to small cave return false
                else:
                    return True  # otherwise we can visit that small cave a second time


# Use a modified Breadth First Search algorithm to find all paths in a graph from given source to destination
def find_paths(graph, source, destination, Part_1_or_2):

    # Variable to store number of paths found
    number_of_paths = 0

    # Create a queue which stores the paths currently explored, path lengths will increase as code goes on
    q = deque()  # this is a list of lists/paths, not a list of individual vertices

    # Path vector to store the current path and initialise stuff
    path = [source]
    q.append(path)

    while q:
        path = q.popleft()  # take the first built up path in the deque, path lengths will increase as code goes on
        last = path[len(path) - 1]  # get the last traversed node in path

        # If last vertex is the desired destination then add to the count for number of paths
        if last == destination:
            number_of_paths += count_paths(path, print_output=False)

        # Traverse to all the nodes connected to last vertex and push new path to queue
        for i in range(len(graph[last])):
            nodes_connected_to_last = list(graph[last].keys())  # get list of nodes from adjacency

            # check if node is in current path or can be added
            if cave_not_been_visited(nodes_connected_to_last[i], path, Part_1_or_2):
                new_path = path.copy()  # make a copy of it as its a new path that will need to be explored later
                new_path.append(nodes_connected_to_last[i])
                q.append(new_path)  # add the new path to later be explored to queue
    return number_of_paths


f = open("Day12.txt")
data = f.readlines()

data = [x.strip().split('-') for x in data]

# First use networkx to get an adjacency list of the graph
G = nx.Graph()
G.add_edges_from(data)

# Code to show a graph of the network using matplotlib
pos = nx.planar_layout(G)
fig, ax = plt.subplots()
nx.draw_networkx(G, pos=pos, ax=ax)
fig.tight_layout()
plt.show(block=False)

connected_nodes = dict(G.adjacency())

# Part 1
num_paths = find_paths(G, 'start', 'end', 'Part 1')
print(f"The number of paths from start to end for Part 1 was {num_paths}")

# Part 2 - time complexity quite slow for main input but does eventually print, is quicker for other examples
num_paths = find_paths(G, 'start', 'end', 'Part 2')
print(f"The number of paths from start to end for Part 2 was {num_paths}")

# https://www.geeksforgeeks.org/print-paths-given-source-destination-using-bfs/

plt.show()
