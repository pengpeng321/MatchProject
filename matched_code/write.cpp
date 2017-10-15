#include "stdafx.h"
#include<iostream>
#include<fstream>
#include "student.h"
#include "department.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <list>
#include <sstream>
using namespace std;
using namespace rapidjson;
void write(std::list<int>* stuList, std::list<int>* depList, student* stu, department* dep,int stu_number, int dep_number)
{
	int i;
	list<int>::iterator n;
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();
	//
	
	//输出部门匹配情况
	Value array(kArrayType);
	for (i = 0; i < dep_number; i++) 
	{
		if (depList[i].size() == 0) continue;								//部门没有纳新到学生deplist为空时无需输出
		Value object1(kObjectType);
		object1.AddMember("department_no", dep[i].getDep_no(), allocator);
		Value array1(kArrayType);
		for (n=depList[i].begin();n!=depList[i].end();n++)
		{
			array1.PushBack(stu[*n].getStu_no(), allocator);
		}
		object1.AddMember("matched_stu", array1, allocator);
		array.PushBack(object1, allocator);
	}
	document.AddMember("matched_department", array, allocator);
	
	//输出学生加入部门的情况
	Value array2(kArrayType);
	for (i = 0; i < stu_number; i++) 
	{
		if (stuList[i].size() == 0) continue;								//学生没有加入部门 stulist为空时无需输出
		Value object2(kObjectType);
		object2.AddMember("student_no", stu[i].getStu_no(), allocator);
		Value array3(kArrayType);
		for (n=stuList[i].begin();n!=stuList[i].end();n++)
		{
			array3.PushBack(dep[*n].getDep_no(), allocator);
		}
		object2.AddMember("matched_dep", array3, allocator);
		array2.PushBack(object2, allocator);
	}
	document.AddMember("matched_student", array2, allocator);

	//输出没有纳新到学生的部门
	Value array4(kArrayType);
	for (i = 0; i < dep_number; i++)
	{
		if (depList[i].size() != 0) continue;								//部门纳新到学生 deplist不为空时无需输出
		array4.PushBack(dep[i].getDep_no(), allocator);
	}
	document.AddMember("standalone_departments", array4, allocator);

	//输出没有加入部门的学生
	Value array5(kArrayType);
	for (i = 0; i < stu_number; i++) 
	{
		if (stuList[i].size() != 0) continue;								//学生加入部门 stulist不为空时无需输出
		array5.PushBack(stu[i].getStu_no(), allocator);
	}
	document.AddMember("standalone_students", array5, allocator);
	ofstream fout;
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	document.Accept(writer);
	const char * out = buffer.GetString();
	//cout << out << endl;

	//根据stu_number和dep_number设置path
	stringstream ss;
	string path = "s";
	string temp;
	ss << stu_number;
	ss >> temp;
	path = path + temp + "-d";
	ss.clear();
	ss << dep_number;
	ss >> temp;
	path = path + temp + "-out.json";

	fout.open(path);
	fout << buffer.GetString();
	fout.close();
}