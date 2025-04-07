#include <stdio.h>
#include <stdlib.h>
#define MAX 5 // ������ �ִ� ũ�� ����

// ���� ����ü ����
typedef struct {
    int data[MAX];   // �����͸� ������ �迭
    int top;         // ������ �ֻ�� �ε���
    const char* name; // ������ �̸�
} Stack;

Stack Stack1, Stack2; // �� ���� ���� ���� (���� ����)

// ���� �ʱ�ȭ �Լ�
void init(Stack* s, const char* stackname) {
    s->top = -1;     // top�� -1�� �ʱ�ȭ (�� ���� ����)
    s->name = stackname;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int isfull(Stack* s) {
    return s->top == MAX - 1; // top�� MAX-1�̸� ������ ���� �� ����
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isempty(Stack* s) {
    return s->top == -1; // top�� -1�̸� ������ ����ִ� ����
}

// ������ ���� ���¸� ����ϴ� �Լ�
void CheckStack(Stack* s) {
    printf("%s�� ����: ", s->name);
    if (isempty(s)) {
        printf("�������\n");
        return;
    }
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

// Stack1�� �����͸� push�ϴ� �Լ� (ť�� enqueue ����)
void push(Stack* s) {
    // ������ ���� á���� Ȯ��
    if (isfull(s)) {
        printf("%s�� ��ȭ����.. Pop�����ؾ���..\n", s->name);
        return;
    }

    int value;
    printf("Stack1�� ���� ���� ������ �Է�..(MAX�� %d)(����� 0) : ", MAX);
    scanf("%d", &value);

    if (value == 0) return; // 0 �Է� �� �Լ� ����
    else if (0 < value && (s->top + 1) + value <= MAX) { // ��ȿ�� ���� �Է� ��
        printf("���������� ���ڸ� �Է� �� Enter.. : ");
        for (int i = 0; i < value; i++) {
            int num;
            scanf("%d", &num);
            s->data[++(s->top)] = num; // ������ push
        }
        CheckStack(s); // ���� ���� ���
    }
    else { // ���� �ʰ� ��
        printf("�Է��� �� �ִ� ������ �ʰ��߽��ϴ�.\n");
        CheckStack(s);
    }
}

// Stack1�� ��� �����͸� Stack2�� �̵��ϴ� �Լ�
void move_stack1_to_stack2() {
    if (isempty(&Stack2) && !isempty(&Stack1)) {
        printf("Stack2�� ����־� Stack1�� �����͸� Stack2�� �̵��մϴ�.\n");
        // Stack1�� ��Ҹ� ��� ������ Stack2�� ���� (������ ������)
        while (!isempty(&Stack1)) {
            Stack2.data[++(Stack2.top)] = Stack1.data[Stack1.top--];
        }
        printf("�̵� �Ϸ�.\n");
        CheckStack(&Stack2);
    }
}

// Stack2���� �����͸� pop�ϴ� �Լ� (ť�� dequeue ����)
void pop(Stack* s) {
    // Stack2�� ��������� Stack1�� ��� ��Ҹ� Stack2�� �̵��� �ϰ� pop�� �������� ����
    if (isempty(s)) {
        if (isempty(&Stack1)) {
            printf("ť�� ����ֽ��ϴ�. (�� ���� ��� �������)\n");
            return;
        }

        move_stack1_to_stack2(); // Stack1 -> Stack2�� ������ �̵�
        printf("Stack1�� �����͸� Stack2�� �̵��߽��ϴ�. �ٽ� Pop�� �����ϸ� �����͸� ���� �� �ֽ��ϴ�.\n");
        return;
    }

    // Stack2�� �̹� �����͸� ������ �ִ� ��� pop ����
    printf("Pop�� ��: %d\n", s->data[s->top]);
    s->top--; // pop ���� ����
    CheckStack(s);
}

int main() {
    // �� ���� �ʱ�ȭ
    init(&Stack1, "Stack1");
    init(&Stack2, "Stack2");

    // ���� ����
    while (1) {
        int select;
        printf("\n===== ���� �� ���� ť �����ϱ� =====\n");
        printf("[1] Push (Stack1�� ������ �߰�)\n");
        printf("[2] Pop (Stack2���� ������ ����)\n");
        printf("[3] ����\n");
        printf("���ڸ� �Է��ϼ���.>>> ");
        scanf("%d", &select);

        // �޴� ���ÿ� ���� ���� ����
        if (select == 1) {
            push(&Stack1); // Stack1�� ������ �߰�
        }
        else if (select == 2) {
            pop(&Stack2); // Stack2���� ������ ����
        }
        else if (select == 3) {
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
        }

        // ���� �� ������ ���� ���
        printf("\nStack1 ����: ");
        CheckStack(&Stack1);
        printf("Stack2 ����: ");
        CheckStack(&Stack2);
    }
}