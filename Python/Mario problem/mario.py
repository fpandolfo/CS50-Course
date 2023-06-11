def main():
    while True:
        try:
            height = int(input("Height: "))
            blank = height
            if 1 <= height <= 8:
                break
        except:
            continue
        
    pyramid(height, blank)
    
def pyramid(height, blank):
    if height == 0:
        return 0
        
    pyramid(height - 1, blank)
    print(" " * (blank - height) + "#" * height, end='  ')
    print("#" * height)

main()