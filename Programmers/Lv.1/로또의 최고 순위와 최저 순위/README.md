# 로또의 최고 순위와 최저 순위
#### 문제 설명
이번 문제는 자신의 로또번호와 당첨된 로또번호를 비교하여 순위를 계산하는 문제이다.
하지만 자신의 로또번호 몇개가 가려져있다 가려진 번호가 당첨이였을때 최고 순위와
아닐때 최저 순위를 구해야한다. 
 
자세한 문제 내용은 밑에 주소에 들어가면 확인 할 수 있다.
https://programmers.co.kr/learn/courses/30/lessons/77484

우선 내가 적은 파이썬 코드이다.
```python
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
```
간단하게 for문과 if문을 사용하여 로또번호 비교와 최고 순위와 최저순위를 구해보았다.
for문과 if문으로도 충분히 가능한 문제였지만 분명 더 간단하게 구현을 했을것이다.

다른 사람들이 만든 코드들 중 베스트 코드를 찾아보았다.

```python
def solution(lottos, win_nums):

    rank=[6,6,5,4,3,2,1]

    cnt_0 = lottos.count(0)
    ans = 0
    for x in win_nums:
        if x in lottos:
            ans += 1
    return rank[cnt_0 + ans],rank[ans]
```
위에 코드가 베스트 코드이다.
보자마자 나는 내가 아직 멀었구나 라는 소리가 입으로 나왔다
그래도 이러한 코드들을 보며 나도 성장할 수 있다고 다짐을 해보며 해석해봤다.

위 코드는 if문과 for문을 최소화 하여 사용했고
lottos.count(0), count 함수로 0의 개수를 확인했다
그리고 win_nums 와 lottos를 비교하여 같은 숫자의 개수를 구하고
그 값에 통해 rank 리스트에서 최고 순위와 최저 순위를 구했다.

충분히 생각할 수 있는 코드다. 다만 나는 바로 생각하지 못했다.

나는 아직 부족한거 같다

그래서 나는 더욱 성장 할 수 있다.