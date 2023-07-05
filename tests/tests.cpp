#include <gtest/gtest.h>
#include <iostream>
#include "../include/Handelsplatz.hpp"
<<<<<<< HEAD

=======
#include "../include/Nutzer.hpp"
#include "../src/Nutzer.cpp"
#include "../src/Handelsplatz.cpp"
>>>>>>> e73c3570e6d9c26005a9bc85cb71869be0a5a299

using namespace std;
using namespace ProjectGamma;

<<<<<<< HEAD

=======
string anna = "anna";
string apfel = "apfel";
>>>>>>> e73c3570e6d9c26005a9bc85cb71869be0a5a299

TEST(handelsplatz, findeBenutzer)
{
      Handelsplatz h;
<<<<<<< HEAD
      EXPECT_EQ(h.nameVergeben("anna"), false);
      EXPECT_EQ(h.findeBenutzer("anna"), false);
}

=======
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
>>>>>>> e73c3570e6d9c26005a9bc85cb71869be0a5a299
