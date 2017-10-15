#pragma once
#include <string>
class department
{
private:
	int number_limit;				//部门最多加入的学生数量
	int dep_no;						//部门编号
	std::string dep_name;			//部门名称
	std::string tags[10];			//部门希望学生拥有的特长
	std::string avail_time[20];		//部门活动时间安排表

	int tag_number;
	int time_number;

public:
	int getNumber_limit();
	int getDep_no();						
	std::string getDep_name();			
	std::string* getTags();			
	std::string* getAvail_time();
	int getTag_number();
	int getTime_number();

	void setData(int, int, std::string, std::string*, std::string*, int, int);

	department();
	~department();
};

