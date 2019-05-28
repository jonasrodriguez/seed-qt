#include <gtest/gtest.h>

#include "Comms.h"

TEST(TestComms, Test1) {
  CommsConfiguration cnf;
  cnf.ip = "google.com";
  cnf.port = 1234;

  Comms comms;
  comms.SetCommsAddress(cnf);

  QString ip("http://" + cnf.ip + ":" + QString::number(cnf.port));

  ASSERT_EQ(comms.GetCommsAddres(), ip);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
