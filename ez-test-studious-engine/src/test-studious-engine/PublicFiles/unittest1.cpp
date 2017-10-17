#include "stdafx.h"
#include "CppUnitTest.h"
#include "Application.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestSMth)
	{
	public:
		
		TEST_METHOD(TestMyMethod)
		{
			SE::Application app;
			int a = 5;
			int b = 2;
			int sum = a + b;
			int c = 7;
			// TODO: Your test code here
			Assert::AreEqual(c, sum);
		}

	};
}