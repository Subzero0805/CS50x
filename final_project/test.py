from pyrsistent import b


a = 0

def add(a):
    a = a +  1
    return a

a = add(a)

print(a)