class Node:
    def __init__(self,val):
        self.val = val
        self.next = None

class MyLinkedList:

    def __init__(self):
        self.head = None

    def get(self, index: int) -> int:
        node = self.head
        i = 0
        while node != None:
            if i == index:
                return node.val
            node = node.next
            i+=1
        return -1
        

    def addAtHead(self, val: int) -> None:
        aux = Node(val)
        if self.head == None:
            self.head = aux
        else:
            aux.next = self.head
            self.head = aux
        

    def addAtTail(self, val: int) -> None:
        if self.head == None:
            self.head = Node(val)
        else:
            node = self.head
            while node.next != None:
                node = node.next
            node.next = Node(val)

    def addAtIndex(self, index: int, val: int) -> None:
        if index == 0:
            self.addAtHead(val)
        else:
            node = self.head
            i = 0
            while node != None:
                if i == index-1:
                    newNode = Node(val)
                    newNode.next = node.next
                    node.next = newNode
                    break
                node = node.next
                i+=1
        

    def deleteAtIndex(self, index: int) -> None:
        if index == 0:
            self.head = self.head.next
        else:
            node = self.head
            prevNode = None                 
            i = 0
            while node != None:
                if i == index:
                    prev.next = node.next
                    break
                prev = node
                node = node.next
                i+=1
