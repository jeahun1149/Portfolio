def solution(s):
    eng = ['zero','one','two','three','four','five','six','seven','eight','nine']

    answer = ''
    c = ''

    for i in range(0, len(s)):
        try:
            if int(s[i:i+1]) >= 0:
                answer += str(s[i:i+1])
        except:
            c += str(s[i:i+1])
            if c in eng:
                dex = eng.index(c)
                answer += str(dex)
                c = ''
                
    return int(answer)