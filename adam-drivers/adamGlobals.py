'''

Variables, Constants & Globals for adam_connect

'''


def success_message():
    print('\n*************** Success *****************')
    print('       ADAM Controller Connected \n\n')

def timeout_message():
    print('\n*************** ERROR *****************')
    print('Attempt to connect to the ADAM timed out. \n' + \
          'Make sure it\'s powered on and plugged in.')
    print('*************** ERROR *****************\n\n')

def os_errormessage():
    print('\n*************** ERROR *****************')
    print('Unable to connect to the ADAM. \n' + \
          'Make sure it\'s powered on and plugged in.')
    print('*************** ERROR *****************\n\n')



def hex_to_binary(hex_number: str, num_digits: int = 8) -> str:
    """
    Converts a hexadecimal value into a string representation
    of the corresponding binary value
    Args:
        hex_number: str hexadecimal value
        num_digits: integer value for length of binary value.
                    defaults to 8
    Returns:
        string representation of a binary number 0-padded
        to a minimum length of <num_digits>
    """
    return str(bin(int(hex_number, 16)))[2:].zfill(num_digits)


'''
Function above replaces this clunky mess
ch_group_a = int(words[7:8], base=16)
            print("Converting A Values")
            print(ch_group_a)
            group_a_bin = bin(ch_group_a)
            print(group_a_bin)
'''


def split(word):
    return list(word)

# Kept here so I can remember how I did it last time
def depreciated_split():
    print("Depreciated")
    # print(words)
    # print(words[0:2])  # First is thrown away
    # print(words[2:4])  # 2nd is 00 also thrown away
    # print(words[4:5])  # Contains Hex (convert to 4 bit binary) for CH:15~12 (Not available on 6052)
    # print(words[5:6])  # Contains Hex (convert to 4 bit binary) for CH:11~8 (Not available on 6052)
    # print(words[6:7])  # Contains Hex (convert to 4 bit binary) for CH:7~4 ) (ch_group_b)
    # print(words[7:8])  # Contains Hex (convert to 4 bit binary) for CH:3~0 ) (ch_group_a)