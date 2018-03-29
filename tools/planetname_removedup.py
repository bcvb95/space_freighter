namedict = {}

def remove_num(_name):
    """ Remove numbers from name """
    if _name[0].isdigit():
        return ""
    for i in range(len(_name)):
        if _name[i].isdigit():
            return _name[:i-1] + '\n'
    return _name

duplicates = 0


with open("planet_names_nodup.txt", 'w', encoding='utf-8') as newf:
    with open("planet_names.txt", 'r', encoding='utf-8') as f:
        DONE = False
        while not DONE:
            line = f.readline()
            if not line:
                DONE = True
                continue
            name = remove_num(line)
            if name in namedict:
                duplicates += 1
            else:
                namedict[name] = 1
                newf.write(name)

print("Removed duplicates:", duplicates)
