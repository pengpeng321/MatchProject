#pragma once
#include <string>
class department
{
private:
	int number_limit;				//�����������ѧ������
	int dep_no;						//���ű��
	std::string dep_name;			//��������
	std::string tags[10];			//����ϣ��ѧ��ӵ�е��س�
	std::string avail_time[20];		//���Żʱ�䰲�ű�

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

