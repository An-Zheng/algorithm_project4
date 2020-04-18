#include <stdio.h>
#include <iostream>
#include "mysql.h"

using namespace std;

#define PORT 3306
	//获取结果集 0 id   1 handsome   2 polite     3 high    4 hardworking    5  marry_him
#define ID 0
#define HANDSOME 1
#define POLITE 2
#define HIGH 3
#define HARDWORKING 4
#define MARRYHIM 5
struct Person
{
	int handsome;
	int polite;
	int high;
	int hardworking;
};
bool marry_him(MYSQL& mysql, Person& person)
{
	MYSQL_RES* res; 
	MYSQL_ROW row;  
	float iMarryHim = 0;
	float iNotMarryHim = 0;

	float iHandsomeAndMarryHim = 0;
	float iPoliteAndMarryHim = 0;
	float iHighAndMarryHim = 0;
	float iHardworkingAndMarryHim = 0;


	float iHandsomeAndNotMarryHim = 0;
	float iPoliteAndNotMarryHim = 0;
	float iHighAndNotMarryHim = 0;
	float iHardworkingAndNotMarryHim = 0;
	


	mysql_query(&mysql, "select * from t_person");

	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		//marryHim
		if (atoi(row[MARRYHIM]) == 1)
		{
			iMarryHim++;
		}
		//notMarryHim
		if (atoi(row[MARRYHIM]) == 0)
		{
			iNotMarryHim++;
		}
		//iHandsomeAndMarryHim
		if (person.handsome == atoi(row[HANDSOME]) && atoi(row[MARRYHIM]) == 1)
		{
			iHandsomeAndMarryHim++;
		}
		//iPoliteAndMarryHim
		if (person.polite == atoi(row[POLITE]) && atoi(row[MARRYHIM]) == 1)
		{
			iPoliteAndMarryHim++;
		}
		//iHighAndMarryHim
		if (person.high == atoi(row[HIGH]) && atoi(row[MARRYHIM]) == 1)
		{
			iHighAndMarryHim++;
		}
		//iHardworkingAndMarryHim
		if (person.hardworking == atoi(row[HARDWORKING]) && atoi(row[MARRYHIM]) == 1)
		{
			iHardworkingAndMarryHim++;
		}


		//iHandsomeAndNotMarryHim
		if (person.handsome == atoi(row[HANDSOME]) && atoi(row[MARRYHIM]) == 0)
		{
			iHandsomeAndNotMarryHim++;
		}
		//iPoliteAndNotMarryHim
		if (person.polite == atoi(row[POLITE]) && atoi(row[MARRYHIM]) == 0)
		{
			iPoliteAndNotMarryHim++;
		}
		//iHighAndNotMarryHim
		if (person.high == atoi(row[HIGH]) && atoi(row[MARRYHIM]) == 0)
		{
			iHighAndNotMarryHim++;
		}
		//iHardworkingAndNotMarryHim
		if (person.hardworking == atoi(row[HARDWORKING]) && atoi(row[MARRYHIM]) == 0)
		{
			iHardworkingAndNotMarryHim++;
		}

	}

	float pHandsomeAndMarryHim = iHandsomeAndMarryHim / iMarryHim;
	float pPoliteAndMarryHim = iPoliteAndMarryHim / iMarryHim;
	float pHighAndMarryHim = iHighAndMarryHim / iMarryHim;
	float pHardworkingAndMarryHim = iHardworkingAndMarryHim / iMarryHim;


	float pHandsomeAndNotMarryHim = iHandsomeAndNotMarryHim / iNotMarryHim;
	float pPoliteAndNotMarryHim = iPoliteAndNotMarryHim / iNotMarryHim;
	float pHighAndNotMarryHim = iHighAndNotMarryHim / iNotMarryHim;
	float pHardworkingAndNotMarryHim = iHardworkingAndNotMarryHim / iNotMarryHim;

	
	float pMarryHim = iMarryHim / (iMarryHim + iNotMarryHim);
	float notMarryHim = 1 - pMarryHim;

	float pMarryHimWithCharacter = pHandsomeAndMarryHim * pPoliteAndMarryHim*pHighAndMarryHim*pHardworkingAndMarryHim*pMarryHim;
	float pNotMarryHimWithCharacter = pHandsomeAndNotMarryHim * pPoliteAndNotMarryHim*pHighAndNotMarryHim*pHardworkingAndNotMarryHim*notMarryHim;

	mysql_free_result(res);
	if (pMarryHimWithCharacter < pNotMarryHimWithCharacter)
	{
		return 0;
	}
	return 1;

}


int main(void)
{
	MYSQL mysql;   

	mysql_init(&mysql);

	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	if (mysql_real_connect(&mysql, "localhost", "root", "root", "algorithm_project4", PORT, NULL, 0) == NULL)
		printf("连接失败！\\n");
	Person person;
	person.handsome = 0;
	person.polite = 0;
	person.high = 0;
	person.hardworking = 0;


	cout<< "is him handsome? 1 = true 0 = false \n";
	cin >> person.handsome;
	cout << "is him polite? 1 = true 0 = false \n";
	cin >> person.polite;
	cout << "is him high? 2 = high 1 = medium 0 = short \n";
	cin >> person.high;
	cout << "is him hardworking? 1 = true 0 = false  \n";
	cin >> person.hardworking;

	if (marry_him(mysql,person))
	{
		cout << "Marry Him !!!\n";
	}
	else
	{
		cout << " don't marry him !!!\n";
	}	
	mysql_close(&mysql);
	system("pause");
	return 0;
}
