#include <CppUnitTest.h>
#include "Modal.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModalTests
{
    TEST_CLASS(StateTests)
    {
    public:
        TEST_METHOD(Default_constructor)
        {
            Modal::State<float, 10> s;
        }
    };
}

