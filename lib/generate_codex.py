import random

messages = ['fail', 'hello', 'goodbye', 'acknowledge', 'query', 'read', 'write', 'true', 'false', 'pass']
motions = ['YXY', 'XYZ', 'ZXZ', 'YZY', 'ZXY', 'XZX', 'ZYY', 'YXZ', 'YYX', 'XZZ']
if __name__=='__main__':
    for i in range(10):
        randomIdx = random.randint(0, len(messages)-1)
        randommsg = messages[randomIdx]
        messages.pop(randomIdx)
        print(i, end=' | ')
        print(motions[i], end=' | ')
        print('led'+str(i), end=' | ')
        print(randommsg)

'''
Dan: 
0 | YXY | led0 | write
1 | XYZ | led1 | goodbye
2 | ZXZ | led2 | fail
3 | YZY | led3 | read
4 | ZXY | led4 | hello
5 | XZX | led5 | query
6 | ZYY | led6 | false
7 | YXZ | led7 | true
8 | YYX | led8 | acknowledge
9 | XZZ | led9 | pass

Raushan:
0 | YXY | led0 | goodbye
1 | XYZ | led1 | query
2 | ZXZ | led2 | read
3 | YZY | led3 | acknowledge
4 | ZXY | led4 | hello
5 | XZX | led5 | fail
6 | ZYY | led6 | true
7 | YXZ | led7 | write
8 | YYX | led8 | pass
9 | XZZ | led9 | false

Jerry: 
0 | YXY | led0 | read
1 | XYZ | led1 | query
2 | ZXZ | led2 | write
3 | YZY | led3 | hello
4 | ZXY | led4 | fail
5 | XZX | led5 | false
6 | ZYY | led6 | goodbye
7 | YXZ | led7 | pass
8 | YYX | led8 | true
9 | XZZ | led9 | acknowledge

Giancarlos:
0 | YXY | led0 | fail
1 | XYZ | led1 | pass
2 | ZXZ | led2 | goodbye
3 | YZY | led3 | false
4 | ZXY | led4 | write
5 | XZX | led5 | hello
6 | ZYY | led6 | acknowledge
7 | YXZ | led7 | read
8 | YYX | led8 | true
9 | XZZ | led9 | query

Zach:
0 | YXY | led0 | hello
1 | XYZ | led1 | acknowledge
2 | ZXZ | led2 | true
3 | YZY | led3 | goodbye
4 | ZXY | led4 | read
5 | XZX | led5 | fail
6 | ZYY | led6 | query
7 | YXZ | led7 | false
8 | YYX | led8 | pass
9 | XZZ | led9 | write





'''
