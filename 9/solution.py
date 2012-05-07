import fileinput
import sys
import dbm

DOCUMENT_COUNT = 800

log = open("log.txt", "w+")

instances = int(sys.stdin.readline().strip())
log.write(str(instances) + '\n')

for instance in range(instances):
    line = sys.stdin.readline().strip()
    log.write(line + '\n')
    word, occurence = line.split()
    occurence = int(occurence)

    for document_index in range(1, DOCUMENT_COUNT + 1):
        index = dbm.open('indexes/index%04d' % document_index, 'r');
    
        if word in index:
            occurences = index[word].split(',')[0:-1]

            if len(occurences) >= occurence:
                print '%d-%s' % (document_index, occurences[occurence - 1])
                break
            else:
                occurence -= len(occurences)

        index.close()
