#include "open62541.h"
#include "ultrasonic.h"

#define MAX_DISTANCE_CM 500 
#define GPIO_TRIGGER	33
#define GPIO_ECHO	32

UA_StatusCode readCurrentDistance(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeId, void *nodeContext, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue);

void addCurrentDistanceDataSourceVariable(UA_Server *server);