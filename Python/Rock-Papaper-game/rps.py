import random

def get_choices():
        player_choice = input("Enter the choices(r,p,s): ")
        options = ["r","p","s"]
        computer_choice  = random.choice(options)
        choices = {"player":player_choice,"computer":computer_choice}
        return choices

def check_win(choices):
        player = choices["player"]
        computer = choices["computer"]

        if player == computer :
                return "Tie"

        elif ((player == "r") and (computer == "s") or \
              (player == "p") and (computer == "r") or \
              (player == "s") and (computer=="p")
              ):
              return "Player win"
         
        else:
            return "Computer wins"
        
current_choices = get_choices()
result = check_win(current_choices)
print(result)