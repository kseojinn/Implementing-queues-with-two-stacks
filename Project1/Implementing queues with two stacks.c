#include <stdio.h>
#include <stdlib.h>
#define MAX 5 // 스택의 최대 크기 정의

// 스택 구조체 정의
typedef struct {
    int data[MAX];   // 데이터를 저장할 배열
    int top;         // 스택의 최상단 인덱스
    const char* name; // 스택의 이름
} Stack;

Stack Stack1, Stack2; // 두 개의 스택 선언 (전역 변수)

// 스택 초기화 함수
void init(Stack* s, const char* stackname) {
    s->top = -1;     // top을 -1로 초기화 (빈 스택 상태)
    s->name = stackname;
}

// 스택이 가득 찼는지 확인하는 함수
int isfull(Stack* s) {
    return s->top == MAX - 1; // top이 MAX-1이면 스택이 가득 찬 상태
}

// 스택이 비어있는지 확인하는 함수
int isempty(Stack* s) {
    return s->top == -1; // top이 -1이면 스택이 비어있는 상태
}

// 스택의 현재 상태를 출력하는 함수
void CheckStack(Stack* s) {
    printf("%s의 상태: ", s->name);
    if (isempty(s)) {
        printf("비어있음\n");
        return;
    }
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

// Stack1에 데이터를 push하는 함수 (큐의 enqueue 역할)
void push(Stack* s) {
    // 스택이 가득 찼는지 확인
    if (isfull(s)) {
        printf("%s는 포화상태.. Pop선택해야함..\n", s->name);
        return;
    }

    int value;
    printf("Stack1에 넣을 값의 개수를 입력..(MAX는 %d)(종료는 0) : ", MAX);
    scanf("%d", &value);

    if (value == 0) return; // 0 입력 시 함수 종료
    else if (0 < value && (s->top + 1) + value <= MAX) { // 유효한 개수 입력 시
        printf("순차적으로 숫자만 입력 후 Enter.. : ");
        for (int i = 0; i < value; i++) {
            int num;
            scanf("%d", &num);
            s->data[++(s->top)] = num; // 데이터 push
        }
        CheckStack(s); // 스택 상태 출력
    }
    else { // 범위 초과 시
        printf("입력할 수 있는 범위를 초과했습니다.\n");
        CheckStack(s);
    }
}

// Stack1의 모든 데이터를 Stack2로 이동하는 함수
void move_stack1_to_stack2() {
    if (isempty(&Stack2) && !isempty(&Stack1)) {
        printf("Stack2가 비어있어 Stack1의 데이터를 Stack2로 이동합니다.\n");
        // Stack1의 요소를 모두 꺼내서 Stack2에 넣음 (순서가 뒤집힘)
        while (!isempty(&Stack1)) {
            Stack2.data[++(Stack2.top)] = Stack1.data[Stack1.top--];
        }
        printf("이동 완료.\n");
        CheckStack(&Stack2);
    }
}

// Stack2에서 데이터를 pop하는 함수 (큐의 dequeue 역할)
void pop(Stack* s) {
    // Stack2가 비어있으면 Stack1의 모든 요소를 Stack2로 이동만 하고 pop은 수행하지 않음
    if (isempty(s)) {
        if (isempty(&Stack1)) {
            printf("큐가 비어있습니다. (두 스택 모두 비어있음)\n");
            return;
        }

        move_stack1_to_stack2(); // Stack1 -> Stack2로 데이터 이동
        printf("Stack1의 데이터를 Stack2로 이동했습니다. 다시 Pop을 선택하면 데이터를 꺼낼 수 있습니다.\n");
        return;
    }

    // Stack2가 이미 데이터를 가지고 있는 경우 pop 수행
    printf("Pop된 값: %d\n", s->data[s->top]);
    s->top--; // pop 연산 수행
    CheckStack(s);
}

int main() {
    // 두 스택 초기화
    init(&Stack1, "Stack1");
    init(&Stack2, "Stack2");

    // 메인 루프
    while (1) {
        int select;
        printf("\n===== 스택 두 개로 큐 구현하기 =====\n");
        printf("[1] Push (Stack1에 데이터 추가)\n");
        printf("[2] Pop (Stack2에서 데이터 추출)\n");
        printf("[3] 종료\n");
        printf("숫자만 입력하세요.>>> ");
        scanf("%d", &select);

        // 메뉴 선택에 따른 동작 수행
        if (select == 1) {
            push(&Stack1); // Stack1에 데이터 추가
        }
        else if (select == 2) {
            pop(&Stack2); // Stack2에서 데이터 추출
        }
        else if (select == 3) {
            printf("프로그램을 종료합니다.\n");
            return 0;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택해주세요.\n");
        }

        // 현재 두 스택의 상태 출력
        printf("\nStack1 상태: ");
        CheckStack(&Stack1);
        printf("Stack2 상태: ");
        CheckStack(&Stack2);
    }
}