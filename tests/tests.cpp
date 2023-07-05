#include <gtest/gtest.h>
#include <iostream>
#include "../include/Handelsplatz.hpp"
#include "../include/Nutzer.hpp"
#include "../src/Nutzer.cpp"
#include "../src/Handelsplatz.cpp"

using namespace std;
using namespace ProjectGamma;

string anna = "anna";
string apfel = "apfel";

TEST(handelsplatz, findeBenutzer)
{
      Handelsplatz h;
      EXPECT_EQ( h.nameVergeben(anna),false);
      EXPECT_EQ(h.findeBenutzer(anna), false);

}

TEST(nutzer, produktBearbeiten)
{
      Nutzer k =Nutzer(anna);
      EXPECT_EQ(k.verkauft(apfel, 12.00, 3),false);
      EXPECT_EQ(k.gekauft(12.00, apfel, 3),false);
      EXPECT_EQ(k.Objekteaussortieren(apfel, 2),false);
      EXPECT_EQ(k.produktzumverkauf(apfel, 2),false);
}
