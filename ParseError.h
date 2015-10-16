#pragma once
#include <stdexcept>
#include <string>
using namespace std;
namespace vp
{
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
}