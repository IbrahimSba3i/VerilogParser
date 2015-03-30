#pragma once
#include <stdexcept>
using namespace std;
class ParseError : public exception
{
	string errorMsg;
public:
	explicit ParseError(){}

	explicit ParseError(const string& errorMsg){
		this->errorMsg = errorMsg;
	}

	virtual ~ParseError() throw (){}

	virtual const char* what() const throw (){
		return errorMsg.c_str();
	}
};