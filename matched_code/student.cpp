#include "stdafx.h"
#include "student.h"

#include <iostream>
#include <string>

int student::getStu_no() { return stu_no; }
std::string student::getStu_name() { return stu_name; }
std::string* student::getTags() { return tags; }
std::string* student::getAvail_time() { return avail_time; }
int* student::getDep_will() { return dep_will; }
float student::getScore() { return score; }
int student::getTag_number() { return tag_number; }
int student::getTime_number() { return time_number; }
int student::getWill_number() { return will_number; }


void student::setData(int stu_no, std::string stu_name, std::string* tags, std::string* avail_time, int* dep_will, float score, int tag_number, int time_number, int will_number)
{
	//设置student个人信息
	int i;
	student::stu_no = stu_no;
	student::stu_name = stu_name;
	student::score = score;
	student::tag_number = tag_number;
	student::time_number = time_number;
	student::will_number = will_number;
	for (i = 0; i < tag_number;  i++) 
	{
		student::tags[i] = tags[i];
	}
	for (i = 0; i < time_number; i++)
	{
		student::avail_time[i] = avail_time[i];
	}
	for (i = 0; i < will_number; i++)
	{
		student::dep_will[i] = dep_will[i];
	}
}

student::student()
{
}


student::~student()
{
}
