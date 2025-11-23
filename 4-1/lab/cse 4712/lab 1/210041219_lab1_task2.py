from collections import defaultdict

class FrequencyMap:
    def __init__ (self, words):
        self.map = defaultdict(int)
        for word in words:
            self.map[word] += 1
    
    def most_common(self):
        ans = max(self.map, key=self.map.get)
        print(ans)

f = FrequencyMap ([" apple ", " banana ", " apple ", " apple ", " pear "])
f.most_common()