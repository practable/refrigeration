'''
Pretty CLI aims to provide an easy lookup dictionary for formatting command line text
https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
'''




pcli = {
    "default":"\033[0m",
    "reset":"\033[0m",
    "fg":{
        "default": "\033[39m",
        "white": "\033[39m",
        "black":"\033[30m",
        "red":"\033[31m",
        "green":"\033[32m",
        "brown":"\033[33m",
        "lilac":"\033[34m",
        "magenta":"\033[35m",
        "dark-cyan":"\033[36m",
        "grey":"\033[37m",
        "dark-grey": "\033[90m",
        "rich-red": "\033[91m",
        "deep-green": "\033[92m",
        "yellow": "\033[93m",
        "blue": "\033[94m",
        "pink": "\033[95m",
        "cyan": "\033[96m",
        "bone-white": "\033[97m",
    },
    "bg": {
        "black": "\033[40m",
        "salmon": "\033[41m",
        "green": "\033[42m",
        "brown": "\033[43m",
        "lilac": "\033[44m",
        "magenta": "\033[45m",
        "dark-cyan": "\033[36m",
        "grey": "\033[37m",
        "dark-grey": "\033[90m",
        "rich-red": "\033[91m",
        "deep-green": "\033[92m",
        "yellow": "\033[93m",
        "blue": "\033[94m",
        "pink": "\033[95m",
        "cyan": "\033[96m",
        "bone-white": "\033[97m",
        "x":"\033[45m "
    }

}

print(pcli["fg"]["black"] + "Sample Text Here")
print(pcli["fg"]["red"] + "Sample Text Here")
print(pcli["default"] + "Sample Text Here")

print(pcli["bg"]["x"] + "Sample Text Here")
