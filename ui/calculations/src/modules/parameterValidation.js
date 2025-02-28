// Define custom exception classes
class ParameterException extends Error {
    constructor(message = "", objects = null) {
      super(message);
      this.errorObject = objects;
      this.returnMessage = "Input Parameters Error";
    }
  }
  
  class TemperatureLTK extends ParameterException {
    constructor(objects) {
      // super(`Input ${objects} Temperature should be Higher than 169.75K!`, objects);
      super(`Your input ${objects} temperature is too low. Please check your input value and that you have used the correct unit.`, objects);
    }
  }
  
  class TemperatureGTK extends ParameterException {
    constructor(objects) {
      // super(`Input ${objects} Temperature should be Lower than 374.21K!`, objects);
      super(`Your input ${objects} temperature is too high. Please check your input value and that you have used the correct unit.`, objects);
    }
  }
  
  class TemperatureEquals extends ParameterException {
    constructor(objects) {
      super(`${objects[0]} and ${objects[1]} temperature should not be equal.`, objects);
    }
  }
  
  class TemperatureConstraints extends ParameterException {
    constructor(objects) {
      super(`${objects[0]} temperature should be higher than ${objects[1]}.`, objects);
    }
  }
  
  class PressureLTPa extends ParameterException {
    constructor(objects) {
      // super(`Absolute ${objects} Pressure (Input pressure + ambient pressure) should be Higher than 389.564Pa!`, objects);
      super(`Your absolute ${objects} pressure (input pressure + ambient pressure) is too low. Please check your input ${objects} value and ambient pressure, and check the unit you used.`, objects);
    }
  }
  
  class PressureGTPa extends ParameterException {
    constructor(objects) {
      // super(`Absolute ${objects} Pressure (Input pressure + ambient pressure) should be Less than 4.05928e+06 Pa!`, objects);
      super(`Your absolute ${objects} pressure (input pressure + ambient pressure) is too high. Please check your input ${objects} value and ambient pressure,and check the unit you used.`, objects);
    }
  }
  
  class PressureEquals extends ParameterException {
    constructor(objects) {
      super(`${objects[0]} and ${objects[1]} pressure should not be equal!`, objects);
    }
  }
  
  class PressureConstraints extends ParameterException {
    constructor(objects) {
      super(`${objects[0]} pressure should be higher than ${objects[1]}!`, objects);
    }
  }
  
  class PressureZero extends ParameterException {
    constructor(objects) {
      super(`${objects} pressure should not be 0!`, objects);
    }
  }

  class TimeShort extends ParameterException {
    constructor(objects) {
      super(`Your measured time is too short. Please collect measurement data as the system tends towards equilibrium. We expect that it will take 20 minutes to reach a steady state. `, objects);
    }
  }
  
  // Function to validate parameters
  function checkParametersSystemCalculation(Parameters_MeasuredData) {
    
    //measures time short
    const measuredTime = Parameters_MeasuredData['MeasuredTime'];
    if (measuredTime < 20) throw new TimeShort("MeasuredTime");

    const ASP = Parameters_MeasuredData["ASP"];
  
    // Validate temperature and pressure
    for (const key in Parameters_MeasuredData) {
      if (key.startsWith("T")) {
        if (Parameters_MeasuredData[key] < -103.4) throw new TemperatureLTK(key);
        if (Parameters_MeasuredData[key] > 101.06) throw new TemperatureGTK(key);
      }
  
      if (key.startsWith("P")) {
        if (Parameters_MeasuredData[key] + ASP < 0.00389564) throw new PressureLTPa(key);
        if (Parameters_MeasuredData[key] + ASP > 40.5928) throw new PressureGTPa(key);
      }
    }
  
    const { T2, T3, T1, T4, T5, P1, P2 } = Parameters_MeasuredData;
    const T145Dict = { T1, T4, T5 };
  
    // Validate temperature constraints
    for (const key in T145Dict) {
      if (T2 < T145Dict[key]) throw new TemperatureConstraints(["T2", key]);
      if (T2 === T145Dict[key]) throw new TemperatureEquals(["T2", key]);
  
      if (T3 < T145Dict[key]) throw new TemperatureConstraints(["T3", key]);
      if (T3 === T145Dict[key]) throw new TemperatureEquals(["T3", key]);
    }
  
    // if (T1 === T4) throw new TemperatureEquals(["T1", "T4"]);
    if (T2 === T3) throw new TemperatureEquals(["T2", "T3"]);
  
    // Validate pressure constraints
    if (P1 === 0) throw new PressureZero("P1");
    if (P2 === 0) throw new PressureZero("P2");
    if (P2 < P1) throw new PressureConstraints(["P2", "P1"]);
    if (P2 === P1) throw new PressureEquals(["P1", "P2"]);

  }
  
  // Export for use in a Vue component or a service
  export { checkParametersSystemCalculation };
  