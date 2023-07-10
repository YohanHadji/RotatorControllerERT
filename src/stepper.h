#include <AccelStepper.h>
#include <config.h>
#include "../ERT_RF_Protocol_Interface/PacketDefinition.h"

enum TRACKING_MODE {
    STATIONARY,
    TRACKING_BINOCULAR,
    TRACKING_TELEMETRY
};

int32_t degToStepAzm(float deg);
int32_t degToStepElv(float deg);

float stepToDegAzm(int32_t step);
float stepToDegElv(int32_t step);

struct controlOutput {
    float azmSpeed;
    float elvSpeed;
};

class solverClass {
    public:
        solverClass();
        void update(float alpha, float beta);
        float computeSpeed();
        float getSpeed();
        void setTimeStep(double timeStepIn);
    private: 
        float alpha;
        float alphaPrev;
        float alpha1;

        float beta;
        float betaPrev;
        float beta1;
        float beta1Prev;
        float beta2; 

        float betaPlusOne;
        float betaPlusOne1;

        float lambda;

        float speedOutput;

        unsigned long timeLastUpdated;
        double timeStep;
};

class conClass {
    public:
        conClass();
        void update(PacketTrackerCmd cmd);
        PacketTrackerCmd getLastCmd();
        controlOutput getOutput();
        controlOutput computeOutput();
        TRACKING_MODE getMode();
        AccelStepper stepperAzm;
        AccelStepper stepperElv;
    private:
        solverClass azm;
        solverClass elv;
        controlOutput output;
        PacketTrackerCmd lastCmd;
        int mode; 
};
