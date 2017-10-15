#include "stdafx.h"
#include "match.h"
#include "student.h"
#include "time.h"

#include <iostream>
#include <list>
#include <string>

void match::matched(student* stu, department* dep, std::list<int>* stuList, std::list<int>* depList, int stu_number, int dep_number)
{
	/*ƥ��ʱ�����ò�����ѡѧ��
	  ����Ȩֵ���£�
		��ѧ����д�Ĳ�����Ը�����˲��ţ����õ���Ȩֵ������7�֣�
		��ѧ���ļ���Խ�ߣ��õ���Ȩֵ�ı���Խ�ߣ�����2�֣�
		��ѧ���ܲ��벿�ų����ĸ���Խ�࣬�õ���Ȩֵ�ı���Խ�ߣ���3�֣�
		��ѧ������Ȥ�����벿��ϣ��ӵ�е���Ȥ������ͬ����Խ�࣬�õ���Ȩֵ�ı���Խ�ߣ���2�֣�
	  ÿ��ѧ����Ȩֵ�Ӹߵ������򣬹�������ѡ����ѡԭ�����£�
		ĳѧ����Ȩֵ���ڵ���7�ֲ����ʸ����˲���
		Ȩֵ�ߵ����Ƚ��벿��
		�����µ������ﵽ���������������ʱ����������
	 */
	int i,j,m,n,temp;								 //ѭ��������
	double stu_dep[5000];							 //ÿ��ѧ����Ȩֵ
	double q;										 //ĳ��ѧ����ʱȨֵ

	int stu_dep_sort[5000];							 //����ÿ�����ţ���ѧ��Ȩֵ����
	int k;											 //stu_dep_sort�����Ԫ�ظ���

	int sw, st, sa;									//ѧ�� ������Ը����/��Ȥ��ǩ����/�п�ʱ������
	int dt, da;										//���� ϣ����Ȥ��ǩ����/�ʱ������
	
	stime stuTime[20],depTime[20];

	for (i = 0; i < dep_number; i++)
	{
		k = 0;
		dt = dep[i].getTag_number();
		da = dep[i].getTime_number();
		timeConvert(dep[i].getAvail_time(), da, depTime);
		for (j = 0; j < stu_number; j++)
		{
			/*�������ÿһ�����ţ�����ÿ��ѧ���Ķ�ӦȨֵ*/
			q = 0;
			sw = stu[j].getWill_number();
			st = stu[j].getTag_number();
			sa = stu[j].getTime_number();

			/*����ѧ��ѡ���ŵ���Ը����Ȩֵ	*/
			for (m = 0; m < sw; m++)
			{
				if (*(stu[j].getDep_will() + m) == dep[i].getDep_no())
				{
					q += 7;						//����Ȩֵ���ۼӣ�
					break;
				}
			}

			/*����ѧ���ļ���������Ȩֵ*/
			q += (stu[j].getScore() / 5.0) * 2;

			/*����ѧ�����п�ʱ��κͲ��Żʱ���������Ȩֵ*/
			//timeConvert()�����ַ�����ʾ��ʱ��ת������stime���ʾ
			timeConvert(stu[j].getAvail_time(), sa, stuTime);
			
			temp = 0;
			for (m = 0; m < da; m++)
			{
				/*����ÿ�����ŵ�ʱ���ѭ��ѧ���п�ʱ��*/
				for (n = 0; n < sa; n++)
				{
					if (stuTime[n].week != depTime[m].week)  continue;
					if (stuTime[n].start > depTime[m].start)	continue;
					if (stuTime[n].end < depTime[m].end)	continue;
					temp++;
					break;
				}
			}
			q += temp*1.0 / da * 2;			//����Ȩֵ���ۼӣ�

			/*����ѧ������Ȥ���úͲ�����Ҫ����Ȥtags������Ȩֵ*/
			temp = 0;
			for (m = 0; m < dt; m++)
			{
				/*����ÿ�����ŵ���ȤҪ���ѭ��ѧ������Ȥ*/
				for (n = 0; n < st; n++)
				{
					if (*(stu[j].getTags() + n) != *(dep[i].getTags() + m)) continue;
					temp++;
					break;
				}
			}
			q += temp*1.0 / dt * 2;			//����Ȩֵ���ۼӣ�

			/*����x��ѧ��������Ȩֵ������stu_dep[x]��*/
			stu_dep[j] = q;

			/*��ѧ����Ȩֵ��������Ȩֵ���ѧ�����±꣬������������stu_dep_sort��ǰ��*/
			if (q < 7)continue;					//ȨֵС��7�������¼��ѧ��
			stu_dep_sort[k] = j;
			for (n = k - 1; n > -1; n--)
			{
				if (stu_dep[stu_dep_sort[n + 1]] > stu_dep[stu_dep_sort[n]])
				{
					temp = stu_dep_sort[n + 1];
					stu_dep_sort[n + 1] = stu_dep_sort[n];
					stu_dep_sort[n] = temp;
				}
			}
			k++;
		}
		
		/*
		std::cout << "Ȩֵ����" << std::endl;
		for (n = 0; n < k; n++)
		{
			std::cout <<n<<' '<< stu[stu_dep_sort[n]].getStu_name() << " " << stu_dep[stu_dep_sort[n]] << "	";
		}
		std::cout << std::endl;
		std::cout << std::endl;


		/*���ڲ��ţ���deplist�м�¼�����벿�ŵ�ѧ��������stu�е������±�
		  ����ѧ������stulist�м�¼�¼���Ĳ���������dep�е������±�	*/

		for (n = 0; n < dep[i].getNumber_limit(); n++)
		{
			if (n >= j) break;									//�ﵽ���ſ�ѡ�������� n > stu_dep_sort����Ԫ�ظ���
			if (n >= k) break;								   //�������������ﵽ���ֵ����������
			if (stuList[stu_dep_sort[n]].size() >= 5) continue; //ѧ������Ĳ��Ŵﵽ��������ټ���
			depList[i].push_back(stu_dep_sort[n]);
			stuList[stu_dep_sort[n]].push_back(i);
		}
	}
}

void match::timeConvert(std::string* time, int number,stime* ansTime)
{
	//���ʱ����*ת���� stime* �ࣨ�����ܼ�����ʼʱ�䣬����ʱ�䣩
	int i, j, temp;
	for(i=0;i<number;i++)
	{
		j = 0;
		switch (time[i][j])
		{
		case 'm':
			j += 3;
			ansTime[i].week = 1; 
			break;
		case 't':
			if (time[i][j + 1] == 'u') { ansTime[i].week = 2; }
			else { ansTime[i].week = 4; }
			j += 4;
			break;
		case 'w':
			j += 3;
			ansTime[i].week = 3;
			break;
		case 'f':
			j += 3;
			ansTime[i].week = 5;
			break;
		case 's':
			if (time[i][j + 1] == 'a') { ansTime[i].week = 6; }
			else { ansTime[i].week = 7; }
			j += 3;
			break;
		default:exit(1);
		}
		temp = 0;
		temp = temp * 10 + (time[i][j++] - '0');
		temp = temp * 10 + (time[i][j++] - '0');
		ansTime[i].start = temp;
		j++;
		temp = 0;
		temp = temp * 10 + (time[i][j++] - '0');
		temp = temp * 10 + (time[i][j] - '0');
		ansTime[i].end = temp;
		//std::cout << ansTime[i].week << ' ' << ansTime[i].start << ' ' << ansTime[i].end << std::endl;
	}
	//std::cout << std::endl;
}

match::match()
{
}


match::~match()
{
}
