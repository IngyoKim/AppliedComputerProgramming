//삽입정렬 & 이진탐색

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void importData();
void sortData();
void printData();
char findPhone(char *name);

struct data 
{
	char name[100];
	long long int phone;
};

typedef struct node
{
	struct data nodedata;
	struct node *next;
}node;

node *head = NULL;
struct data userdata[100];
struct data temp;
int count = 0;

int main()
{
	char nameForFinding[100];
	importData();
	printf("Input\n\n");
	printData();
	sortData();
	printf("\nAfter Sorting\n\n");
	printData();
	printf("\nEnter the name you want to find : ");
	scanf_s("%s", nameForFinding, 100);
	findPhone(nameForFinding);
}

void importData()
{
	FILE* inFile = fopen("data.txt", "r");

	while (fscanf_s(inFile, "%s %lld", userdata[count].name, 100, &userdata[count].phone) == 2)
	{
		count++;
	}
}

void sortData()
{
	for (int i = 0; i < count; i++)
	{
		node* newnode = (node*)malloc(sizeof(node));
		strcpy_s(newnode->nodedata.name, 100, userdata[i].name);
		newnode->nodedata.phone = userdata[i].phone;
		newnode->next = NULL;

		if (head == NULL || strcmp(head->nodedata.name, newnode->nodedata.name) > 0)
		{
			newnode->next = head;
			head = newnode;
		}
		else
		{
			node* cur = head;
			while (cur->next != NULL)
			{
				if (strcmp(newnode->nodedata.name, cur->next->nodedata.name) > 0)
				{
					cur = cur->next;
				}
				else
				{
					break;
				}
			}
			newnode->next = cur->next;
			cur->next = newnode;
		}
	}
	node* cur = head;
	count = 0;
	while (cur->next != NULL)
	{
		strcpy_s(userdata[count].name, 100, cur->nodedata.name);
		userdata[count++].phone = cur->nodedata.phone;
		cur = cur->next;
	}
}

void printData()
{

	for (int i = 0; i < count; i++)
	{
		printf("Name : %s, Phone : 0%lld\n", userdata[i].name, userdata[i].phone);
	}
}

char findPhone(char* name)
{
	int start = 1, end = count + 1, now = (end - start + 1) / 2;
	while (strcmp(name, userdata[now].name) != 0)
	{
		int half;
		if (strcmp(name, userdata[now].name) > 0)
		{
			start = now + 1;
			half = (end - start) / 2;
			now = (now + 1) + half;
		}
		else
		{
			end = now - 1;
			half = (end - start) / 2;
			now = (now - 1) - half;
		}
	}
	printf("Name : %s, Phone : 0%lld", userdata[now].name, userdata[now].phone);
}
*/

//삽입정렬 & 해싱 (영어만) -> 한국어인 경우 한국어 한개의 (int)형 값이 -로 나오기 때문에 배열에 넣기 힘듦 

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void importData();
void sortData();
long long int hashData(char *inputName);
void printData();
char findPhone(char* name);

struct data
{
	char name[100];
	long long int phone, hasingKey;
};

typedef struct node
{
	struct data nodedata;
	struct node* next;
}node;

node* head = NULL;
struct data userdata[100];
struct data temp;
int count = 0;
long long int arr[100000000];

int main()
{
	char nameForFinding[100];
	importData();
	for (int i = 0; i < count; i++)
	{
		userdata[i].hasingKey = hashData(userdata[i].name);
		arr[userdata[i].hasingKey] = userdata[i].phone;
	}
	printf("Input\n\n");
	printData();
	sortData();
	printf("\nAfter Sorting\n\n");
	printData();
	printf("\nEnter the name you want to find : ");
	scanf_s("%s", nameForFinding, 100);
	findPhone(nameForFinding);
}

void importData()
{
	FILE* inFile = fopen("data.txt", "r");

	while (fscanf_s(inFile, "%s %lld", userdata[count].name, 100, &userdata[count].phone) == 2)
	{
		count++;
	}
}

long long int hashData(char *inputName)
{
	long long int value = 0;
	for (int j = 0; j < strlen(inputName); j++)
	{
		if (j == 0)
		{
			value += (long long int)inputName[j] * 7 + (long long int)inputName[j + 1] * 3;
		}
		else if (j == strlen(inputName) - 1)
		{
			value += (long long int)inputName[j] * 2 + (long long int)inputName[j - 1] * 4;
		}
		else
		{
			value += (long long int)inputName[j] * 8 + (long long int)inputName[j - 1] * 5 + (long long int)inputName[j + 1] * 6;
		}
	}
	return value;
}

void sortData()
{
	for (int i = 0; i < count; i++)
	{
		node* newnode = (node*)malloc(sizeof(node));
		strcpy_s(newnode->nodedata.name, 100, userdata[i].name);
		newnode->nodedata.phone = userdata[i].phone;
		newnode->nodedata.hasingKey = userdata[i].hasingKey;
		newnode->next = NULL;

		if (head == NULL || strcmp(head->nodedata.name, newnode->nodedata.name) > 0)
		{
			newnode->next = head;
			head = newnode;
		}
		else
		{
			node* cur = head;
			while (cur->next != NULL)
			{
				if (strcmp(newnode->nodedata.name, cur->next->nodedata.name) > 0)
				{
					cur = cur->next;
				}
				else
				{
					break;
				}
			}
			newnode->next = cur->next;
			cur->next = newnode;
		}
	}
	node* cur = head;
	count = 0;
	while (cur->next != NULL)
	{
		strcpy_s(userdata[count].name, 100, cur->nodedata.name);
		userdata[count].phone = cur->nodedata.phone;
		userdata[count++].hasingKey = cur->nodedata.hasingKey;
		cur = cur->next;
	}
}

void printData()
{

	for (int i = 0; i < count; i++)
	{
		printf("Name : %s, Phone : 0%lld HasingKey : %lld\n", userdata[i].name, userdata[i].phone, userdata[i].hasingKey);
	}
}

char findPhone(char* name)
{
	long long int value = 0;
	value = hashData(name);

	if (arr[value] == NULL)
	{
		printf("Name not entered.");
	}
	else
	{
		printf("Name : %s, Phone : 0%lld", name, arr[value]);
	}
}
*/

//삽입정렬 & 해싱 (영어 & 한글) -> 유니코드를 통한 계산 (wchar_t 자료형 사용)

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>
#include <math.h>

void importData();
void sortData();
long long int hashData(wchar_t *nameValue);
void printData();
char findPhone(wchar_t* name);

struct data
{
	char name_c[100];
	wchar_t name_w[100];
	long long int phone, hasingKey;
};

typedef struct node
{
	struct data nodedata;
	struct node* next;
}node;

node* head = NULL;
struct data userdata[100];
struct data temp;
int count = 0;
int i = 0;
int k = 0;
long long int arr[100000000];

int main()
{
	setlocale(LC_ALL, "");

	wchar_t nameForFinding[100]; 
	importData();
	for (int i = 0; i < count; i++)
	{
		userdata[i].hasingKey = hashData(userdata[i].name_w);
		arr[userdata[i].hasingKey] = userdata[i].phone;
	}
	printf("Input\n\n");
	printData();
	sortData();
	printf("\nAfter Sorting\n\n");
	printData();
	printf("\nEnter the name you want to find : ");
	wscanf_s(L"%s", nameForFinding, 100);
	findPhone(nameForFinding);
}

void importData()
{
	FILE* inFile = _wfopen(L"data.txt", L"r, ccs=UTF-8");

	while (fwscanf_s(inFile, L"%ls %lld", userdata[count].name_w, 100, &userdata[count].phone) == 2)
	{
		WideCharToMultiByte(CP_ACP, 0, userdata[count].name_w, -1, userdata[count].name_c, sizeof(userdata[count].name_c), NULL, NULL);
		count++;
	}
}

long long int hashData(wchar_t *inputName) 
{
	long long int value = 0;
	for (int j = 0; j < wcslen(inputName); j++)
	{
		if (j == 0)
		{
			value += (long long int)inputName[j] * 3 - (long long int)inputName[j + 1] * 7;
		}
		else if (j == wcslen(inputName) - 1)
		{
			value += (long long int)inputName[j] * 2 + (long long int)inputName[j - 1] * 4;
		}
		else
		{
			value += (long long int)inputName[j] * 8 + (long long int)inputName[j - 1] * 5 + (long long int)inputName[j + 1] * 6;
		}
	}
	return value;
}

void sortData()
{
	for (int i = 0; i < count; i++)
	{
		node* newnode = (node*)malloc(sizeof(node));
		strcpy_s(newnode->nodedata.name_c, 100, userdata[i].name_c);
		wcscpy_s(newnode->nodedata.name_w, 100, userdata[i].name_w);
		newnode->nodedata.phone = userdata[i].phone;
		newnode->nodedata.hasingKey = userdata[i].hasingKey;
		newnode->next = NULL;

		if (head == NULL || strcmp(head->nodedata.name_c, newnode->nodedata.name_c) > 0)
		{
			newnode->next = head;
			head = newnode;
		}
		else
		{
			node* cur = head;
			while (cur->next != NULL)
			{
				if (strcmp(newnode->nodedata.name_c, cur->next->nodedata.name_c) > 0)
				{
					cur = cur->next;
				}
				else
				{
					break;
				}
			}
			newnode->next = cur->next;
			cur->next = newnode;
		}
	}
	node* cur = head;
	count = 0;
	while (cur->next != NULL)
	{
		strcpy_s(userdata[count].name_c, 100, cur->nodedata.name_c);
		wcscpy_s(userdata[count].name_w, 100, cur->nodedata.name_w);
		userdata[count].phone = cur->nodedata.phone;
		userdata[count++].hasingKey = cur->nodedata.hasingKey;
		cur = cur->next;
	}
}

void printData()
{

	for (int i = 0; i < count; i++)
	{
		printf("Name(char) : %s, ", userdata[i].name_c);
		wprintf(L"Name(wchar_t) : %ls, ", userdata[i].name_w);
		printf("Phone : 0%lld, ", userdata[i].phone);
		printf("HasingKey : %lld\n", userdata[i].hasingKey);
	}
}

char findPhone(wchar_t* name)
{
	long long int value = 0;
	value = hashData(name);
	
	if (arr[value] == NULL)
	{
		printf("Name not entered.");
	}
	else
	{
		wprintf(L"Name : %ls, Phone : 0%lld", name, arr[value]);
	}
}
*/
