import re

string = 'hoge(huga)&piyo_'
string = re.sub(r'([()&])', r'\\\1', string)
print(string)
