#include "stdafx.h"
#include "CppUnitTest.h"
#include "Application.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestSMth)
	{
		SE::Application app;
		
	public:
		
		TEST_METHOD(TestMyMethod)
		{
			SE::Rectangle r1(SE::vec3(3.0f, 4.0f, 0.0f), SE::vec2(10, 10), SE::vec3(0.0, 1.0, 0.0), 0);
			//SE::Rectangle r2(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			//bool result = app.isCollided(&r1, &r2);
			// TODO: Your test code here
			//Assert::AreEqual(true,result);
			Assert::IsTrue(true);
		}

	};
}