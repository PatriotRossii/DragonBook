import sys


def S():
    global program
    if not program:
        print("SYNTAX ERROR")
        sys.exit(1)

    lookahead = program[0]
    
    if lookahead == "+":
        program = program[1:]
        S()
        S()
    elif lookahead == "-":
        program = program[1:]
        S()
        S()
    elif lookahead == "a":
        program = program[1:]
    else:
        print("SYNTAX ERROR")
        sys.exit(1)

    return program


if __name__ == "__main__":
    program = input()
    if S():
        print("SYNTAX ERROR")
    else:
        print("SUCCESS")
