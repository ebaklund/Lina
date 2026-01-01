
#include <Modal/Modal.h>

int x(int number) { return number <= 1 ? number : x(number - 1) * number; }

//TEST_CASE("testing the factorial function") {
//    CHECK(x(1) == 1);
//
//}
//