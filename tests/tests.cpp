#include <gtest/gtest.h>
#include <iostream>
#include "../include/Handelsplatz.hpp"


using namespace ProjectGamma;



TEST(handelsplatz, findeBenutzer)
{
      Handelsplatz h;
      EXPECT_EQ(h.nameVergeben("anna"), false);
      EXPECT_EQ(h.findeBenutzer("anna"), false);
}

