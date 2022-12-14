/*
 * calculator for rand.x
*/

program RAND_PROG {
  version RAND_VERS {
    int INITIALIZE_RANDOM(string) = 1;
    double GET_NEXT_RANDOM(void) = 2;
  } = 1;
} = 0x31111111;
