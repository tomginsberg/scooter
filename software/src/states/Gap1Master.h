
#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

class S_Gap1Master: public State {
    uint8_t state = 0;
    uint8_t sensorBias = 50;

    void onLoop() { 
        switch( state ) {
            case 0: 
                {
                    LEFT_EDGE_BASELINE  = analogRead( TF_EDGE_LEFT  );
                    RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
                    Motors::run(135,105);
                    state = 5;
                    break;
                }
            case 5:
                {
                    if ( analogRead( TF_EDGE_LEFT )  > 350 - sensorBias)
                        { 
                           state = 10;
                           Motors::hardStop();
                           delay(200);
                       }
                    else if ( analogRead( TF_EDGE_RIGHT ) > 850 - sensorBias)
                        {
                            state = 20;
                            Motors::hardStop();
                            delay(200);
                        }

                    break;
                }
            
            case 10: 
                {
                    Motors::run( 90, -60 );
                    if ( analogRead( TF_EDGE_RIGHT ) > 850 - sensorBias){
                            Motors::stop();
                            delay(200);
                            state = 30; 
                        }
                    break;
                }

            case 20: 
                {
                    Motors::run( -60, 90 );
                    if( analogRead( TF_EDGE_LEFT ) > 350 - sensorBias) {
                        Motors::stop();
                        delay(200);
                        state = 30;
                    }
                    break;
                }
            case 30:
                {
                    Motors::run(-100,-110);
                    delay(600);
                    Motors::stop();
                    state=40;
                }
        }
    }
    

    bool transitionCondition() {
        // <tt>DropFirstPlatform<tt> 
        return (state==40);
    }
};
