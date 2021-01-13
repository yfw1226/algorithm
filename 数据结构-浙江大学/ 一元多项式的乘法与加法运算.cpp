#include <iostream>
#include <stdio.h>

typedef struct Node *PtrToNode;

struct Node{
    int coef;
    int exp;
    PtrToNode Next;
};

typedef PtrToNode List;

List Read();
void Print(List L);
List Add(List L1, List L2);
List Multiply(List L1, List L2);
void Attach(int coef, int exp, List *pRear);

int main() {
    List L1, L2, L_add, L_mul;
    L1 = Read();
    L2 = Read();
    L_mul = Multiply(L1, L2);
    Print(L_mul);
    L_add = Add(L1, L2);
    Print(L_add);
    return 0;
}

//在表尾申请空间，构建新节点，并重定向表尾指针
void Attach(int coef, int exp, List *pRear){
    List L;
    L = (List)malloc(sizeof(struct Node));
    L->coef = coef;
    L->exp = exp;
    L->Next = NULL;
    (*pRear)->Next = L;
    *pRear = L;
}

List Read(){
    List L, Rear, tmp;
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    Rear = L;

    int coef, exp, N;
    scanf("%d", &N);
    while(N--){
        scanf("%d %d", &coef, &exp);
        Attach(coef, exp, &Rear);
    }

    tmp = L; L=L->Next; free(tmp);
    return L;

}

void Print(List L){
    int flag = 0;
    if (!L){printf("0 0\n"); return;}
    while (L){
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d", L->coef, L->exp);
        L = L->Next;
    }
    printf("\n");
}

List Add(List L1, List L2){
    List L, t, Rear, t1, t2;
    if (!L1 && !L2) return NULL;

    t1 = L1;
    t2 = L2;
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    Rear = L;

    while(t1 && t2){
        if(t1->exp < t2->exp){
            Rear->Next = t2;
            t2 = t2->Next;
            Rear = Rear->Next;
        }else if(t1->exp > t2->exp){
            Rear->Next = t1;
            t1 = t1->Next;
            Rear = Rear->Next;
        }else{
            t2->coef += t1->coef;
            if(t2->coef != 0){
                Rear->Next = t2;
                t2 = t2->Next;
                Rear = Rear->Next;
            }else{
                t = t2;
                t2 = t2->Next;
                free(t);
            }
            t = t1;
            t1 = t1->Next;
            free(t);
        }

    }

    //todo 为什么不能写成 if (t1){Rear->Next = t1;} ???
    
    if (t1 == NULL){
        Rear->Next = t2;
    }else if(t2 == NULL){
        Rear->Next = t1;
    }

    t = L; L = L->Next; free(t);

    return L;
}

List Multiply(List L1, List L2){
    List L, Rear, t, t1, t2;
    int coef, exp;

    if (!L1 || !L2) return NULL;

    t1 = L1; t2 = L2;
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    Rear = L;

    //先用L1的第一项乘L2，构造初始L
    while (t2){
        coef = t1->coef * t2->coef;
        exp = t1->exp + t2->exp;
        Attach(coef, exp, &Rear);

        t2 = t2->Next;
    }
    t1 = t1->Next;
    while (t1){
        t2 = L2; Rear = L;
        while (t2){
            coef = t1->coef * t2->coef;
            exp = t1->exp + t2->exp;

            while (Rear->Next && Rear->Next->exp > exp)
                Rear = Rear->Next;
            if (Rear->Next && Rear->Next->exp == exp){
                if (Rear->Next->coef + coef)
                    Rear->Next->coef += coef;
                else{
                    t = Rear->Next;
                    Rear->Next = t->Next;
                    free(t);
                }
            }else{
                t = (List)malloc(sizeof(struct Node));
                t->coef = coef; t->exp = exp;
                t->Next = Rear->Next;
                Rear->Next = t;
                Rear = Rear->Next;
            }

            t2 = t2->Next;
        }
        t1 = t1->Next;
    }
    t2 = L; L = L->Next; free(t2);
    return L;
}
