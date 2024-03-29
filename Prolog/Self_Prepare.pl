isList([]).
isList([_|_]).

append1([], L2, L2).
append1([H|T1], L2, [H|R]):- append1(T1, L2, R).

% 1. member 2x ways to say it with recursion or with append
member1(X, [X|_]).
member1(X, [_|T]):- member1(X, T).

member2(X,L):- append1(_, [X|_], L).


% 2. length of list with recursion and is_list
length1([], 0).
length1([_|T], L):-length1(T, M), L is M + 1.

% 3. take first element of list and last element of list
first(X, [X|_]).
last(X, L):- append1(_, [X], L).

% 4. reverse list
reverse1(L, RL):- rev(L, [], RL).
rev([], Stack, Stack).
rev([H|T], Stack, R):- rev(T, [H|Stack], R).

% is_palindrome(L) :- L is a palindrome list
is_palindrome(L):-reverse1(L, L).

% 5. insert element in list randomly in it
insert(X, L, RL):- append1(A, B, L), append1(A, [X|B], RL).
insert1(X, L, RL):- remove1(X, RL, L).

% 6. remove an element from a list
remove(X, L, RL):- append1(A, [X|B], L), append1(A, B, RL).
remove1(X, L, RL):- insert1(X, RL, L).

% 7. permutation of a list
permutation([], []).
permutation([H|T], P):- permutation(T, Q), insert(H, Q, P).

% 8. is_sorted and simplest sort
is_sorted(L):- not((append(_, [A,B|_], L), A > B)).
simplestSort(L, SL):- permutation(L, SL), is_sorted(SL).


sum([], 0).
sum([H|T], S):- sum(T, M), S is H + M.

min1(L, X):- member(X, L), \+ ((member(Y, L), X \= Y, Y < X)).
max1(L, X):- member(X, L), \+ ((member(Y, L), X \= Y, Y > X)).


%second way
lesser(A, B, A):- A < B.

min2(X, [X]).
min2(X, [H|T]):- min2(M, T), lesser(H, M, X).

max2(X, [X]).
max2(X, [H|T]):- max2(M, T), \+ lesser(H, M, X).

% 3.Div
div(_, Y):- Y =:= 0.
div(X, Y):- Y >= X, div(X, Y - X).



% Quick Sort
partition(_, [], [], []).
partition(Pivot, [H|T], [H|L], R):- Pivot >= H, partition(Pivot, T, L, R).
partition(Pivot, [H|T], L, [H|R]):-  Pivot < H, partition(Pivot, T, L, R).

quickSort([], []).
quickSort([H|T], R):- partition(H, T, PL, PR), quickSort(PL, SL), quickSort(PR, SR), append1(SL, [H|SR], R).

% Prefix and Sufix of List
prefix(P, L):- append1(P, _, L).
sufix(S, L):- append1(_, S, L).

% sublist of a list
sublist(R, L):- append1(_, S, L), append1(R, _, S).

% subset of a list
subset([],[]).
subset([_|T], R):- subset(T, R).
subset([H|T], [H|R]):- subset(T, R).

% n_th element - generates the position where element X is at or gives the element at position N

n_th_element(X, 1, [X|_]).
n_th_element(X, N, [_|T]):- n_th_element(X, M, T), N is M + 1.


% union, intersection, difference, subset, equal
in_union(X, A, B):- member2(X, A); member2(X, B).
in_intersection(X, A, B):- member2(X, A), member2(X, B).
in_difference(X, A, B):- member2(X, A), not((member2(X, B))).
in_subset_of(A, B):- not((member2(X, A), not(member2(X, B)))).
are_equal(A, B):- is_subset_of(A, B), is_subset_of(B, A).

% 8./*
% 6.IV.2013 г.
% Задача 1. Да се дефинира на пролог предикат p(L), който
% по даден списък от различни списъци L проверява дали
% всеки два различни елемента на L имат общ елемент, който
% не принадлежи на някой елемент на L.*/

p(L):- not(( member1(A, L), member1(B, L), A \= B, not(( in_intersection(X, A, B), member1(C, L), C \= A, C \= B, not(( member2(X, C))))))).

% 9.
% /*
% 6.IV.2013 г.
% Задача 2. Казваме, че списък X мажорира списък Y , ако
% всички елементи на X са елементи на Y . Да се дефинира
% на пролог предикат p(L,M), който по даден списък от спи-
% съци L намира списък M, който съдържа всички елементи
% на L и в който никой елемент не се мажорира от елемент,
% намиращ се след него в списъка.*/

q(L, M):- perm(L, M), cond(M).
cond(M):- not(( append(_, [A|T], M), member(B,T), is_subset_of(B, A))).

% Merge Sort
split([], [], []).
split([A], [A], []).
split([A,B|T], [A|L1], [B|L2]):- split(T, L1, L2).

merge1([], S, S).
merge1(F, [], F).
merge1([H1|T1], [H2|T2], [H1|R]):- H1#=<H2, merge1(T1, [H2|T2], R).
merge1([H1|T1], [H2|T2], [H2|R]):- H1#>H2, merge1([H1|T1], T2, R).
:-use_module(library(clpfd)).

merge_sort1([], []).
merge_sort1([A], [A]).
merge_sort1(L, R):- split(L, LR, RR), merge_sort1(LR, R1), merge_sort1(RR, R2), merge1(R1, R2, R).

% substract т.е. A\B = C, където C  е раликата на множеството А без B

substract1(A, [], A).
substract1([], _, []).
substract1([H|T], B, [H|C]):- not((member1(H,B))), substract1(T, B, C).
substract1([H|T], B, C):- member1(H,B), substract1(T, B, C).


% program generatig all numbers Y = k*X where k = 0, 1, 2...

generator1(_, 0).
generator1(X, Y):- generator1(X, Z), Y is X + Z.

% Exponentiation by squaring - бърз алгоритъм за степенуване

even(X):- X mod 2 =:= 0.

pow_fast(_, 0, 1).
pow_fast(X, Y, R):- Y > 0, even(Y), Y1 is Y / 2, pow_fast(X, Y1, Z), R is Z * Z.
pow_fast(X, Y, R):- Y > 0, not((even(Y))), Y1 is Y - 1, pow_fast(X, Y1, Z), R is X * Z.

% Задача 1. Да се дефинира на пролог предикат p(L), който
% по даден списък от различни списъци L проверява дали
% в L съществуват два различни елемента, които имат общ
% елемент, който не принадлежи на никой друг елемент на L.

p1(L, X, Y, EL):- member2(X, L), member2(Y, L), X \= Y, in_intersection(EL, X, Y), not((member2(Z, L), Z \= X, Z= Y, member2(EL, Z))).

% Зад. 2. Да се дефинира предикат p(X,Y ), който по даден
% списък X генерира в Y всички списъци, чиито елементи са
% елементи на X и броят на срещанията на най-често среща-
% ния елемент в Y е число, което не е елемент на X.

count(_, [], 0).
count(X, [X|T], R):- count(X, T, R1), R is R1 + 1.
count(X, [A|T], R):- A \= X, count(X, T, R).

count_max(X, L, N):- member2(X, L), count(X, L, N), not((member2(Y, L), count(Y, L, N1), N1 > N)).

p2(X, Y):- member2(X1, X), permutation(X1, Y), count_max(_, Y, N), not((member2(N, X))).



% Graphs

addV(V, VL, VR):- not((member2(V, VL))), append([V], VL, VR).
addV(V, VL, VL):- member2(V, VL).

% Main function

vertices([], []).
vertices([[X, Y]|T], V):- vertices(T, TV), addV(X, TV, TX), addV(Y, TX, V).

% Друг начин:
% - Конкатенираме Е в нов списък L
% - Премахваме повторенията в L

megaConcat([], []).
megaConcat([H|T], R):- megaConcat(T, Q), append(H, Q, R).

toSet([], []).
toSet([H|T], [H|R]):- toSet(T, R), not((member2(H, R))).
toSet([H|T], R):- toSet(T, R), member2(H, R).

vertices2(E, V):- megaCOncat(E, L), toSet(L, V).

% Path in a graph

path(E, X, Y, P):- path1(E, X, [Y], P).

path1(_, X, [X|Rest], [X|Rest]).
path1(E, X, [Y|Rest], P):- member2([Z, Y], E),
    not((member2(Z, [Y|Rest]))),
    path1(E, X, [Z, Y| Rest], P).

% Version with 5 parameters

path2(E, X, Y, P):- path3(E, X, Y, [], P).

path3(_, _, Y, Visited, P):- append2([Y], _, Visited), reverse1(Visited, P).
path3(E, X, Y, Visited, P):- member2([X, Z], E), not((meber2(Z, Visited))), path3(E, Z, Y, [X|Visited], P).

cycle(E, [X|P1]):- member2([X, Y], E), X \= Y, path(E, Y, X, P1).

connected(V, E):- not(( member2(X, V), member2(Y, V), X \=Y, not((path(E, X, Y, _))))).

% DFS

gen_next_vertice(E, Curr, Container, Visited, Next):- member1([Curr, Next], E), not((member1(Next, Container))), not(( member1(Next, Visited))).

dfs(E, Root, Result):- dfs_main(E, [Root], [], Result).

dfs_main(_, [], _, []).
dfs_main(E, [StackH|StackT], Visited, [[StackH, Next]|Result]):- gen_next_vertice(E, StackH, [StackH|StackT], Visited, Next), dfs_main(E, [Next, StackH|StackT], Visited, Result).
dfs_main(E, [StackH|StackT], Visited, Result):- not((gen_next_vertice(E, StackH, [StackH|StackT], Visited, _))), dfs_main(E, StackT, [StackH|Visited], Result).


% BFS

bfs(E, Root, Result):- bfs_main(E, [Root], [], Result).

bfs_main(_, [], _, []).
bfs_main(E, [QueueH|QueueT], Visited, [[QueueH, Next]|Result]):- gen_next_vertice(E, QueueH, [QueueH|QueueT], Visited, Next), append1([QueueH|QueueT], [Next], NewQueue), bfs_main(E, NewQueue, Visited, Result).
bfs_main(E, [QueueH|QueueT], Visited, Result):- not((gen_next_vertice(E, QueueH, [QueueH|QueueT], Visited, _))), dfs_main(E, QueueT, [QueueH|Visited], Result).

% Hamilton Cycle

hamiltonian_path(V, E, P):- permutation(V, P), not((append(_, [A, B|_], P), not((member1([A, B], E))))).


hamiltonian_cycle(V, E, C):- hamiltonian_path(V, E, [H|T]), append(_, [Y], T), member([Y, H], E), append([H|T], [H], C).

%  1. Реализирайте алгоритъм stree(V, E, ST), генериращ в ST покриващото
%  дърво на графа G(V, E)

stree(V, E, ST):- V = [H|T], st(V, E, [H], T , ST).

st(_, _, _, [], []).
st(V, E, Visited, NotYetVisited, [[U,W]|Result]):-
    member1([U, W], E), member1(U, Visited), not((member1(W, Visited))), remove(W, NotYetVisited, NewNotYetVisited), st(V, E, [W|Visited], NewNotYetVisited, Result).


% Зад. 1. Нека G е неориентиран граф. Множеството от вър-
%	ховете на G е представено със списък V от
%        върховте, всяко ребро v е представено с
%        двуелементен списък на краища-та му, а
%        множеството от ребрата на G е представено със
%        списък E от ребрата. Да се дефинира на Пролог
%        предикат
%	а) con(V, E), който разпознава дали
%        представеният с V и E граф е свързан.
%	б) crit(V, E, X), който по дадени V и E на
%        свързан граф генерира в X списък на всички
%        върхове, чието отстраняване води до граф, който
%       не е свързан. (3 + 3 точки)

con(V, E):- not((member1(X, V), member(Y, V), X \= Y,
    not((path(E, X, Y, _))), not((path(E, Y, X, _))))).

critical(V, E, X):- append(A, [X|B], V),
    append(A, B, NV), member(U, NV), member(W, NV),
    not((path(E, U, W, _))).

crity(_, _, [], []).
crity(V, E, [CurrentV|T], [CurrentV|Result]):-
    critical(V, E, CurrentV), crity(V, E, T, Result).
crity(V, E, [CurrentV|T], Result):-
    not((critical(V, E, CurrentV))), crity(V, E, T, Result).

crit(V, E, X):- crit(V, E, V, X).

validMove([X, Y], Forbidden, [NX, NY]):- member([A, B], [[-2, -1], [-2, 1], [-1, 2], [1, 2], [2, 1], [2, -1], [1, -2], [-1, -2]]),
    NX is X + A,
    NY is Y + B,
    NX > 0,
    NY > 0,
    NX < 9,
    NY < 9,
    not(member([NX, NY], Forbidden)).


knightPath(_, _, _, []).
knightPath(CurrPos, EndPoint, Forbidden, [CurrPos|Result]):- CurrPos \= EndPoint,
    validMove(CurrPos, Forbidden, NextPos),
    knightPath(NextPos, EndPoint, [CurrPos|Forbidden], Result).
