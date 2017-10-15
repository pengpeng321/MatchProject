#pragma once
#include "stdafx.h"
#include<iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "student.h"
#include "department.h"


//读取json数据给学生
void toStudent(student* stu,int stu_number, int dep_number);

//读取json数据给部门
void toDepartment(department* dep, int stu_number, int dep_number);