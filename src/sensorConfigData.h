/**
 **************************************************
 *
 * @file        sensorConfigData.h
 * @brief       Header file that stores configuration data for each sensor type
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Josip Šimun Kuči @ soldered.com
 ***************************************************/
#ifndef SENSOR_CONFIG_DATA
#define SENSOR_CONFIG_DATA

struct sensorType
{
    int regression_method;
    double Rs_R0_ratio;
    double coefficient_a;
    double coefficient_b;
};


/*
      Exponential regression:
      Gas    | a      | b
      H2     | 987.99 | -2.162
      LPG    | 574.25 | -2.222
      CO     | 36974  | -3.109
      Alcohol| 3616.1 | -2.675
      Propane| 658.71 | -2.168
    */
const struct sensorType MQ2_config={
    1, //Regression method type (a*ratio^b)

    9.83, //Rs/R0 in clean air

    //Coefficient values calculated (LPG)
    574.25, //a

    -2.222, //b
    
};


    /*
      Exponential regression:
    Gas    | a      | b
    LPG    | 44771  | -3.245
    CH4    | 2*10^31| 19.01
    CO     | 521853 | -3.821
    Alcohol| 0.3934 | -1.504
    Benzene| 4.8387 | -2.68
    Hexane | 7585.3 | -2.849
    */
const struct sensorType MQ3_config={
    1, //Regression method type (a*ratio^b)

    60, //Rs/R0 in clean air

    //Coefficient values calculated (Alcohol)
    0.3934, //a

    -1.504, //b
    
};


    /*
      Exponential regression:
    Gas    | a      | b
    LPG    | 3811.9 | -3.113
    CH4    | 1012.7 | -2.786
    CO     | 200000000000000 | -19.05
    Alcohol| 60000000000 | -14.01
    smoke  | 30000000 | -8.308
    */
const struct sensorType MQ4_config={
    1, //Regression method type (a*ratio^b)
    
    4.4, //Rs/R0 in clean air
    
    //Coefficient values calculated (CH4)
    1012.7, //a
    
    -2.786, //b
       
};



    /*
      Exponential regression:
    Gas    | a      | b
    LPG    | 80.897 | -2.431
    CH4    | 177.65 | -2.56
    CO     | 491204 | -5.826
    H2     | 1163.8 | -3.874
    alcohol| 97124  | -4.918
    */
const struct sensorType MQ5_config={
    1, //Regression method type (a*ratio^b)
    
    6.5, //Rs/R0 in clean air
    
    //Coefficient values calculated (CH4)
    80.897, //a
    
    -2.431, //b
       
};

    /*
      Exponential regression:
    GAS     | a      | b
    H2      | 88158  | -3.597
    LPG     | 1009.2 | -2.35
    CH4     | 2127.2 | -2.526
    CO      | 1000000000000000 | -13.5
    Alcohol | 50000000 | -6.017
    */
const struct sensorType MQ6_config={
    1, //Regression method type (a*ratio^b)
        
    10, //Rs/R0 in clean air
        
    //Coefficient values calculated (LPG)
    1009.2, //a
        
    -2.35, //b
           
};

    /*
      Exponential regression:
    GAS     | a      | b
    H2      | 69.014  | -1.374
    LPG     | 700000000 | -7.703
    CH4     | 60000000000000 | -10.54
    CO      | 99.042 | -1.518
    Alcohol | 40000000000000000 | -12.35
    */
const struct sensorType MQ7_config={
    1, //Regression method type (a*ratio^b)
        
    27.5, //Rs/R0 in clean air
        
    //Coefficient values calculated (CO)
    99.042, //a
        
    -1.518, //b
           
};


    /*
      Exponential regression for all gasses:
    GAS     | a      | b
    H2      | 976.97  | -0.688
    LPG     | 10000000 | -3.123
    CH4     | 80000000000000 | -6.666
    CO      | 2000000000000000000 | -8.074
    Alcohol | 76101 | -1.86
    */
const struct sensorType MQ8_config={
    1, //Regression method type

    70, //Rs/R0 in clean air

    //Coefficient values calculated (H2)
    976.97, //a

    -0.688, //b

    
};

    /*
      Exponential regression:
    GAS     | a      | b
    LPG     | 1000.5 | -2.186
    CH4     | 4269.6 | -2.648
    CO      | 599.65 | -2.244
    */
const struct sensorType MQ9_config={
    1, //Regression method type

    9.6, //Rs/R0 in clean air

    //Coefficient values calculated (LPG)
    1000.5, //a

    -2.186, //b

    
};


    /*
        Linear regression:
    GAS     | a      | b
    O3      | 0.41195 | -0.4708
    */
const struct sensorType MQ131_config={
    0, //Regression method type

    1, //Rs/R0 in clean air

    //Coefficient values calculated (O3)
    0.41195, //a

    -0.4708, //b

    
};

    /*
      Linear regression:
    GAS      | a       | b
    H2       | -0.5101   | 0.31988
    NH3      | -0.47712  | 0.4491
    Toulene  | -0.21779   | -0.23269
    
    */
const struct sensorType MQ135_config={
    0, //Regression method type

    1, //Rs/R0 in clean air

    //Coefficient values calculated (NH3)
    -0.47712, //a

    0.4491, //b

    
};

    /*
        Linear regression:
    GAS     | a        | b
    NH3     | -0.26406 | -0.24143
    */
const struct sensorType MQ137_config={
    0, //Regression method type
    
    1, //Rs/R0 in clean air
    
    //Coefficient values calculated (NH3)
    -0.26406, //a
    
    -0.24143, //b
    };

    /*
        Linear regression:
    GAS        | a        | b
    Alcohol    | -0.46099 | 0.0681
    Acetone    | -0.52356 | 0.49225
    Toluene    | -0.4434  | 0.15397
    */
const struct sensorType MQ138_config={
    0, //Regression method type
    
    1, //Rs/R0 in clean air
    
    //Coefficient values calculated (Toluene)
    -0.4434, //a
    
    0.15397, //b
    };

//Used as the configuration for not yet supported sensors
const struct sensorType Blank_config={
    0, //Regression method type
    
    0, //Rs/R0 in clean air
    
    //Coefficient values calculated 
    0, //a
    
    0, //b
    };

#endif