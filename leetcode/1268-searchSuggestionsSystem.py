class Solution:
    def isPrefix(self, product: str, searchWord: str) -> bool:
        i = 0
        for c in product:
            if c != searchWord[i]:
                return false
            i+=1
        return true
    
    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        products.sort()
        result = []
        for i in range(1,len(searchWord)+1):
            searchWordTemp = searchWord[:i]
            sublist = []
            limit = 0
            for p in products:
                if limit < 3 and p.startswith(searchWordTemp):
                    sublist.append(p)
                    limit += 1
            result.append(sublist)
        return result 
