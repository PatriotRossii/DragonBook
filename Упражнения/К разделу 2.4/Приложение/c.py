import sys


def match(target):
    global program
    global lookahead

    if lookahead == target:
        program = program[len(target):]
        if program:
            lookahead = program[0]
    else:
        print("SYNTAX ERROR")
        sys.exit(1)


def S():
    global program
    global lookahead

    if lookahead == "0":
        match("0")
        S()
        match("1")

    return program


if __name__ == "__main__":
    program = input()
    lookahead = program[0]

    if S():
        print("SYNTAX ERROR")
    else:
        print("SUCCESS")
