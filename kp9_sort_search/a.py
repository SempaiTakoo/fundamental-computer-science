import random, string

import random, string

def randomword(length):
   letters = string.ascii_lowercase
   return ''.join(random.choice(letters) for i in range(length))

with open('data.txt', 'r', encoding='utf-8') as f:
    mas = f.readlines()
for i in range(len(mas)):
    mas[i] = f"{randomword(5)} {random.randint(100, 999)} {mas[i]}"
with open('data.txt', 'w', encoding='utf-8') as f:
    f.write(f"{len(mas)} \n")
    f.writelines(mas)