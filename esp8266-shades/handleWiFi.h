// Handling WiFi and HTTP for window shades

String shiftStringUntil(String& s, String untilString) {
  String result;
  int idx = s.indexOf(untilString);;
  if (idx != -1) {
    result = s.substring(0, idx);
    s.remove(0, idx + untilString.length());
  }
  return result;
}

HttpMethod parseHttpMethodString(String httpMethodStr) {
  HttpMethod result;
  if (httpMethodStr == "GET") {
    result = HM_GET;
  } else if (httpMethodStr == "POST") {
    result = HM_POST;
  } else {
    result = HM_NONE;
  }
  return result;
}

void handleRequest(String request, String& response, String route,
  HttpMethod httpMethod, String (*handler)(String)) {
    if (response.length() > 0) {
      return;
    }

    String reqHttpMethodString = shiftStringUntil(request, " ");
    HttpMethod reqHttpMethod = parseHttpMethodString(reqHttpMethodString);

    String reqRoute = shiftStringUntil(request, " ");

    if (reqHttpMethod != httpMethod) {
      return;
    }

    if (reqRoute != route) {
      return;
    }

    shiftStringUntil(request, "\r\n\r\n");
    String requestBody = request;

    response = handler(requestBody);
  }

String createResponse(String responseBody) {
  // Prepare the response
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: application/json\r\n";
    response += "\r\n";
    if (responseBody.length() > 0) {
      response += responseBody;
    }
    return response;
  }

String createResponse() {
    String responseBody;
    String response = createResponse(responseBody);
    return response;
  }

  String handleCurrentPosition(String requestBody) {
    String responseBody = String(currentPosition[0]);    // hier muss der entsprechende Wert rein
    String response = createResponse(responseBody);
    return response;
  }
  String handleCurrentPosition1(String requestBody) {
    String responseBody = String(currentPosition[1]);    // hier muss der entsprechende Wert rein
    String response = createResponse(responseBody);
    return response;
  }

  String handlePositionState(String requestBody) {
    String responseBody = String(positionState[0]);   //hier auch
    String response = createResponse(responseBody);
    return response;
  }
  String handlePositionState1(String requestBody) {
    String responseBody = String(positionState[1]);   //hier auch
    String response = createResponse(responseBody);
    return response;
  }
 
  String handleTargetPositionBoth(String requestBody, bool _window) {
    String response = createResponse();

    // TODO: Pretty bad JSON parsing.
    // We should really use a proper JSON parsing library here.
    const String valueKey = "\"value\"";
    int idx = requestBody.indexOf(valueKey);
    if (idx == -1) {
      return response;
    }
    requestBody.remove(0, idx + valueKey.length());
    idx = requestBody.indexOf(':');
    if (idx == -1) {
      return response;
    }
    requestBody.remove(0, idx + 1);
    idx = requestBody.indexOf('}');
    if (idx == -1) {
      return response;
    }
    String newTargetPositionStr = requestBody.substring(0, idx);
    newTargetPositionStr.trim();

    int newTargetPosition = newTargetPositionStr.toInt();

    // if isNaN(newTargetPosition)
    if (newTargetPosition == 0 && newTargetPositionStr != "0") {
      return response;
    }

    if (newTargetPosition < 0 || newTargetPosition > 100
      || newTargetPosition == targetPosition[_window]
      || (targetPosition[_window] == -1 && newTargetPosition == currentPosition[_window])) {
      return response;
    }

    targetPosition[_window] = newTargetPosition;

    void closeWindow(bool _window);
    void openWindow(bool _window);
    
    Serial.println("Target position Window "+String(_window)+" :" + targetPosition[_window]);
    if (newTargetPosition < currentPosition[_window])
    {
      closeWindow(_window);
    }
    if (newTargetPosition > currentPosition[_window])
    {
      openWindow(_window);
    }

    return response;
  }

  String handleTargetPosition(String requestBody) {
    String response = handleTargetPositionBoth(requestBody, 0);  
    return response;
  }

  String handleTargetPosition1(String requestBody) {
    String response =  handleTargetPositionBoth(requestBody, 1);
    return response;  
  }
 
