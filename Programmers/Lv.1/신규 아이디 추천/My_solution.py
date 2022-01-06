def solution(new_id):
    sp = [
            'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
            ,'0','1','2','3','4','5','6','7','8','9'
            ,'-','_','.'
             ]
    nick = new_id.lower()
    nick_l = len(nick)
    for i in range(0, len(nick)):
        nick_t = nick[i:i+1]
        if nick_t not in sp:
            nick = nick.replace(nick_t, " ")
    nick = nick.replace(" ", "")

    for i in range(len(nick), 1, -1):
        nick = nick.replace('.'*i, '.')

    while(1):
        if nick[:1] != '.' and nick[-1:] != '.':
            break
        elif nick[:1] == '.':
            nick = nick[1:]
        elif nick[-1:] == '.':
            nick = nick[:-1]
    if nick == '':
        nick = 'a'

    if len(nick) > 15:
        nick = nick[:-(len(nick)-15)]
        if nick[-1:] == '.':
            nick = nick[:-1]

    while(len(nick) < 3):
        nick += nick[-1:]
    answer = nick
    
    return answer