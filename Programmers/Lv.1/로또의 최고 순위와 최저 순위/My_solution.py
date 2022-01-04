def solution(lottos, win_nums):
    zero = 0
    cnt = 0
    
    for i in lottos:
        if i != 0:
            for j in win_nums:
                if i == j:
                    cnt += 1
        else:
            zero += 1
            
    if cnt == 0 and zero == 0:
        answer = [6, 6]
    elif cnt == 0 and zero != 0:
        answer = [7-zero, 6]
    else:
        answer = [7-cnt-zero, 7-cnt]
        
    
    return answer