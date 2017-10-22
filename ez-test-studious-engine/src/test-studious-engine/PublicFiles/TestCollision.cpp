#include "stdafx.h"
#include "CppUnitTest.h"
#include "Application.h"
#include "SimpleRenderer.h"
#include "Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCollision
{
	TEST_CLASS(TestCollision)
	{
		SE::Application app;

	public:

		TEST_METHOD_INITIALIZE(SetupWindowAndRender)
		{
			auto window = std::make_shared<SE::Window>("test", 151, 152);
			auto test = new SE::SimpleRenderer();
		}

		TEST_METHOD(TestLeftTopCornerCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(70, 70, 0.0f), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}
		TEST_METHOD(TestRightDownCornerCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(70, 70, 0.0f), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r2, &r1);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestLeftDownCornerCollision)
		{

			SE::Rectangle r1(SE::vec3(150, 150, 0.0f), SE::vec2(50, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(70, 70, 0.0f), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r2, &r1);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestRightTopCornerCollision)
		{

			SE::Rectangle r1(SE::vec3(150, 150, 0.0f), SE::vec2(50, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(70, 70, 0.0f), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}


		TEST_METHOD(TestInsideTopCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(70, 70, 0.0f), SE::vec2(30, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestInsideDownCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(70, 70, 0.0f), SE::vec2(30, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r2, &r1);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestNoCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(20, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(80, 80, 0.0f), SE::vec2(30, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsFalse(result);
		}

		TEST_METHOD(TestTopEdgeCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 100), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(40, 30, 0.0f), SE::vec2(20, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestLeftEdgeCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(150, 70, 0.0f), SE::vec2(20, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestDownEdgeCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(20, 100, 0.0f), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestRightEdgeCollision)
		{

			SE::Rectangle r1(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec3(150, 70, 0.0f), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestGLEW)
		{
			Assert::IsTrue(glewInit());
		}
	};
}