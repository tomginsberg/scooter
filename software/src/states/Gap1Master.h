
#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

class S_Gap1Master: public State {
    uint8_t state = 0;
    uint8_t sensorBias = 70;

    void onLoop() { 
        switch( state ) {
            case 0: 
                {
                    LEFT_EDGE_BASELINE  = analogRead( TF_EDGE_LEFT  );
                    RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
                    Motors::run(30,110);
                    delay(400);
                    Motors::stop();
                    delay(200);
                    Motors::run(100,110);
                    delay(200);
                    Motors::stop();
                    delay(200);
                    Motors::run(130,20);
                    delay(400);
                    Motors::run(120,100);
                    state = 5;
                    break;
                }
            case 5:
                {
                    if ( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_THR ) {
                    //if ( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_BASELINE + LEFT_EDGE_DELTA ) { 
                           state = 10;
                           Motors::hardStop();
                           delay(200);
                    } else if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR) {
                    //} else if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_BASELINE + RIGHT_EDGE_DELTA ) {
                            state = 20;
                            Motors::hardStop();
                            delay(200);
                    }

                    break;
                }
            
            case 10: 
                {
                    Motors::run( 90, -50 );

                    if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR ) {
                    //if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_BASELINE + RIGHT_EDGE_DELTA ) {
                            Motors::stop();
                            delay(200);
                            state = 30; 
                    }
                    break;
                }

            case 20: 
                {
                    Motors::run( -50, 90 );
                    if( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_THR ) {
                    //if( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_BASELINE + LEFT_EDGE_DELTA ) {
                        Motors::stop();
                        delay(200);
                        state = 30;
                    }
                    break;
                }
            case 30:
                {
                    Motors::run(-90,-95);
                    delay(800);
                    Motors::run(200);
                    delay(20);
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
