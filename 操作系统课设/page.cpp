#include <stdio.h>
#include <stdlib.h>

#define nlen 4 // �ڴ����

int *strs;       // ��̬�������ڴ��ָ���ַ
int *pages;      // ��̬�������ڴ��ָ��ҳ
int count;       // ȱҳ����
int time[nlen];  // ��¼�����ڴ�ʱ��
int flags[nlen]; // Clock�㷨����λ

// ����һ������ѭ���б�����ʾ�ڴ��
typedef struct Block {
  int block_num; // ���
  int page_num;  // װ���ڴ����ҵҳ��
  struct Block *next;
} Block, *BlockList;

BlockList blocks[nlen];
BlockList b_clock;

void init(int len);                        // ��ʼ��
void option(int len);                      // ѡ��ʹ�������㷨
void exchange(int str, int page, int num); // �û�ҳ��
int empty_or_in(int str, int page,
                int str_num); // ����ڴ��Ϊ�ջ�ָ�������ڴ���
void OPT(int str, int page, int str_num, int len); // ����û��㷨
void FIFO(int str, int page, int str_num);         // �Ƚ��ȳ��û��㷨
void LRU(int str, int page, int str_num);   // ������δ���û��㷨
void Clock(int str, int page, int str_num); // ʱ���㷨

int main() {
  int flag1 = 1; // �����������Ƿ����
  int len;

  while (flag1) {
    printf("������ָ���ַ���ĳ��ȣ�\n");
    scanf("%d", &len);

    strs = (int *)malloc(len * sizeof(int));
    pages = (int *)malloc(len * sizeof(int));

    init(len);
    option(len);

    printf("�Ƿ������(1��������0������)\n");
    scanf("%d", &flag1);

    free(strs);
    free(pages);
  }
  return 0;
}

void init(int len) {
  int i;

  count = 0;

  // ��ʼ���ڴ��
  for (i = 0; i < nlen; i++) {
    blocks[i] = (BlockList)malloc(sizeof(Block));
    blocks[i]->page_num = -1;
    blocks[i]->block_num = i + 1;
    flags[i] = 0;
  }
  for (i = 0; i < nlen; i++)
    blocks[i]->next = blocks[(i + 1) % nlen];

  b_clock = blocks[0];

  // ����ָ������
  printf("������ָ���ַ����\n");
  for (i = 0; i < len; i++) {
    scanf("%d", &strs[i]);
    pages[i] = strs[i] / 10;
  }
}

void option(int len) {
  int i, choice, flag0 = 1;

  printf("��ѡ���û��㷨��1_OPT  |  2_FIFO  |  3_LRU  |  4_Clock\n");
  while (flag0) {
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      for (i = 0; i < len; i++)
        OPT(strs[i], pages[i], i + 1, len);
      flag0 = 0;
      printf("------OPT-------\n");
      break;
    case 2:
      for (i = 0; i < len; i++)
        FIFO(strs[i], pages[i], i + 1);
      flag0 = 0;
      printf("------FIFO-------\n");
      break;
    case 3:
      for (i = 0; i < len; i++)
        LRU(strs[i], pages[i], i + 1);
      flag0 = 0;
      printf("------LRU-------\n");
      break;
    case 4:
      for (i = 0; i < len; i++)
        Clock(strs[i], pages[i], i + 1);
      flag0 = 0;
      printf("------Clock-------\n");
      break;
    default:
      printf("û�д�ѡ�������ѡ��\n");
      break;
    }
  }
  printf("ȱҳ��%f\n", (double)count / len);
}

int empty_or_in(int str, int page, int str_num) {
  // ����1��ʾָ����װ���ڴ�
  BlockList b = blocks[0];
  int i;

  for (i = 0; i < nlen; i++) {
    if (b->page_num == -1) { // ��Ϊ��
      b->page_num = page;
      time[b->block_num - 1] = str_num;
      flags[b->block_num - 1] = 1;
      count++;
      printf("ָ��δװ���ڴ棡ҳ���û����\n");
      printf("�û�ָ���%dҳ��%d���������ַΪ����%d���%d��\n\n", page,
             str % 10 + 1, b->block_num, str % 10 + 1);
      return 1;
    }
    if (b->page_num == page) { // ָ�����ڴ���
      printf("ָ�������ڴ��У�\n");
      printf("�û�ָ���%dҳ��%d���������ַΪ����%d���%d��\n\n", page,
             str % 10 + 1, b->block_num, str % 10 + 1);
      flags[b->block_num - 1] = 1;
      return 1;
    }

    b = b->next;
  }
  return 0;
}

void exchange(int str, int page, int num) {
  BlockList b = blocks[0];
  int i;
  for (i = 0; i < num; i++)
    b = b->next;
  b->page_num = page;
  count++;
  printf("ָ��δװ���ڴ����ڴ��������    ҳ���û���ɣ�\n");
  printf("�û�ָ���%dҳ��%d���������ַΪ����%d���%d��\n\n", page,
         str % 10 + 1, b->block_num, str % 10 + 1);
}

void OPT(int str, int page, int str_num, int len) {
  BlockList b = blocks[0];
  int i, j, next[nlen], max = 0; // next��ʾ�뵱ǰ�����ҳ��ַ

  printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
  if (empty_or_in(str, page, str_num))
    return;

  // OPT
  for (i = 0; i < nlen; i++) {
    for (j = str_num; j < len; j++) {
      if (b->page_num == pages[j]) {
        next[i] = j;
        break;
      }
    }
    b = b->next;
    if (j == len) // ��ǰҳ����ʹ��
      next[i] = j;

    if (next[max] < next[i]) // ѡ����Ҫ���û������ڴ�ҳ
      max = i;
  }

  exchange(str, page, max);
}

void FIFO(int str, int page, int str_num) {
  BlockList b = blocks[0];
  int i, earliest = 0;

  printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
  if (empty_or_in(str, page, str_num))
    return;

  // FIFO
  for (i = 0; i < nlen; i++) {
    if (time[earliest] > time[i])
      earliest = i;
  }

  exchange(str, page, earliest + 1);
  time[b->block_num - 1] = str_num;
}

void LRU(int str, int page, int str_num) {
  BlockList b = blocks[0];
  int i, j, prior[nlen], min = 0;

  printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
  if (empty_or_in(str, page, str_num))
    return;

  // LRU
  for (i = 0; i < nlen; i++) {
    for (j = str_num - 2; j >= 0; j--) {
      if (b->page_num == pages[j]) {
        prior[i] = j;
        break;
      }
    }
    b = b->next;
    if (prior[min] > prior[i])
      min = i;
  }

  exchange(str, page, min);
}

void Clock(int str, int page, int str_num) {
  int i, index, temp = -1; // temp������Ҫ�û���ҳ��

  printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
  if (empty_or_in(str, page, str_num))
    return;

  // Clock
  while (temp == -1) {
    for (i = 0; i < nlen; i++) {
      index = b_clock->block_num - 1;
      if (flags[index] == 0) {
        temp = index;
        break;
      }
      flags[index] = 0;
      b_clock = b_clock->next;
    }
  }
  exchange(str, page, temp);
  flags[b_clock->block_num - 1] = 1;
  b_clock = b_clock->next;
}
