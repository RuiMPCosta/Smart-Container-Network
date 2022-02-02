#include "model.h"

UA_StatusCode readCurrentDistance(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeId, void *nodeContext, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) {
    uint32_t distance;
    ultrasonic_sensor_t sensor = {
		.trigger_pin = GPIO_TRIGGER,
		.echo_pin = GPIO_ECHO
    };
    ultrasonic_init(&sensor);
    ultrasonic_measure_cm(&sensor, MAX_DISTANCE_CM, &distance);
    UA_Float distancia = distance;
    UA_Variant_setScalarCopy(&dataValue->value, &distancia, &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


void addCurrentDistanceDataSourceVariable(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Distance");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "distance");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "distance");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentDistance;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId, parentReferenceNodeId, currentName, variableTypeNodeId, attr, timeDataSource, NULL, NULL);
}