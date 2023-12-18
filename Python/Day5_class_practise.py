import numpy as np


class HydrothermalVent:
    def __init__(self, x1, y1, x2, y2):
        # set up instance of a hydrothermal vent line with the line end point coordinates and line coverage list
        self.x1 = x1
        self.x2 = x2
        self.y1 = y1
        self.y2 = y2
        self.coverage_x = []
        self.coverage_y = []

        # depending on which line type it is use a different method to get coverage
        if x1 == x2 or y1 == y2:
            self._vent_straight_line_coverage()
        else:
            self._vent_diagonal_line_coverage()

    def _vent_straight_line_coverage(self):
        if self.x1 == self.x2:  # straight lines have one or other coordinate the same
            start = min(self.y1, self.y2)
            end = max(self.y1, self.y2) + 1
            for num in range(start, end):  # so update the other coordinate coverage list accordingly
                self.coverage_y.append(num)
                self.coverage_x.append(self.x1)
        elif self.y1 == self.y2:  # do the same for the y coord
            start = min(self.x1, self.x2)
            end = max(self.x1, self.x2) + 1
            for num in range(start, end):
                self.coverage_x.append(num)
                self.coverage_y.append(self.y1)

    def _vent_diagonal_line_coverage(self):
        start_x, end_x, start_y, end_y = self.x1, self.x2, self.y1, self.y2
        if start_x < end_x:  # use this to get range() step value accordingly, step will either be +ve or -ve
            step_x = 1
            end_x = end_x + 1  # done to include the end coordinate in the coverage list
        else:
            step_x = -1
            end_x = end_x - 1
        if start_y < end_y:  # do the same for y coord
            step_y = 1
            end_y = end_y + 1
        else:
            step_y = -1
            end_y = end_y - 1
        for numX in range(start_x, end_x, step_x):  # add x and y coord for diagonals to the coverage list
            self.coverage_x.append(numX)
        for numY in range(start_y, end_y, step_y):
            self.coverage_y.append(numY)
        return


class HydrothermalVentDiagram:

    def __init__(self):
        self.diagram = np.array([[0]*1000 for i in range(1000)])  # initialise empty diagram when object created

    def update(self, vent: HydrothermalVent):  # method to update the diagram with a specific vent object
        for i in range(len(vent.coverage_x)):
            column = vent.coverage_x[i]
            row = vent.coverage_y[i]
            self.diagram[row, column] += 1


if __name__ == '__main__':  # not really needed but done so external import of classes above won't run code below
    f = open("..\Personal txt Inputs\Day5.txt")
    data = f.readlines()  # reformat input text to a list of 4 integers without other stuff
    data = [x.strip().replace(' -> ', ',') for x in data]
    data = [x.split(',') for x in data]
    data = [list(map(int, x)) for x in data]

    part1_diagram = HydrothermalVentDiagram()  # create two diagram object instances for part one and two
    part2_diagram = HydrothermalVentDiagram()
    for vent_idx in data:
        x_1, y_1, x_2, y_2 = vent_idx[0], vent_idx[1], vent_idx[2], vent_idx[3]
        hydrothermal_vent = HydrothermalVent(x_1, y_1, x_2, y_2)  # create a vent object instance
        if x_1 == x_2 or y_1 == y_2:  # only update the part 1 diagram if the vent is horizontal or vertical
            part1_diagram.update(hydrothermal_vent)
        part2_diagram.update(hydrothermal_vent)  # otherwise, part 2 diagram will update for all vents

    part1_bigger_than_2 = np.where(part1_diagram.diagram >= 2)  # find where at least two vents overlap
    part1_bigger_than_2 = len(part1_bigger_than_2[0])
    print(f"The num. of overlapping points for horizontal/vertical hydrothermal vent lines are: {part1_bigger_than_2}")

    part2_bigger_than_2 = np.where(part2_diagram.diagram >= 2)
    part2_bigger_than_2 = len(part2_bigger_than_2[0])
    print(f"The num. of overlapping points for all hydrothermal vent lines are: {part2_bigger_than_2}")
