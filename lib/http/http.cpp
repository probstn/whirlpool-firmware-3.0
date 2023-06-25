#include <Arduino.h>
#include "./heat/heat_listener.h"

class Http : public HeatListener
{

public:
    Http()
    {
        // Constructor
    }

    void pushTemp()
    {
        // Push temperature to server
    }

    void pushisHeating()
    {
        // Push isHeating to server
    }

    void pullisHeating()
    {
        // Pull isHeating from server
    }
    
    void onHeatEvent(bool isTurnedOn)
    {
        // Turn on/off heating
    }
};