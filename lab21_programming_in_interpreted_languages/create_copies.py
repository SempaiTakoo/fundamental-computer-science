from shutil import copy
from sys import argv

def name_format(filename: str):
    return [i[::-1] for i in filename[::-1].split('.', 1)][::-1]

def next_char(s: str):
    if s.isdigit():
        return str(int(s) + 1)
    if s == 'z':
        return 'a'
    if s == 'Z':
        return 'A'
    return chr(ord(s) + 1)

def copying_file(argv: list):
    if len(argv) == 0:
        print("\nError: Parameter [FILENAME] was not entered.")
        print("Try 'create_copies ?'\n")
        return
    if argv[0] == '?':
        print("\nThe command generates the specified number of copies of the file.")
        print("Copy names are created by adding the next letter/digit to the name of source file, starting with specified letter/digit.")
        print("create_ocpies [FILENAME] [NUMBER] [ENUMERATION]\n")
        return
    if len(argv) == 1:
        n, enum = 1, '1'
    else:
        n, enum = int(argv[1]), str(argv[2])
    filename = argv[0]
    name, format = name_format(filename)
    with open(filename) as f:
        for i in range(n):
            copy(filename, f"{name}{enum}.{format}")
            enum = next_char(enum)

if __name__ == '__main__':
    copying_file(argv[1:])