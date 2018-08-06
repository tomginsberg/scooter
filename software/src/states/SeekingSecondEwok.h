#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingSecondEwok: public State {
    TapeFollower tf;

    void onStart() {
        tf.kdTape = 0.21;
        tf.MAX_SPEED=155;
    }
    void onLoop() { 
        tf.poll( 130 ); 
    }

    bool transitionCondition() {
        // <tt>AcquireSecondEwok<tt>
        return digitalRead( R_CLAW_COMM_IN );
    }
};
