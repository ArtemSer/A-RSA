
//Алгоритм Евклида. Алгоритм для нахождения наибольшего
//общего делителя двух целых чисел. Используется для проверки
//чисел на взаимопростоту.

/* int gcd(int a, int b) {
    int c;
    while (b) {
        c = a % b;       <--- Алгоритм ужасно медленный
        a = b;
        b = c;
    }
    return abs(a);
}*/
// предлагаю свою реализацию битового итерационного алгоритма Эвклида со смещением
int gcd(int a, int b){
    int nod = 1;
    int tmp;
    if (a==0) return b;
    if (b==0) return a;
    if (a==b) return a;
    if (a==1 || b==1) return 1;
        while (a!=0 && b!=0){
            if(((a & 1)|(b & 1)) == 0){
                                             nod <<=1;
                                             a>>=1;
                                             b>>=1;
                                             continue;
                                      }
             if(((a & 1)== 0) && (b & 1)){
                                             a>>=1;
                                             continue;
                                         } 
             if(((a & 1) && (b & 1)) == 0){
                                             b>>=1;
                                             continue;
                                           }
             if(a>b){
                        tmp =a;
                        a=b;
                        b=tmp;
                    }
             tmp=a;
             a=(b-a)>>1;
             b=tmp;
                           }
    if(a==0) return nod*b;
    else return nod*a;
}
