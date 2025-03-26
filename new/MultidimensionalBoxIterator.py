import numpy as np

def rho(a, b):
    return max([abs(x[0]-x[1]) for x in zip(a, b)])

def minimum_dist(items, coords):
    min_d = 1e9
    for t in items:
        min_d = min(min_d, rho(coords, t))
    return min_d

class MultidimensionalBoxIterator:
    def __init__(self, dims, r):
        self.dims, self.r = dims, r
        self.size = len(dims)
        self.p_dims = [1] * (self.size + 1)

        for i in range(self.size-1, -1, -1):
            self.p_dims[i] = self.p_dims[i+1] * self.dims[i]

        self.verbose = False

    def get_number(self, coords):
        pos = 0
        for i in range(0, len(coords)):
            pos += self.p_dims[i + 1] * coords[i]
        return pos

    def get_coords(self, l):
        coords = []
        for i in range(self.size):
            coords.append((l // self.p_dims[i + 1]) % self.dims[i])
        return tuple(coords)

    def place_next(self, items, l):
        box_size = self.p_dims[0]

        while(l < box_size):
            c = self.get_coords(l)
            if(minimum_dist(items, c) >= self.r): 
                items.append(c)
                return l
            l += 1
        return -1

    def next_combination(self, items):
        M = len(items)

        while(len(items) > 0):
            l = self.get_number(items.pop()) + 1
            
            repeat = M - len(items)
            for _ in range(repeat):
                if (l := self.place_next(items, l)) < 0:
                    break
            
            if len(items) == M:
                break
            
        return items

    def run(self, M):
        l, cnt, items = 0, 0, []
        
        for i in range(M):
            if((l := self.place_next(items, l)) < 0):
                return cnt

        start = self.get_number(items[0])

        while len(items) > 0:
            cnt += 1

            if self.verbose:
                pos = self.get_number(items[0])
                if(pos != start):
                    start = pos
                    print(f'start position moved to {items[0]}')

                if self.size == 2:
                    field = np.zeros((self.dims[0], self.dims[1]))
                    print('Next combination: ')
                    for t in items:
                        field[t[0], t[1]] = 1
                    print(field)

            items = self.next_combination(items)

        return cnt

from sympy import binomial

def test_main():
    A, B, C = 8, 8, 8
    r, k = 7, 4

    m = MultidimensionalBoxIterator([A, B, C], r)
    m.verbose = True
    
    print(m.run(k), binomial(A*B*C, k))
    #print(binomial(A*B*C, k))

def test_2d(): # OEIS A061996
    ans = []
    for N in range(1, 10):
        m = MultidimensionalBoxIterator([N, N], 2)
        ans.append(m.run(3))
    print(ans)

def test_3d(): # OEIS A166540
    ans = []
    for N in range(1, 8):
        m = MultidimensionalBoxIterator([N, N, N], 2)
        ans.append(m.run(2))
    print(ans)

if __name__ == '__main__':
    #test_3d()
    test_main()
