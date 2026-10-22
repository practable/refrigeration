/*   adamFunctions

  All functions relating to ADAM industrial controllers



*/

#include "globals.h"

#ifndef adamFunctions_h
#define adamFunctions_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

enum adamName_t {
    ADAM6052_A,
    ADAM6052_B,
    ADAM6217_C,
    ADAM6217_D,
};

class adamFunctions {
  public:
    adamFunctions();

    void adams_begin();

    bool check_modbus_connection(adamName_t unit);

    void set_DO(adamName_t unit, int coilNum, bool coilState);

    void sample_adam6052A();
    void sample_adam6052B();
    void sample_adam6217C();
    void sample_adam6217D();

  private:
    // Create an adamController object and pass the Ethernet Client and IP Address for the server
    // adamController adam6052_A(ethClient, adam6052A_ip, DAC_OUTPUT, "ADAM-6052-A");
    // adamController adam6052_B(ethClient, adam6052B_ip, DAC_OUTPUT, "ADAM-6052-B");
    //  adamController adam6217_C(ethClient, adam6217C_ip, VOLTAGE_OUTPUT, "ADAM-6217-C");
    //  adamController adam6217_D(ethClient, adam6217D_ip, CURRENT_OUTPUT, "ADAM-6217-D");
    adamController adamsCtrl[4] = {adamController(ethClient, adam6052A_ip, DAC_OUTPUT, "ADAM-6052-A"), adamController(ethClient, adam6052B_ip, DAC_OUTPUT, "ADAM-6052-B"),
                                   adamController(ethClient, adam6217C_ip, VOLTAGE_OUTPUT, "ADAM-6217-C"), adamController(ethClient, adam6217D_ip, CURRENT_OUTPUT, "ADAM-6217-D")};
};

#endif