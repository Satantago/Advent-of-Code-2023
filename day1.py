import re

def read_input(file_path):
    with open(file_path) as file:
        data = file.read().strip()
    return data

def extract_numbers(lines):
    return [re.findall("\d", line) for line in lines]

def calibration_sum(numbers):
    return sum(int(n[0] + n[-1]) for n in numbers)

def perform_calibrations(data):
    numbers = extract_numbers(data.split("\n"))
    return calibration_sum(numbers)

if __name__ == "__main__":
    input_file_path = "input1.txt"
    input_data = read_input(input_file_path)

    result_part1 = perform_calibrations(input_data)
    print("Part 1 Result:", result_part1)

    replacement_dict = {"one": "one1one", "two": "two2two", "three": "three3three", 
                        "four": "four4four", "five": "five5five", "six": "six6six", 
                        "seven": "seven7seven", "eight": "eight8eight", "nine": "nine9nine"}
    
    for old_str, new_str in replacement_dict.items():
        input_data = input_data.replace(old_str, new_str)

    result_part2 = perform_calibrations(input_data)
    print("Part 2 Result:", result_part2)
