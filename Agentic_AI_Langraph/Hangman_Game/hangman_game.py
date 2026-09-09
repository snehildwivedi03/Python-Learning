import random
from words import words 


hangman_art = {
    0: (
        "  +---+",
        "      |",
        "      |",
        "      |",
        "     ==="
    ),
    1: (
        "  +---+",
        "  O   |",
        "      |",
        "      |",
        "     ==="
    ),
    2: (
        "  +---+",
        "  O   |",
        "  |   |",
        "      |",
        "     ==="
    ),
    3: (
        "  +---+",
        "  O   |",
        " /|   |",
        "      |",
        "     ==="
    ),
    4: (
        "  +---+",
        "  O   |",
        " /|\\  |",
        "      |",
        "     ==="
    ),
    5: (
        "  +---+",
        "  O   |",
        " /|\\  |",
        " /    |",
        "     ==="
    ),
    6: (
        "  +---+",
        "  O   |",
        " /|\\  |",
        " / \\  |",
        "     ==="
    )
}


def display_man(wrong_guesses):
    art_key = min(wrong_guesses, len(hangman_art) - 1)
    for line in hangman_art[art_key]:
        print(line)
    print()

def display_spaces(spaces):
    print(" ".join(spaces))
    print()

def display_avail_attempts(max_attempts, wrong_guesses):
    remaining = max_attempts - wrong_guesses
    print(f"Attempts remaining: {remaining}")
    print("-" * 25)

def display_answer(answer):
    print(" ".join(answer))
    print()


def main():
    answer = random.choice(list(words.keys()))
    spaces = ["_"] * len(answer)
    max_attempts = 7
    wrong_guesses = 0
    guessed_letters = set()
    is_running = True
    hint_used = False

    while(is_running):
        display_man(wrong_guesses)
        display_spaces(spaces)
        display_avail_attempts(max_attempts, wrong_guesses)

        guess = input("Enter a letter: ").lower()
        print()

        if len(guess) != 1 or not guess.isalpha():
            print("Invalid input!\n")
            continue

        if(guess in guessed_letters):
            print(f"'{guess}' has already been guessed.\n")
            continue

        guessed_letters.add(guess)

        if guess in answer:
            for i in range(len(answer)):
                if answer[i] == guess:
                    spaces[i] = guess
        else:
            wrong_guesses += 1

        if wrong_guesses >= 2 and not hint_used:
            hint_prompt = input("Do you want a hint? (cost 1 attempt) [yes/no]: ").lower()
            print()
            if(hint_prompt == "yes"):
                print(f"Hint: {words[answer]}\n")
                hint_used = True
            else:
                hint_used = True

        if "_" not in spaces:
            display_man(wrong_guesses)
            display_answer(answer)
            print(f"YOU WIN! You took {wrong_guesses} wrong attempts.")
            is_running = False

        elif wrong_guesses == max_attempts:
            display_man(wrong_guesses)
            display_answer(answer)
            print("YOU LOSE!")
            is_running = False


if __name__ == "__main__":
    main()