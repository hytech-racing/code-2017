/*
  TeensySideLinduinoI2C.ino - Code that runs on BMS Teensy. Serves as a relay between the Linduino and the Car CAN system
  Created by Charith "Karvin" Dassanayake & Shrivathsav Seshan, April 11, 2017.
 */

#include <Wire.h>
#include <Arduino.h>
#include <stdint.h>
#include <FlexCAN.h>
#include "HyTech17.h"

/**
 * BMS State Variables
 */
BMS_voltages bmsVoltageMessage;
BMS_currents bmsCurrentMessage;
BMS_temperatures bmsTempMessage;
BMS_status bmsStatusMessage;

FlexCAN CAN(500000);
static CAN_message_t msg;

// bool readCAN(); // Reads CAN message for controlling BMS
// bool processCAN(); // processes and sends I2C request, called within
// bool writeI2C(int configID); // transmits data to linduino
//
// bool requestI2C(int configID); // sends I2C request for linduino
// bool processI2C(); // processes and sends CAN message, called within
int writeCAN(); // writes status messages for BMS onto CAN

static int runningIndex; // Used for tracking
uint8_t buf[32];

void setup() {
    Serial.begin(115200);
    delay(2000);
    Wire.begin(8);
    delay(2000);
//    CAN.begin();
    Wire.onReceive(receiveEvent);
    pinMode(13, OUTPUT);
    runningIndex = 0;
    Serial.println("Setup Complete");
}

void loop() {
    digitalWrite(13, HIGH);
}

void receiveEvent(int howMany) {
    while (Wire.available()) {
        byte b = Wire.read();
        if (runningIndex == 32) {
            uint8_t singleBuf[8];
            memcpy(&(singleBuf[0]), &(buf[0]), 8);
            bmsVoltageMessage.load(singleBuf);
            memcpy(&(singleBuf[0]), &(buf[8]), 8);
            bmsCurrentMessage.load(singleBuf);
            memcpy(&(singleBuf[0]), &(buf[16]), 8);
            bmsTempMessage.load(singleBuf);
            memcpy(&(singleBuf[0]), &(buf[24]), 8);
            bmsStatusMessage.load(singleBuf);
            runningIndex = 0;
            Serial.println("Full Message Received");
            Serial.print("Total Voltage: "); Serial.println(bmsVoltageMessage.getTotal());
            Serial.print("Average Voltage: "); Serial.println(bmsVoltageMessage.getAverage());
            bmsTester();
        }
        buf[runningIndex] = b;
        runningIndex++;
    }
    writeCAN();
}

void bmsTester() {
//    if (!bmsStatusMessage.getBMSStatusOK()) {
//        Serial.println("FAULT DETECTED!");
//    } else {
//        Serial.println("VOLTAGE IN BOUNDS!");
//    }
    Serial.print("BMS STATUS: ");
    Serial.print(bmsStatusMessage.getBMSStatusOK()); Serial.println(".");
    Serial.print("Over Voltage: ");
    Serial.print(bmsStatusMessage.getChargeOvervoltage() || bmsStatusMessage.getDischargeOvervoltage());
    Serial.print(". Max Voltage: "); Serial.println(bmsVoltageMessage.getHigh());
    Serial.print("Under Voltage: ");
    Serial.print(bmsStatusMessage.getChargeUndervoltage() || bmsStatusMessage.getDischargeUndervoltage());
    Serial.print(". Min Voltage: "); Serial.println(bmsVoltageMessage.getLow());
}

int writeCAN() {
    int bufferAvailable = 0;

    // Send out CAN message 1 - BMS_currents
    BMS_currents curBMS_currents =  BMS_currents();
    msg.ID = BMS_currents;
    msg.len = 8;
    float testFloat = 0; // TODO Replace with real value
    CHARGING_STATE testStatus = UNKNOWN; // TODO Replace with real value

    curBMS_currents.setCurrent(testFloat);
    curBMS_currents.setChargingState(testStatus);

    curBMS_currents.write(msg.buf);
    bufferAvailable += CAN.write(msg);

    // Send out CAN message 1 - BMS_status
    BMS_status curBMS_status = BMS_status();
    msg.ID = BMS_status;
    msg.len = 3;

    // TODO Replace all following with real value

    curBMS_status.setDischargeOvervoltage(false);
    curBMS_status.setDischargeUndervoltage(false);
    curBMS_status.setChargeOvervoltage(false);
    curBMS_status.setChargeUndervoltage(false);

    curBMS_status.setDischargeOvercurrent(false);
    curBMS_status.setDischargeUndercurrent(false);
    curBMS_status.setChargeOvercurrent(false);
    curBMS_status.setChargeUndercurrent(false);

    curBMS_status.setDischargeOvertemp(false);
    curBMS_status.setDischargeUndertemp(false);
    curBMS_status.setChargeOvertemp(false);
    curBMS_status.setChargeUndertemp(false);

    curBMS_status.setBMSStatusOK(true);

    curBMS_status.write(msg.buf);
    bufferAvailable += CAN.write(msg);

    // Send out CAN message 1 - BMS_temperatures

    // Send out CAN message 1 - BMS_voltages

    return bufferAvailable;
}