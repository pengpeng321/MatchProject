#pragma once
#include <string>
class student
{
private:
	int stu_no;								//ѧ��ѧ��
	std::string stu_name;					//ѧ������
	std::string tags[10];					//ѧ����Ȥ����    ���10��
	std::string avail_time[20];				//ѧ���пյ�ʱ��  ���20��
	int dep_will[5];						//ѧ��������Ը	  ���5��
	float score;							//ѧ������

	int tag_number;							//���ø���
	int time_number;						//ʱ��θ���
	int will_number;						//������Ը����
public:

	//��ȡ���private������Ϣ
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

