'''
Pretty CLI aims to provide an easy lookup dictionary for formatting command line text
https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
'''




pcli = {
    "df":"\033[0m",
    "default":"\033[0m",
    "reset":"\033[0m",
    "fg":{
        "default": "\033[39m",
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
        "white": "\033[97m",
    },
    "bg": {
        "default":"\033[49m",
        "black": "\033[40m",
        "salmon": "\033[41m",
        "green": "\033[42m",
        "brown": "\033[43m",
        "lilac": "\033[44m",
        "magenta": "\033[45m",
        "dark-cyan": "\033[46m",
        "grey": "\033[47m",
        "dark-grey": "\033[100m",
        "rich-red": "\033[101m",
        "deep-green": "\033[102m",
        "yellow": "\033[103m",
        "blue": "\033[104m",
        "pink": "\033[105m",
        "cyan": "\033[106m",
        "white": "\033[107m",
    },
    "font":{
        0 :"\033[10m",
        1 :"\033[11m",
        2 :"\033[12m",
        3 :"\033[13m",
        4 :"\033[14m",
        5 :"\033[15m",
        6 :"\033[16m",
        7 :"\033[17m",
        8 :"\033[18m",
        9 :"\033[19m",
        "default":"\033[10m"
    },
    "fx":{
    "bold":"\033[1m",
    "ul":"\033[4m",
    "nul":"\033[24m",
    "blink":"\033[5m",
    "noblink":"\033[25m",
    "inv":"\033[7m",
    "ninv":"\033[27m",
    "frame":"\033[51m",
    "noframe": "\033[54m",
    "cir": "\033[52m",
    "nocir": "\033[54m",
    "over": "\033[53m",
    "nover": "\033[55m"
    }
}



mgbg = pcli["bg"]["magenta"]
blbg = pcli["fg"]["black"]
spc =  "       "


if __name__ == "__main__":
    print(pcli["bg"]["cyan"] +  "                              " + pcli["reset"])
    print(pcli["bg"]["pink"] +  "         Trans                " + pcli["reset"])
    print(pcli["bg"]["white"]+pcli["fg"]["black"] + "             Rights           " + pcli["reset"])
    print(pcli["bg"]["pink"] +  "            Now!              " + pcli["reset"])
    print(pcli["bg"]["cyan"] +  "                              " + pcli["reset"])



    print("\n\nText Foreground Colour: Usually Supported")
    for colour in pcli["fg"]:
        print(pcli["fg"][colour] + "Sample Text Here, FG Colour:  " + colour + spc + pcli["reset"])
    print("\nText Background Colour: Usually Supported")
    for colour in pcli["bg"]:
        print(pcli["bg"][colour] + "Sample Text Here, BG Colour:  " + colour + spc +pcli["reset"])
        print(pcli["bg"][colour]+ pcli["fg"]["black"] + "Sample Text Here, BG Colour:  " + colour + spc +  pcli["reset"])
    print("\nText FX: Often Unsupported")
    for effect in pcli["fx"]:
        print(pcli["fx"][effect] + "Sample Text Here, Effect:  " + effect + spc + pcli["reset"])
    print("\nText Fonts: Often Unsupported")
    for font in pcli["font"]:
        print(pcli["font"][font] + "Sample Text Here, Font:  " + str(font) + spc + pcli["reset"])



