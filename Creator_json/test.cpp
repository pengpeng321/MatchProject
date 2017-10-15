// test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

//生成随机字符串
string randString();
//生成size长度，数字大小不超过max的随机字符串
void randArray(int size,int max,int* array);

int main()
{
	ofstream fout;
	int student_num;
	int department_num;
	int tag_count;
	int event_count;
	int department_no;
	int member_limit;
	int student_no;
	int department_will;
	double score;
	int arra[10];
	string tag_hub[10] = { "singing","dancing","guiter","swimming","soccer","basketball",
						"movie","reading","computer","chess" };
	string event_hub[10] = { "mon8:00-10:00","tues8:00-11:00","wed9:00-11:00","thur9:00-12:00","fri14:00-15:00",
						"sat14:00-16:00","sun15:00-16:00","sat15:00-17:00","sun19:00-21:00","sun19:00-22:00" };
	string department_name;
	string student_name;
	//
	//
	cin >> department_num;//输入部门数量
	cin >> student_num;//输入学生数量
	//
	//
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();
	Value array(kArrayType);
	//
	for (int i = 0; i < department_num; i++)
	{
		department_no = i + 1;//部门号码
		department_name = randString();//随机部门名称
		tag_count = rand() % 10+1;//随机部门标签数量
		event_count = rand() % 5 + 1;//随机部门事件数量
		member_limit = rand() % 15+1;//随机部门人数
		score = (rand() % 50) / 10.0;//随机绩点
		Value object(kObjectType);
		//设置部门号码
		object.AddMember("department_no", department_no, allocator);
		//设置部门名称
		object.AddMember("department_name", Value(department_name.c_str(), document.GetAllocator()).Move(), allocator);
		//设置部门人数限制
		object.AddMember("member_limit", member_limit, allocator);
		//设置部门标签
		randArray(tag_count, 10, arra);
		Value array2(kArrayType);
		for (int i = 0; i < tag_count; i++)
		{
			array2.PushBack(Value(tag_hub[arra[i]].c_str(), document.GetAllocator()).Move(), allocator);
		}
		object.AddMember("tags",array2, allocator);
		//设置部门时间表
		randArray(event_count, 10, arra);
		Value array3(kArrayType);
		for (int i = 0; i < event_count; i++)
		{
			array3.PushBack(Value(event_hub[arra[i]].c_str(), document.GetAllocator()).Move(), allocator);
		}
		object.AddMember("event_schedules",array3, allocator);
		//设置分数限制
		object.AddMember("score_limit",score, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("departments", array, allocator);
	//
	//
	//生成学生信息
	Value array1(kArrayType);
	for (int i = 0; i < student_num; i++)
	{
		student_no = i + 1;//学生学号
		student_name = randString();//随机学生名字
		tag_count = rand() % 10+1;//随机学生标签数量
		event_count = rand() % 5 + 1;//随机学生事件数量
		department_will = rand() % 5+1;//随机意愿部门数量
		score = (rand() % 50) / 10.0;//随机绩点
		Value object(kObjectType);
		//设置学号
		object.AddMember("student_no", student_no, allocator);
		//设置学生姓名
		object.AddMember("student_name", Value(student_name.c_str(), document.GetAllocator()).Move(), allocator);
		//设置学分
		object.AddMember("score", score, allocator);

		//添加兴趣
		randArray(tag_count, 10, arra);
		Value array4(kArrayType);
		for (int i = 0; i < tag_count; i++)
		{
			array4.PushBack(Value(tag_hub[arra[i]].c_str(), document.GetAllocator()).Move(), allocator);
		}
		object.AddMember("tags", array4, allocator);

		//添加时间表
		randArray(event_count, 10, arra);
		Value array3(kArrayType);
		for (int i = 0; i < event_count; i++)
		{
			array3.PushBack(Value(event_hub[arra[i]].c_str(), document.GetAllocator()).Move(), allocator);
		}
		object.AddMember("available_schedules", array3, allocator);

		//设置学生的部门意愿
		randArray(department_will, department_num,arra);
		Value array5(kArrayType);
		for (int i = 0; i < department_will; i++)
		{
			array5.PushBack(arra[i]+1, allocator);
		}
		object.AddMember("department_will", array5, allocator);/**/
		array1.PushBack(object, allocator);
	}
	document.AddMember("students", array1, allocator);
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	document.Accept(writer);
	const char * out = buffer.GetString();
	cout << out << endl;
	fout.open("wjson.json");
	fout << buffer.GetString();
	fout.close();
    return 0;
}
string randString()
{
	int size = rand() % 10+1;
	string ch;
	string str;
	for (unsigned i = 0; i < size; i++)
	{
		ch = rand() % 26 + 97;
		str = str+ch;
	}
	return str;
}
void randArray(int size, int max,int* array)
{
	int temp;
	int i;
	int j;
	array[0] = rand() % max;
	for (i = 1; i < size; i++)
	{
		temp = rand() % max;
		for (j = 0; j < i; j++)
		{
			if (temp == array[j])
			{
				break;
			}
		}
		if (j == i)
		{
			array[i] = temp;
		}
		else
		{
			i--;
		}
	}
}

