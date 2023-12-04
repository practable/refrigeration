
import sys

## This is used to get arguments from command line input it is not needed here


if len(sys.argv) != 4:
    print(f"Usage: {sys.argv[0]} <host> <port> <num_connections>")
    sys.exit(1)
else:
    data = sys.argv[1:4]
    print(data)

