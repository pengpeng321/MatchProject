// SDMatched.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "rapidjson/document.h"
#include "student.h"
#include "department.h"
#include "match.h"
#include "read.h"
#include "write.h"

#include <string>
#include <iostream>
#include <cstring>
#include <list>
int main()
{
	int stu_number = 5000;
	int dep_number = 100;

	std::list<int>* stuList=new std::list<int>[stu_number];		//学生链表数组，存放x学生加入的所有部门
	std::list<int>* depList=new std::list<int>[dep_number];		//部门链表数组，存放x部门对应的所有纳新招收的学生
	student* stu=new student[stu_number];						//学生数组，存放所有学生信息
	department* dep=new department[dep_number];				    //部门数组，存放所有部门信息

	//从json文件中读取数据到数组stu和dep中
	toStudent(stu, stu_number, dep_number);
	toDepartment(dep, stu_number, dep_number);

	//进行匹配
	match::matched(stu, dep, stuList, depList, stu_number, dep_number);

	//将匹配结果输出
	write(stuList, depList, stu, dep, stu_number, dep_number);

	//释放空间
	delete[] stu;
	delete[] dep;
	delete[] stuList;
	delete[] depList;
	return 0;
}

