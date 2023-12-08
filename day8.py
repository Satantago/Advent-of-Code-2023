def read_file(path):
    moves = ""
    map = {}
    with open(path, 'r') as file:
        moves = file.readline().strip()
        c = 0
        for line in file:
            if c == 0: 
                c += 1
                continue
            if line:
                key, value = line.split("=")
                key = key.strip()
                values = list(val.strip() for val in value[1:-1].split(','))
                values[0] = values[0][1:]
                values[1] = values[1][:-1]
                map[key] = values
    return moves, map


def part_one(map, moves):
    cur = 'AAA'
    target = 'ZZZ'
    res = 0
    while cur != target:
        for move in moves:
            cur = map[cur][0] if move == 'L' else map[cur][1]
            res += 1
    return res



import math

def starting_points(map, moves):
    start = []
    for key in map.keys():
        if key[-1] == 'A':
            start.append(key)
    return start
def part_two(map, moves):
    def first_z(cur):
        ans = 0
        while (cur[-1] != 'Z'):
            move = moves[ans % len(moves)]
            cur = map[cur][0] if move == 'L' else map[cur][1]
            ans += 1
        return ans
    start = starting_points(map, moves)
    res = 1
    for elt in start:
        res = math.lcm(res, first_z(elt))
    return res

moves, map = read_file("input88.txt")
print(part_two(map,moves))