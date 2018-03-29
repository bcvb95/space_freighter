from urllib import request
from lxml import html
import re, time

TARGET_URL = "http://www.scifiideas.com/planet-name-generator/"

with open("planet_names.txt", 'w', encoding='utf-8') as f:

    for i in range(1000):
        print("Loop count: ", i)
        HTML_STR = request.urlopen(TARGET_URL).read().decode("utf-8")
        PATTERN = re.compile("<h3>Planet Name Generator</h3>[\d\D\n\r]*Planet Name #[1-3]:</strong> (.*)</p>[\d\D\n\r]*<hr />")
        MATCH = PATTERN.search(HTML_STR)
        F_PATTERN = re.compile("Planet Name #[1-3]:</strong> (.*)</p>")
        ITER = F_PATTERN.findall(MATCH.group())
        for match in ITER:
            print(match)
            f.write(match + "\n")
        time.sleep(2)
