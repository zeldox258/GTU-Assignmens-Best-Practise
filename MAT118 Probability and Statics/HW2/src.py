import math
import numpy as np
import matplotlib.pyplot as plt

CRASH = 5
def print_table(X):
    table_a = []
    for i in range(CRASH):
        table_a.append(num_of_case(X, i))
    print("{}\t{}".format(i, table_a[i]))
    return table_a

def find_lambda(X, cc, yc):
    cases = 0
    for i in range(CRASH):
            cases += i * num_of_case(X, i)
    return cases / (cc * yc)
  

def pdf(X, mean):
    return (math.exp(-mean) * (mean**X) / math.factorial(X))

def estimate(Xe, mean, cc, yc):
    E = []
    for x in Xe:
        E.append(pdf(x, mean) * cc * yc)
    return E
  

               
def barplot(R, E):
    w = 0.1
    np_X = np.arange(CRASH)
    real_plt = plt.bar(np_X, R, w, label="true")
    est_plt = plt.bar(np_X + w, E, w, label="estimated")
    for i in range(0, CRASH):
        real_plt[i].set_color('g') 
        est_plt[i].set_color('r')
    plt.title("true compared estimated values")
    plt.xlabel("# of crashes")
    plt.ylabel("# of cases")
    plt.xticks(np_X + w/2, [i for i in range(0, CRASH)])
    plt.legend(loc="best")
    plt.show()
def input():
    file = open("manufacturing_defects.txt", "r")
    X = []
    for line in file:
        stripped_line = line.strip()
        line_list = stripped_line.split()
        X.append(line_list)
    file.close()
    return X
def num_of_case(X, crash_num):
    count = 0
    for line in X:
        count += line[1:].count(str(crash_num))
    return count
        
X = input()

companies = len(X[0]) - 2
years = len(X)-1#-1 up to file

table = print_table(X)

#C
print(table)

# find lambda
mean = find_lambda(X, companies, years)
print(mean)

# find estimations
estimated_table = estimate([i for i in range(len(table))], mean, companies, years)
print(estimated_table)

# plot
barplot(table, estimated_table)

# difference
print(np.array(table) - np.array(estimated_table))

               
