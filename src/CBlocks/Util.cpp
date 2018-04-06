#include "Arduino.h"
#include "Util.h"
#include "ArduinoJson.h"

namespace CBlocks{
  String Util::getClientID(unsigned int objectID, unsigned int instanceID){
    String clientID(objectID);
    clientID.concat("-");
    clientID.concat(instanceID);

    return clientID;
  }

  String Util::getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
    String topic(objectID);
    topic.concat("/");
    topic.concat(instanceID);
    topic.concat("/");
    topic.concat(resourceID);
    topic.concat("/");
    topic.concat("output");

    return topic;
  }

  String Util::getInputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
    String topic("internal/+");
    topic.concat("/");
    topic.concat(objectID);
    topic.concat("/");
    topic.concat(instanceID);
    topic.concat("/");
    topic.concat(resourceID);
    topic.concat("/");
    topic.concat("input");

    return topic;
  }

  String Util::getNamedTopic(unsigned int objectID, unsigned instanceID, String resourceName){
    String topic(objectID);
    topic.concat("/");
    topic.concat(instanceID);
    topic.concat("/");
    topic.concat(resourceName);

    return topic;
  }

  String Util::getPayloadFor(unsigned int value){
    return String(value);
  }

  String Util::getPayloadFor(float value){
    return String(value);
  }

  String Util::getPayloadFor(JsonObject& data){
    String payload;
    data.printTo(payload);

    return payload;
  }

  Will Util::getLastWillFor(unsigned int objectID, unsigned int instanceID){
    Will will = {
      Util::getNamedTopic(objectID, instanceID, "status"),
      2,
      true,
      String("offline")
    };

    return will;
  }

  Will Util::getFirstWillFor(unsigned int objectID, unsigned int instanceID){
    Will will = {
      Util::getNamedTopic(objectID, instanceID, "status"),
      2,
      true,
      String("online")
    };

    return will;
  }

  JsonObject& Util::getJSONForPayload(byte *payload, unsigned int length, DynamicJsonBuffer& buffer){
    return buffer.parseObject((char*)payload);
  }

  String Util::validateCommandRequestID(JsonObject& json){
    if(!json.containsKey("requestID")){
      return String("Command has no \"requestID\".");
    }

    if(!json.is<unsigned long>("requestID")){
      return String("\"requestID\" must be of type long.");
    }

    return String("");
  }

  String Util::validateCommandData(JsonObject& json){
    if(!json.containsKey("data")){
      return String("Command has no \"data\".");
    }

    return String("");
  }

  String Util::getResponseTopic(String clientID){
    String& responseTopic = clientID;
    responseTopic.concat("/");
    responseTopic.concat("responses");

    return responseTopic;
  }

  String Util::getClientIDFromCommandTopic(String topic){
    int indexOfFirstTopicSeperator = topic.indexOf('/');
    int indexOfSecondTopicSeperator = topic.indexOf('/', indexOfFirstTopicSeperator+1);

    return topic.substring(indexOfFirstTopicSeperator+1, indexOfSecondTopicSeperator);
  }

  String Util::removeClientIDFromCommandTopic(String topic){
    int indexOfFirstTopicSeperator = topic.indexOf('/');
    int indexOfSecondTopicSeperator = topic.indexOf('/', indexOfFirstTopicSeperator+1);

    String clientIndependentTopic("internal/+/");

    clientIndependentTopic.concat(topic.substring(indexOfSecondTopicSeperator+1));

    return clientIndependentTopic;
  }
}
