#pragma once
#include "student.h"
#include "department.h"
#include "time.h"
#include <list>
class match
{
public:
	static void matched(student*, department*, std::list<int>*, std::list<int>*, int, int);
	static void timeConvert(std::string*, int,stime*);
	match();
	~match();
};

