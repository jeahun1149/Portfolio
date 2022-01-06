def solution(numbers, hand):
    L_num = [1,4,7,10]
    R_num = [3,6,9,12]
    M_num = [2,5,8,0]
    L_list = [1,3,0]
    R_list = [1,3,0]
    H = hand[0:1].upper()
    answer = ''
    for i in numbers:
        if i in L_num:
            L_list[0] = 1
            L_list[1] = L_num.index(i)
            answer += 'L'
        elif i in R_num:
            R_list[0] = 1
            R_list[1] = R_num.index(i)
            answer += 'R'
        else:
            M_y = M_num.index(i)
            L_list[2] = L_list[0]+abs(L_list[1]-M_y)
            R_list[2] = R_list[0]+abs(R_list[1]-M_y)
            if L_list[2] < R_list[2]:
                L_list[0] = 0
                L_list[1] = M_y
                answer += 'L'
            elif L_list[2] > R_list[2]:
                R_list[0] = 0
                R_list[1] = M_y
                answer += 'R'
            else:
                answer += H
                if H == 'L':
                    L_list[0] = 0
                    L_list[1] = M_y
                else:
                    R_list[0] = 0
                    R_list[1] = M_y
                    
    return answer