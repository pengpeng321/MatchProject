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
#include <list>

void write(std::list<int>* stuList, std::list<int>* depList, student* stu, department* dep,int stu_number,int dep_number);