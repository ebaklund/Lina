#include <CppUnitTest.h>
#include "Modal.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModalTests
{
    TEST_CLASS(ModelTests)
    {
    public:
        TEST_METHOD(Default_constructor)
        {
            Modal::Model m;
        }
    };
}

