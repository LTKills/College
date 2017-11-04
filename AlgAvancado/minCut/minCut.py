import sys
import numpy
import copy


class Graph:

    def __init__(self, edges, residual, nvertexes, nedges):
        self.nedges = nedges
        self.nvertexes = nvertexes
        self.graph = copy.copy(edges)
        self.orig = copy.copy(edges)
        self.flow = sys.maxsize
        self.parent = {}
        self.visited = []

    def augmenting_path(self, source=1, sink=2):
        """ BFS to find a new augmenting path """
        self.parent = {}
        self.visited = []
        self.flow = sys.maxsize
        queue = []

        self.visited.append(source)
        queue.append(source)

        while(queue):
            u = queue.pop(0)

            for index, val in enumerate(self.graph[u]):
                if index not in self.visited and val > 0:
                    queue.append(index)
                    self.visited.append(index)
                    self.parent[index] = u

        return True if sink in self.visited else False

    def ford_fulkerson(self, source=1, sink=2):
        """Apply ford fulkerson algorithm and generate
        the residual graph for source 1 (0 in indexes)
        and sink 2 (1 in indexes)"""

        while(self.augmenting_path()):
            # find bottleneck flow
            s = sink
            while(s !=  source):
                self.flow = min (self.flow, self.graph[self.parent[s]][s])
                s = self.parent[s]

            # update residual graph and graph
            v = sink
            while(v !=  source):
                u = self.parent[v]
                self.graph[u][v] -= self.flow
                self.graph[v][u] += self.flow
                v = self.parent[v]

    def minCut(self, source=1, sink=2):
        for i in range(self.nvertexes):
            for j in range(self.nvertexes):
                if(self.graph[i][j] == 0 and self.orig[i][j] != 0):
                    print(str(i) + ' ' + str(j))


def solve(nvertexes, nedges):

    edges = numpy.zeros(shape=(nvertexes+1, nvertexes+1))
    residual = numpy.zeros(shape=(nvertexes+1, nvertexes+1))

    for _ in range(nedges):
        foo = [int(a) for a in input().split(' ')]
        edges[foo[0]][foo[1]] = foo[2]

    graph = Graph(edges, residual, nvertexes+1, nedges+1)
    graph.ford_fulkerson()
    graph.minCut()


def main(argv):

    nvertexes, nedges = [int(a) for a in input().split(' ')]
    while(nvertexes != 0 or nedges != 0):
        solve(nvertexes, nedges)
        print()
        nvertexes, nedges = [int(a) for a in input().split(' ')]

    pass


if __name__ == "__main__":
    main(sys.argv)
