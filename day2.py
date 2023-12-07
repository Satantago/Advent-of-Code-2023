import math
import re
from collections import defaultdict

def read_file(file_path):
    with open(file_path) as file:
        lines = file.read().strip().split("\n")
    return lines

def process_input_lines(lines):
    good_ids_count = 0
    total_power = 0

    for line in lines:
        cleaned_parts = re.sub("[;,:]", "", line).split()
        color_max_counts = defaultdict(int)

        for count, color in zip(cleaned_parts[2::2], cleaned_parts[3::2]):
            color_max_counts[color] = max(color_max_counts[color], int(count))

        if color_max_counts["red"] <= 12 and color_max_counts["green"] <= 13 and color_max_counts["blue"] <= 14:
            good_ids_count += int(cleaned_parts[1])

        total_power += math.prod(color_max_counts.values())

    return good_ids_count, total_power

if __name__ == "__main__":
    input_file_path = "../../input.txt"
    input_lines = read_file(input_file_path)

    good_ids_result, total_power_result = process_input_lines(input_lines)

    print("good_ids:", good_ids_result)
    print("sum:", total_power_result)
