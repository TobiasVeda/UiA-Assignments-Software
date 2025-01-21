#include "mbed.h"
#include <chrono>
#include <cstdio>
#include "wifi-ism43362/ISM43362Interface.h"
#include "HTS221Sensor.h"


const char *ACCESS_TOKEN = "8Y047LHOXw2aoqg0TPWE";
const char *HTTP_SERVER_ADDR = "100.0.0.204";
constexpr uint16_t HTTP_SERVER_PORT = 9090;

constexpr uint32_t HTTP_REQUEST_BUFFER_SIZE = 300;
constexpr uint32_t JSON_CONTENT_BUFFER_SIZE = 100;
constexpr uint32_t HTTP_RESPONSE_BUFFER_SIZE = 400;

int main() {
    DevI2C hts_i2c_pins(PB_11, PB_10);
    //I2C internal_pins(SDA, SCL)
    HTS221Sensor hts(&hts_i2c_pins);

    if (hts.init(NULL) != 0) {
        printf("Failed to initialize HTS221 device!\n");
        }
        // Power up the HTS221 device
    if (hts.enable() != 0) {
        printf("Failed to power up HTS221 device!\n");
    }
    
  float temp = 0.0;
  float humid = 0;

  // Get pointer to default network interface
  NetworkInterface *network = nullptr;

  while (network == nullptr) {
    printf("Get pointer to default network interface...\n");
    network = NetworkInterface::get_default_instance();

    if (!network) {
      printf("Failed to get default network interface\n");
    }

    ThisThread::sleep_for(1000ms);
  } 


  nsapi_size_or_error_t result;
  SocketAddress address;

  while (result != NSAPI_ERROR_OK) {

    printf("Connecting to the network...\n");
    result = network->connect();

    if (result != NSAPI_ERROR_OK) {
      printf("Failed to connect to network: %d\n", result);
      continue;
    }


    printf("Get local IP address...\n");
    result = network->get_ip_address(&address);

    if (result != NSAPI_ERROR_OK) {
      printf("Failed to get local IP address: %d\n", result);
    }

  } 

  printf("Connected to WLAN and got IP address %s\n", address.get_ip_address());

// ^^connect^^ ===================     \/http\/       ======================================


  while (true) {  

    hts.get_temperature(&temp);
    hts.get_humidity(&humid);

    TCPSocket socket;

   
    result = socket.open(network);

    if (result != NSAPI_ERROR_OK) {
      printf("Failed to open TCPSocket: %d\n", result);
      continue;
    }

    
    result = network->gethostbyname(HTTP_SERVER_ADDR, &address);

    if (result != NSAPI_ERROR_OK) {
      printf("Failed to get IP address of host %s: %d\n", HTTP_SERVER_ADDR, result);
      continue;
    }

    printf("IP address of server %s is %s\n", HTTP_SERVER_ADDR, address.get_ip_address());



    // Set server TCP port number
    address.set_port(HTTP_SERVER_PORT);
    // Connect to server at the given address
    result = socket.connect(address);

    // Check result
    if (result != NSAPI_ERROR_OK) {
      printf("Failed to connect to server at %s: %d\n", HTTP_SERVER_ADDR, result);
      continue;
    }

    printf("Successfully connected to server %s\n", HTTP_SERVER_ADDR);



    // Send HTTP POST request
    static char http_request[HTTP_REQUEST_BUFFER_SIZE];
    static char json_content[JSON_CONTENT_BUFFER_SIZE];

    snprintf(json_content, JSON_CONTENT_BUFFER_SIZE,
             "{\"Temperatur\": %.2f, \"Fuktighet\": %0.2f}", temp, humid);

    snprintf(http_request, HTTP_REQUEST_BUFFER_SIZE,
             "POST /api/v1/%s/telemetry HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %u\r\n"
             "\r\n",
             ACCESS_TOKEN, HTTP_SERVER_ADDR, strlen(json_content));

    strcat(http_request, json_content);

    

    // The request might not be fully sent in one go,
    // so keep track of how much we have sent
    nsapi_size_t bytes_to_send = strlen(http_request);
    nsapi_size_or_error_t sent_bytes = 0;

    printf("\nSending message: \n%s\n\n", http_request);

    // Loop as long as there are more data to send
    while (bytes_to_send > 0) {
      // Try to send the remaining data.
      // send() returns how many bytes were actually sent
      sent_bytes = socket.send(http_request + sent_bytes, bytes_to_send);

      if (sent_bytes < 0) {
        // Negative return values from send() are errors
        // break inner loop to then continue outer
        break;
      } else {
        printf("Sent %d bytes\n", sent_bytes);
      }

      bytes_to_send -= sent_bytes;
    }

    if (sent_bytes < 0) {
      printf("Sending HTTP POST failed with error code: %d\n", sent_bytes);
      continue;
    //   continue after breaking inner
    }

    printf("Complete message sent\n");

// =================response from server===================

    // Reuse http_response for recieving response from server
    static char http_response[HTTP_RESPONSE_BUFFER_SIZE];
    // Clear http_response
    memset(http_response, 0, sizeof(http_response));

    nsapi_size_t remaining_bytes = HTTP_RESPONSE_BUFFER_SIZE;
    nsapi_size_or_error_t received_bytes = 0;

    while (remaining_bytes > 0) {
      nsapi_size_or_error_t result = socket.recv(http_response + received_bytes, remaining_bytes);


      if (result < 0) { //less than 0 = error
        received_bytes = result;
        //break inner loop to then continue outer loop
        break;
      } else {
        printf("Received %d bytes\n", result);
      }

      // If the result is 0 there are no more bytes to read
      if (result == 0) {
        break;
      }

      received_bytes += result;
      remaining_bytes -= result;
    }

    if (received_bytes < 0) {
      printf("Receive HTTP respons failed with error code: %d\n", received_bytes);
      continue;
    //   continue outer loop after breaking inner
    }

    printf("\nReceived %d bytes with HTTP status code: %.*s\n", received_bytes,
            strstr(http_response, "\n") - http_response, http_response);


    ThisThread::sleep_for(2000ms);
  }
}