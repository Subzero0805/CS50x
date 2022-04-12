# TODO

from cs50 import get_string

text = get_string("Text:")


def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1
    return letters


def count_words(text):
    words = 1
    for i in range(len(text)):
        if text[i].isspace():
            words += 1
    return words


def count_sent(text):
    sent = 0
    for i in range(len(text)):
        if text[i] == "?" or text[i] == "!" or text[i] == ".":
            sent += 1
    return sent


num_letters = count_letters(text)
num_words = count_words(text)
num_sent = count_sent(text)

L = (num_letters / num_words) * 100
S = (num_sent / num_words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")

elif index > 16:
    print("Grade 16+")

else:
    print(f"Grade: {index}")
