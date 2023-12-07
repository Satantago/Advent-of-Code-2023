def extract_calibration_value(line):
    first_digit = next(char for char in line if char.isdigit())
    last_digit = next(char for char in reversed(line) if char.isdigit())

    calibration_value = int(first_digit + last_digit)

    return calibration_value

def sum_calibration_values(file_path):
    total_sum = 0

    with open(file_path, 'r') as file:
        for line in file:
            calibration_value = extract_calibration_value(line)
            total_sum += calibration_value

    return total_sum

input_file_path = 'input.txt'
result = sum_calibration_values(input_file_path)

print(result)