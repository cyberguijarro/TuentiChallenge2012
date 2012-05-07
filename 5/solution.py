import datetime
import fileinput

#              0  1  2  3  4  5  6  7  8  9
full_counts = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6]

def process_number_old_clock(number):
    digits = divmod(number, 10)
    return full_counts[digits[0]] + full_counts[digits[1]]

def process_time_old_clock(time):
    return sum(map(process_number_old_clock, [time.hour, time.minute, time.second]))

deltas = {
    0: {      0: 0, 1: 0},
    1: {      1: 0, 2: 4},
    2: {0: 2, 2: 0, 3: 1},
    3: {0: 2, 3: 0, 4: 1},
    4: {      4: 0, 5: 2},
    5: {0: 2, 5: 0, 6: 1},
    6: {      6: 0, 7: 1},
    7: {      7: 0, 8: 4},
    8: {      8: 0, 9: 0},
    9: {0: 1, 9: 0}
}

def process_number_new_clock(previous, current):
    previous = divmod(previous, 10)
    current = divmod(current, 10)
    
    return deltas[previous[0]][current[0]] + deltas[previous[1]][current[1]]

def process_time_new_clock(previous, current):
    r = sum(map(process_number_new_clock, 
                   [previous.hour, previous.minute, previous.second],
                   [current.hour, current.minute, current.second]))
    return r

def times(start, count):
    current = start

    for index in range(count):
        #print current
        yield current
        current += datetime.timedelta(0, 1)

# Some precomputations
base_time = datetime.datetime(2000, 1, 1)
old_clock_one_day_consumption = sum(map(process_time_old_clock, times(base_time, 3600*24)))
day_transition_new_clock = process_time_new_clock(datetime.time(23, 59, 59), datetime.time(0, 0, 0))
new_clock_one_day_consumption = sum(map(process_time_new_clock, times(base_time, 3600*24 - 1), times(base_time + datetime.timedelta(0, 1), 3600*24 - 1)))

for line in fileinput.input():
    # Problem data formatting
    start, end = line.split(' - ')
    start = datetime.datetime.strptime(start, '%Y-%m-%d %H:%M:%S')
    end = end.rstrip('\n ')
    end = datetime.datetime.strptime(end, '%Y-%m-%d %H:%M:%S')
    diff = end - start;

    old_clock_consumption = diff.days*old_clock_one_day_consumption + sum(map(process_time_old_clock, times(base_time, diff.seconds + 1)))
    new_clock_consumption = 36 + diff.days*(new_clock_one_day_consumption + day_transition_new_clock) + sum(map(process_time_new_clock, times(base_time, diff.seconds), times(base_time + datetime.timedelta(0, 1), diff.seconds)))

    print old_clock_consumption - new_clock_consumption
