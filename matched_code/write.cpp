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
	
	//�������ƥ�����
	Value array(kArrayType);
	for (i = 0; i < dep_number; i++) 
	{
		if (depList[i].size() == 0) continue;								//����û�����µ�ѧ��deplistΪ��ʱ�������
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
	
	//���ѧ�����벿�ŵ����
	Value array2(kArrayType);
	for (i = 0; i < stu_number; i++) 
	{
		if (stuList[i].size() == 0) continue;								//ѧ��û�м��벿�� stulistΪ��ʱ�������
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

	//���û�����µ�ѧ���Ĳ���
	Value array4(kArrayType);
	for (i = 0; i < dep_number; i++)
	{
		if (depList[i].size() != 0) continue;								//�������µ�ѧ�� deplist��Ϊ��ʱ�������
		array4.PushBack(dep[i].getDep_no(), allocator);
	}
	document.AddMember("standalone_departments", array4, allocator);

	//���û�м��벿�ŵ�ѧ��
	Value array5(kArrayType);
	for (i = 0; i < stu_number; i++) 
	{
		if (stuList[i].size() != 0) continue;								//ѧ�����벿�� stulist��Ϊ��ʱ�������
		array5.PushBack(stu[i].getStu_no(), allocator);
	}
	document.AddMember("standalone_students", array5, allocator);
	ofstream fout;
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	document.Accept(writer);
	const char * out = buffer.GetString();
	//cout << out << endl;

	//����stu_number��dep_number����path
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