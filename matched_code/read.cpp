
#include "stdafx.h"
#include "student.h"
#include "department.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
using namespace rapidjson;
void getPath(char* ,int, int);
//��ȡjson���ݸ�ѧ��
void toStudent(student* stu, int stu_number,int dep_number)
{
	FILE* fp;
	char path[20];
	getPath(path, stu_number, dep_number);
	auto err = fopen_s(&fp, path, "r");
	char readBuffer[6000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	fclose(fp);
	if (d.HasParseError())
	{
		cout << "get json data err!" << endl;
	}
	Value& students = d["students"];
	int stu_no;						//ѧ��ѧ��
	string stu_name;					//ѧ������
	string tags[10];					//ѧ����Ȥ����    ���10��
	string avail_time[20];				//ѧ���пյ�ʱ��  ���20��
	int dep_will[5];						//ѧ��������Ը	  ���5��
	float score;							//ѧ������
	int tag_number;							//���ø���
	int time_number;						//ʱ��θ���
	int will_number;
	
	if (students.IsArray())
	{
		for (SizeType i = 0; i < stu_number; i++)
		{
			Value student;
			student = students[i];
			stu_no = student["student_no"].GetInt();
			stu_name = student["student_name"].GetString();
			Value array1, array2, array3;
			array1 = student["tags"];
			tag_number = 0;
			for (SizeType j = 0; j < array1.Size(); j++)
			{
				tags[j] = array1[j].GetString();
				
				tag_number++;
			}
			array2 = student["available_schedules"];
			time_number = 0;
			for (SizeType j = 0; j < array2.Size(); j++)
			{
				avail_time[j] = array2[j].GetString();
				
				time_number++;
			}
			array3 = student["department_will"];
			will_number = 0;
			for (SizeType j = 0; j < array3.Size(); j++)
			{
				dep_will[j] = array3[j].GetInt();
				//cout << dep_will[j];
				will_number++;
			}
			score = student["score"].GetDouble();
			stu[i].setData(stu_no, stu_name, tags, avail_time, dep_will, score, tag_number, time_number, will_number);
		}
		
	}
}
//��ȡjson���ݸ�����
void toDepartment(department* dep, int stu_number, int dep_number)
{
	FILE* fp;
	char path[20];
	getPath(path, stu_number, dep_number);
	auto err = fopen_s(&fp, path, "r");
	char readBuffer[6000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	fclose(fp);
	if (d.HasParseError())//|| !d.IsArray())
	{
		cout << "get json data err!" << endl;
	}
	int number_limit;				//�����������ѧ������
	int dep_no;						//���ű��
	string dep_name;			//��������
	string tags[10];			//����ϣ��ѧ��ӵ�е��س�
	string avail_time[20];		//���Żʱ�䰲��
	int tag_number;
	int time_number;
	Value& departments = d["departments"];
	if (departments.IsArray())
	{
		for (SizeType i = 0; i < dep_number; i++)
		{
			Value department;
			department = departments[i];
			number_limit = department["member_limit"].GetInt();
			
			dep_no = department["department_no"].GetInt();
			dep_name = department["department_name"].GetString();
			
			Value array1, array2, array3;
			array1 = department["tags"];
			tag_number = 0;
			for (SizeType j = 0; j < array1.Size(); j++)
			{
				tags[j] = array1[j].GetString();
				
				tag_number++;
			}
			array2 = department["event_schedules"];
			time_number = 0;
			for (SizeType j = 0; j < array2.Size(); j++)
			{
				avail_time[j] = array2[j].GetString();
				//cout << avail_time[j] <<' ';
				time_number++;
			}
			dep[i].setData(number_limit, dep_no, dep_name, tags, avail_time, tag_number, time_number);
		}

	}
}

void getPath(char*path, int stu_number, int dep_number)
{
	/*����stu_number��dep_number����ȡ�ļ�����*/
	char temp[10];
	sprintf_s(temp, "%d", stu_number);
	strcpy_s(path, sizeof(char) * 20,"s");
	strcat_s(path, sizeof(char) * 20, temp);
	strcat_s(path, sizeof(char) * 20, "-d");
	sprintf_s(temp, "%d", dep_number);
	strcat_s(path, sizeof(char) * 20, temp);
	strcat_s(path, sizeof(char) * 20, "-in.json");
}