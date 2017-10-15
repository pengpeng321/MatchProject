#pragma once
#include <string>
class student
{
private:
	int stu_no;								//学生学号
	std::string stu_name;					//学生姓名
	std::string tags[10];					//学生兴趣爱好    最多10个
	std::string avail_time[20];				//学生有空的时间  最多20个
	int dep_will[5];						//学生部门意愿	  最多5个
	float score;							//学生绩点

	int tag_number;							//爱好个数
	int time_number;						//时间段个数
	int will_number;						//部门意愿个数
public:

	//获取相关private个人信息
	int getStu_no();
	std::string getStu_name();
	std::string* getTags();
	std::string* getAvail_time();
	int* getDep_will();
	float getScore();
	int getTag_number();
	int getTime_number();
	int getWill_number();
	void setData(int, std::string,std::string*, std::string*, int*, float,int,int,int);
	
	student();
	~student();
};

