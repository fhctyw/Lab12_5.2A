#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_5.2A\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student s = { "Ivan", 2, Spec::IT, 3, 2, 4 };
			Assert::AreEqual((int)avgMark(s), 3);
		}
	};
}
