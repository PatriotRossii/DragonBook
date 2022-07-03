import sys


class Parser:
    def __init__(self):
        self.lookahead: str = sys.stdin.read(1)

    def expr(self):
        self.term()
        while True:
            if self.lookahead == "+" or self.lookahead == "-":
                symbol = self.lookahead

                self.match(self.lookahead)
                self.term()
                print(symbol, end="")
            else:
                return

    def term(self):
        if self.lookahead.isdigit():
            print(self.lookahead, end="")
            self.match(self.lookahead)
        else:
            raise RuntimeError("SYNTAX ERROR")

    def match(self, target: str):
        if self.lookahead == target:
            self.lookahead = sys.stdin.read(1)
        else:
            raise RuntimeError("SYNTAX ERROR")


if __name__ == "__main__":
    parser = Parser()
    parser.expr()
    print()
