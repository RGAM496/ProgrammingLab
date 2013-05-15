from random import randint

def random_map (x, y, min_h, max_h):
    return [[randint(min_h, max_h) for i in range(y)] for j in range(x)]
