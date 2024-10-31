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
	printf("입력 받았을 때\n");
	printData();
	sortData();
	printf("\n소팅 후\n\n");
	printData();
	printf("찾고자하는 이름을 입력해주세요 : ");
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
		printf("%s 0%lld\n", userdata[i].name, userdata[i].phone);
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
	printf("%s 0%lld", userdata[now].name, userdata[now].phone);
}
