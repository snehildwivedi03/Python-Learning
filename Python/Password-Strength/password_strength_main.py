from string import punctuation

def get_pass_len(user_password):
   length = len(user_password)
   return length

def check_for_uppercase(user_password):
    upper_case_char = 0
    
    for char in user_password:
        if char.isupper():
            upper_case_char += 1
            
    return upper_case_char

def check_for_lowercase(user_password):
    lower_case_char = 0
    
    for char in user_password:
        if char.islower():
            lower_case_char += 1
            
    return lower_case_char

def check_for_special_characters(user_password):
   special_char = set(punctuation)
   no_of_sp_char = 0
   
   for char in user_password:
      if(char in special_char):
         no_of_sp_char+=1
      
   return no_of_sp_char

def check_strength(user_password):
    
    length = get_pass_len(user_password)
    upper_count = check_for_uppercase(user_password)
    lower_count = check_for_lowercase(user_password)
    special_count = check_for_special_characters(user_password)

    if length >= 16 and upper_count > 0 and lower_count > 0 and special_count > 0:
        print("Strength: Strongest Password")
    elif length >= 12 and upper_count > 0 and lower_count > 0:
        print("Strength: Strong Password ")
    elif length >= 8 and (upper_count > 0 or lower_count > 0):
        print("Strength: Good password")
    else:
        print("Strength: Weak Password (Must be longer and contain mixed case/symbols)")

def take_user_pass():
    max_retry = 4

    while max_retry > 0:
        user_password = input("Type your password: ")
        verify_pass = input(f"You typed {user_password}, is this correct? (yes or no): ").lower()

        if verify_pass in ("yes", "y"):
            check_for_uppercase(user_password)
            check_for_lowercase(user_password)
            check_for_special_characters(user_password)
            check_strength(user_password)
            break
        else:
            max_retry -= 1
            print(f"Let's try again. You have {max_retry} attempts remaining.\n")

    if max_retry == 0:
        print("Maximum retries reached. Exiting.")
        exit()
        

def main():
    print("===========================================")
    print("This is a password strength checker.")
    take_user_pass()
    

if __name__ == "__main__":
 main()