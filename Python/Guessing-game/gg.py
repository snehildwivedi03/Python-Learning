from random import randint

player_number = input("Select the digit's range you want to play (1,2,3): ")
range_digit = int(player_number)
max_attempts = 7

def random_with_N_digit(range_digit):
    range_start = 10**(range_digit-1)
    range_end = (10**range_digit) -1
    return randint(range_start,range_end)

secret_number = random_with_N_digit(range_digit)
print(f"(Psst... for testing, the secret number is {secret_number})")


user_ip = input("Tell me the number: ")
user_no = int(user_ip)

attempts=0

while attempts < max_attempts :
    guess_no = int(input(f"Attempt {attempts + 1}/{max_attempts} - Give the number you want to guess: "))

    attempts += 1 
    
    if guess_no == secret_number:
        print(f"Correct! You won in {attempts} attempts.")
        break
    elif guess_no > secret_number:
        print("Too high! Try a lower number.\n")
    else:
        print("Too low! Try a higher number.\n")

# If loop finishes without breaking, user ran out of tries
else:
    print(f"Game Over! You've used all {max_attempts} attempts. The secret number was {secret_number}.")


