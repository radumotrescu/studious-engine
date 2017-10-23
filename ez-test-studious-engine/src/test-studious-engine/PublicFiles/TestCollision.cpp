#include "stdafx.h"
#include "CppUnitTest.h"
#include "SimpleRenderer.h"
#include "Window.h"
#include "CollisionChecker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCollision
{
	TEST_CLASS(TestCollision)
	{
		SE::CollisionChecker app;

	public:

		TEST_METHOD_INITIALIZE(SetupWindowAndRender)
		{
			Assert::IsTrue(glewInit());
			auto window = std::make_shared<SE::Window>("test", 151, 152);
			auto test = new SE::SimpleRenderer(151,152,10);
		}

		TEST_METHOD(TestLeftTopCornerCollision)
		{

			Assert::IsTrue(glewInit());
			auto window = std::make_shared<SE::Window>("test", 151, 152);
			auto test = new SE::SimpleRenderer(151,152,10);
			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(70, 70), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}
		TEST_METHOD(TestRightDownCornerCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(70, 70), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r2, &r1);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestLeftDownCornerCollision)
		{

			SE::Rectangle r1(SE::vec2(150, 150), SE::vec2(50, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(70, 70), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r2, &r1);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestRightTopCornerCollision)
		{

			SE::Rectangle r1(SE::vec2(150, 150), SE::vec2(50, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(70, 70), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}


		TEST_METHOD(TestInsideTopCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(70, 70), SE::vec2(30, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestInsideDownCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(70, 70), SE::vec2(30, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r2, &r1);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestNoCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(20, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(80, 80), SE::vec2(30, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsFalse(result);
		}

		TEST_METHOD(TestTopEdgeCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 100), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(40, 30), SE::vec2(20, 20), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestLeftEdgeCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(150, 70), SE::vec2(20, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestDownEdgeCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(20, 100), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestRightEdgeCollision)
		{

			SE::Rectangle r1(SE::vec2(50, 50), SE::vec2(100, 50), SE::vec3(0.0, 0.0, 0.0), 2);
			SE::Rectangle r2(SE::vec2(150, 70), SE::vec2(100, 130), SE::vec3(0.0, 0.0, 0.0), 2);
			bool result = app.isCollided(&r1, &r2);

			Assert::IsTrue(result);
		}

		TEST_METHOD(TestGLEW)
		{
			Assert::IsTrue(glewInit());
		}
	};
}