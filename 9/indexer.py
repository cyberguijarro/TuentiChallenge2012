import fileinput
import dbm
import os.path
import sys

start = int(sys.argv[1])
end = int(sys.argv[2])

for document_index in range(start, end + 1):
    print 'Indexing document %04d...' % document_index

    index = dbm.open('indexes/index%04d' % document_index, 'n');
    file_position = 1

    for line in fileinput.input('./documents/%04d' % document_index):
        line_position = 1

        for word in line.split():
            if len(word) > 2:
                lower = word.lower()
                record = '{0}-{1},'.format(file_position, line_position)

                if lower in index:
                    index[lower] += (record)
                else:
                    index[lower] = record
        
            line_position += 1

        file_position += 1

    index.close()
