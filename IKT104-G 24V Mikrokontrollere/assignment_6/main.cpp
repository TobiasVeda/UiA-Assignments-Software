#include "mbed.h"
#include <algorithm>
#include <cstdio>
#include <wifi-ism43362/ISM43362Interface.h>
#include <chrono>
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main() {     
  DigitalIn button(BUTTON1, PullNone);

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

// ^^connect^^      \/http\/
printf("--Press button to make http request--\n");
while (button.read()) {

}

while (true) {
    
    TCPSocket socket;

    // Configure timeout on socket receive
    // (returns NSAPI_ERROR_WOULD_BLOCK on timeout)
    socket.set_timeout(500);



    result = socket.open(network);

    if (result != NSAPI_ERROR_OK) {
      printf("Failed to open TCPSocket: %d\n", result);
      continue;
    }

    
    const char host[] = "ikt104.andersenitc.no";
    result = network->gethostbyname(host, &address);

    if (result != NSAPI_ERROR_OK) {
      printf("Failed to get IP address of host %s: %d\n", host, result);
      continue;
    }

    printf("IP address of server %s is %s\n", host, address.get_ip_address());



    // Set server TCP port number
    address.set_port(80);
    // Connect to server at the given address
    result = socket.connect(address);

    // Check result
    if (result != NSAPI_ERROR_OK) {
      printf("Failed to connect to server at %s: %d\n", host, result);
      continue;
    }

    printf("Successfully connected to server %s\n", host);

    // Create HTTP request
    const char http_request[] = "GET /index.json HTTP/1.1\r\n"
                                "Host: ikt104.andersenitc.no\r\n"
                                "Connection: close\r\n"
                                "\r\n";


    nsapi_size_t bytes_to_send = strlen(http_request);
    nsapi_size_or_error_t sent_bytes = 0;

    while (bytes_to_send > 0) {
      // Try to send the remaining data.
      // send() returns how many bytes were actually sent
      sent_bytes = socket.send(http_request + sent_bytes, bytes_to_send);

      if (sent_bytes < 0) {
        // Negative return values from send() are errors
        break;
        // break this loop, continue outer loop after breaking
      }

      bytes_to_send -= sent_bytes;
    }
    if (sent_bytes < 0) {
        // continue after inner loop break
      printf("Failed to send HTTP request: %d\n", sent_bytes);
      continue;
    }
    printf("Complete message sent\n");




  // Receive response from the server
    char buffer[101]; // Extra byte for null terminator
    char http_response[2000];
    nsapi_size_or_error_t received_bytes = 0;
    printf("Received response:\n");

    // Receive data in chunks
    while ((received_bytes = socket.recv(buffer, sizeof(buffer) - 1)) > 0) {
        // Null terminate the received data
        buffer[received_bytes] = '\0';
        printf("%s...", buffer);
        strncat(http_response, buffer, 100);
    }

    // Check for errors or if all data received
    if (received_bytes < 0) {
        printf("Failed to receive data: %d\n", received_bytes);
    } else {
        printf("\nReceived all data\n\n");

        printf("=======================================================\n%s", http_response);
        

        printf("===========================json==========================\n");
        std::string c = http_response;
        size_t pos = c.find("{");
        c.erase(0,pos);

        // std::cout <<c;
        json data = json::parse(c);
        std::string fname = data["first name"];
        std::string lname = data["last name"];
        int age = data["age"];
        
        std::cout
        <<"First name: " <<fname <<std::endl
        <<"Last name: " <<lname <<std::endl
        <<"Age: " <<age <<std::endl;
        break;
    }

    // Close the socket
    socket.close();




}


}


    




