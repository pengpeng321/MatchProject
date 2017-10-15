
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
//读取json数据给学生
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
	int stu_no;						//学生学号
	string stu_name;					//学生姓名
	string tags[10];					//学生兴趣爱好    最多10个
	string avail_time[20];				//学生有空的时间  最多20个
	int dep_will[5];						//学生部门意愿	  最多5个
	float score;							//学生绩点
	int tag_number;							//爱好个数
	int time_number;						//时间段个数
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
//读取json数据给部门
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
	int number_limit;				//部门最多加入的学生数量
	int dep_no;						//部门编号
	string dep_name;			//部门名称
	string tags[10];			//部门希望学生拥有的特长
	string avail_time[20];		//部门活动时间安排
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
	/*根据stu_number和dep_number来获取文件名称*/
	char temp[10];
	sprintf_s(temp, "%d", stu_number);
	strcpy_s(path, sizeof(char) * 20,"s");
	strcat_s(path, sizeof(char) * 20, temp);
	strcat_s(path, sizeof(char) * 20, "-d");
	sprintf_s(temp, "%d", dep_number);
	strcat_s(path, sizeof(char) * 20, temp);
	strcat_s(path, sizeof(char) * 20, "-in.json");
}