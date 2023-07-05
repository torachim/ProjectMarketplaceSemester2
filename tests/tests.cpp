#include <gtest/gtest.h>
#include <iostream>
#include "../include/Handelsplatz.hpp"
#include "../include/Nutzer.hpp"
#include "../include/Objekt.hpp"

using namespace ProjectGamma;

TEST(handelsplatz, isHit)
{
      Handelsplatz h;
      h.login(Nutzer1, 2023);  //Nach anpassen der Funktion für Phyton
      EXPECT_EQ(h.login(Nutzer1, 2023));
      EXPECT_EQ();
}

TEST(boardfkt, canSetShip)
{
      board m;
      EXPECT_EQ(m.canSetShip(4, 6, 1), true);
      EXPECT_EQ(m.canSetShip(9, 6, 1), false); // Ausnahmen beachten
}

TEST(boardfkt, winner)
{
      board m;
      EXPECT_EQ(m.winner(), true);
}