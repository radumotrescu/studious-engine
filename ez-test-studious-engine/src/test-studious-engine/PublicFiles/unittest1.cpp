#include "stdafx.h"
#include "CppUnitTest.h"
#include "Application.h"
#include "SimpleRenderer.h"
#include "Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestSMth)
	{
		SE::Application app;
		
	public:
		
		TEST_METHOD(TestMyMethod)
		{
			Assert::IsTrue(glewInit());
			auto window = std::make_shared<SE::Window>("test", 151, 152);
			auto test = new SE::SimpleRenderer();
			SE::Rectangle r2(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			r2.moveLeft();
			//bool result = app.isCollided(&r1, &r2);
			// TODO: Your test code here
			//Assert::AreEqual(true,result);
			Assert::IsTrue(true);
		}

	};
}