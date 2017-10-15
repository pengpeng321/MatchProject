#include "stdafx.h"
#include "department.h"

int department::getNumber_limit() { return number_limit; }
int department::getDep_no() { return dep_no; }
std::string department::getDep_name() { return dep_name; }
std::string* department::getTags() { return tags; }
std::string* department::getAvail_time() { return avail_time; }
int department::getTag_number() { return tag_number; }
int department::getTime_number() { return time_number; }


void department::setData(int number_limit, int dep_no, std::string dep_name, std::string* tags, std::string* avail_time, int tag_number, int time_number)
{
	////设置department个人信息
	int i;
	department::number_limit = number_limit;
	department::dep_no = dep_no;
	department::dep_name = dep_name;
	department::tag_number = tag_number;
	department::time_number = time_number;
	for (i = 0; i < tag_number; i++)
	{
		department::tags[i] = tags[i];
	}
	for (i = 0; i < time_number; i++)
	{
		department::avail_time[i] = avail_time[i];
	}
}


department::department()
{
}


department::~department()
{
}
