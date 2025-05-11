#include <assert.h> //�ж�ָ���Ƿ�Ϊ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mess {
  int num;           // ���
  char place[50];    // �˺�λ��
  char describe[50]; // �˺�����
  char name[20];     // �˺�����
  char code[20];     // �˺�����
};
struct Node {
  struct mess data;
  struct Node *next;
};
struct Node *Creathead();                         // �����ͷ
struct Node *Creatnode();                         // ������
int Verification();                               // �ж������Ƿ���ȷ
void Insert(struct Node *head, struct mess data); // ¼������
void Modify();                                    // �޸�����
struct Node *Search(struct Node *head, int n);    // ��������
void Delete(struct Node *head, int n);            // ɾ������
void Print(struct Node *head);                    // ��ӡ����
void Makemenu();                                  // �����˵�
void Keydown();                                   // ����ͻ����������
void Savefile(struct Node *head, const char *fileURL); // д�ļ�
void Readfile(struct Node *head, const char *fileURL); // ���ļ�

struct Node *list = NULL; // ����һ��ȫ�ֱ���
int main() {
  if (Verification() == 0)
    return 0;
  list = Creathead();            // ����ͷ���
  Readfile(list, "message.txt"); // ��������ʱ���ļ�
  while (1) {
    Makemenu();
    Keydown();
    system("pause");
    system("cls"); // ��������
  }
}
void Keydown() {
  int x, n = 0, i;
  struct Node data;
  struct mess data1;
  struct Node *result = NULL;
  struct Node *result1 = NULL;
  char s[20];
  scanf("%d", &x);
  switch (x) {
  case 0:
    printf("�˳��ɹ�!\n");
    system("pause");
    exit(0);
    break;
  case 1:
    printf("���������ݱ��:");
    scanf("%d", &data1.num);
    printf("����������λ��:");
    scanf("%s", data1.place);
    printf("��������������:");
    scanf("%s", data1.describe);
    printf("��������������:");
    scanf("%s", data1.name);
    printf("��������������:");
    scanf("%s", s);
    for (i = 0; i < strlen(s); i++) {
      data1.code[i] = s[i] + 64;
    }
    data1.code[i] = '\0';
    Insert(list, data1);
    printf("¼��ɹ�!\n");
    // ����
    Savefile(list, "message.txt");
    break;
  case 2:
    Print(list);
    break;
  case 3:
    printf("������Ҫɾ�������ݵı��:");
    scanf("%d", &n);
    Delete(list, n);
    // ����
    Savefile(list, "message.txt");
    break;
  case 4:
    printf("������Ҫ��ѯ�����ݵı��:");
    scanf("%d", &n);
    result1 = Search(list, n);
    if (result1 != NULL) {
      printf("���:%d λ��:%s ����:%s ����:%s ����:%s\n", result1->data.num,
             result1->data.place, result1->data.describe, result1->data.name,
             result1->data.code);
    } else
      printf("δ�ҵ�ָ������");
    break;
  case 5:
    printf("��������Ҫ�޸ĵ����ݵı��:");
    scanf("%d", &n);
    result1 = Search(list, n);
    if (result1 != NULL) {
      printf("�������µ����ݱ��:");
      scanf("%d", &result1->data.num);
      printf("�������µ�����λ��:");
      scanf("%s", result1->data.place);
      printf("�������µ���������:");
      scanf("%s", result1->data.describe);
      printf("�������µ���������:");
      scanf("%s", result1->data.name);
      printf("�������µ���������:");
      scanf("%s", s);
      for (i = 0; i < strlen(s); i++) {
        result1->data.code[i] = s[i] + 64;
      }
      result1->data.code[i] = '\0';
    } else
      printf("δ�ҵ�ָ������,�޷��޸�");
    // ����
    Savefile(list, "message.txt");
    break;
  default:
    printf("�������,����������");
    break;
  }
}
void Makemenu() {
  printf("---------��˽����ϵͳ----------\n");
  printf("\t0.�˳�ϵͳ\n");
  printf("\t1.¼����Ϣ\n");
  printf("\t2.�����Ϣ\n");
  printf("\t3.ɾ����Ϣ\n");
  printf("\t4.��ѯ��Ϣ\n");
  printf("\t5.�޸���Ϣ\n");
  printf("-------------------------------\n");
  printf("�������ѡ��0-5:");
}
int Verification() {
  int i;
  char key[50];
  printf("------����������֤------\n����������:");
  scanf("%s", key);
  for (i = 0; i < 3; i++) { // �ж������Ƿ���ȷ,�������λ���
    if (strcmp(key, "114514") == 0) {
      printf("������ȷ!\n");
      return 1;
    } else if (i < 2 && strcmp(key, "114514") != 0) {
      printf("�������,������%d�λ���\n", 2 - i);
    }
    if (i < 2)
      scanf("%s", key);
  }
  if (i == 3) { // ����������˳�
    printf("���ǷǷ��û���");
    return 0;
  }
}
struct Node *Creathead() {
  struct Node *head = (struct Node *)malloc(sizeof(struct Node)); // ������ͷ
  assert(head);
  head->next = NULL;
  return head;
}
struct Node *Creatnode(struct mess data) {
  struct Node *p = (struct Node *)malloc(sizeof(struct Node));
  p->data = data;
  p->next = NULL;
}
void Insert(struct Node *head, struct mess data) {
  struct Node *p = Creatnode(data);
  p->next = head->next;
  head->next = p;
}
void Print(struct Node *head) {
  struct Node *pMove = head->next;
  while (pMove != NULL) {
    printf("���:%d λ��:%s ����:%s ����:%s ����:%s\n", pMove->data.num,
           pMove->data.place, pMove->data.describe, pMove->data.name,
           pMove->data.code);
    pMove = pMove->next;
  }
}
void Delete(struct Node *head, int n) {
  struct Node *ptr = head, *ptr1 = head->next;
  while (ptr1 != NULL && ptr1->data.num != n) {
    ptr = ptr1;
    ptr1 = ptr->next;
  }
  if (ptr1 != NULL) {
    ptr->next = ptr1->next;
    free(ptr1);
    printf("ɾ���ɹ�\n");
  }
}
struct Node *Search(struct Node *head, int n) {
  struct Node *p = head->next;
  while (p->next != NULL && p->data.num != n) {
    p = p->next;
  }
  return p;
}
void Readfile(struct Node *head, const char *fileURL) {
  FILE *fp = fopen(fileURL, "r");
  char s[20];
  int i;
  if (fp == NULL) {
    fp = fopen(fileURL, "w+"); // ���û���ļ��򴴽�
    fclose(fp);
    return;
  }
  struct mess p;
  while (fscanf(fp, "%d\t%s\t%s\t%s\t%s\n", &p.num, p.place, p.describe, p.name,
                p.code) != EOF) { // ��������
    Insert(list, p);
  }
  fclose(fp);
}
void Savefile(struct Node *head, const char *fileURL) {
  FILE *fp = fopen(fileURL, "w");
  int i;
  struct Node *p = head->next;
  while (p != NULL) { // д������
    fprintf(fp, "%d\t%s\t%s\t%s\t%s\n", p->data.num, p->data.place,
            p->data.describe, p->data.name, p->data.code);
    p = p->next;
  }
  fclose(fp);
}
